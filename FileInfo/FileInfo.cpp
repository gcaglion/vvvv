#include "FileInfo.h"

sFileInfo::sFileInfo(s0name* name_, s0parms* cparms_, s0* parent_) : s0(name_, cparms_, parent_, true) {

	//-- set File, Path, mode from parameters
	mode=cparms->pvalI[0];
	strcpy_s(Path, MAX_PATH, cparms->pvalS[1]);
	strcpy_s(Name, MAX_PATH, cparms->pvalS[2]);

	setModeS();
	fopen_s(&handle, FullName, modeS);
	if (errno!=0) {
		sprintf_s(errmsg, sizeof(errmsg), "%s(): Error %d trying to %s file %s", __func__, errno, modeDesc, FullName);
		throw std::exception(errmsg);
	}
	savePos();
}

sFileInfo::~sFileInfo() {
	fflush(handle);
	fseek(handle, 0, SEEK_END); // seek to end of file
	size_t fsize = ftell(handle); // get current file pointer

	fclose(handle);
	if (fsize==0) remove(FullName);
}
void sFileInfo::savePos() {
	fgetpos(handle, &pos);
}
void sFileInfo::restorePos(){
	fsetpos(handle, &pos);
}
void sFileInfo::setModeS() {
	DWORD ct=timeGetTime();

	if (strlen(Path)==0) {
		if (!getCurrentPath(Path)) {
			sprintf_s(errmsg, sizeof(errmsg), "%s(): getCurrentPath() failed.\n", __func__); throw std::runtime_error(errmsg);
		}
	}
	switch (mode) {
	case FILE_MODE_READ:
		strcpy_s(modeS, "r");
		strcpy_s(modeDesc, "Read"); 
		sprintf_s(FullName, MAX_PATH-1, "%s/%s", Path, Name);
		break;
	case FILE_MODE_WRITE:
		strcpy_s(modeS, "w");
		strcpy_s(modeDesc, "Write"); 
		//sprintf_s(FullName, MAX_PATH-1, "%s/%lu_%s", Path, ct, Name);
		sprintf_s(FullName, MAX_PATH-1, "%s/%s", Path, Name);
		break;
	case FILE_MODE_APPEND:
		strcpy_s(modeS, "a");
		strcpy_s(modeDesc, "Append"); 
		break;
	default:
		sprintf_s(errmsg, sizeof(errmsg), "%s(): Error %d accessing file %s; invalid mode: (%d)\n", __func__, errno, FullName, mode); throw std::runtime_error(errmsg);
		break;
	}
}


#include "FileInfo.h"

void sFileInfo::commonConstructor() {
	switch (mode) {
	case FILE_MODE_READ:
		strcpy_s(modeS, "r");
		strcpy_s(modeDesc, "Read");
		break;
	case FILE_MODE_WRITE:
		strcpy_s(modeS, "w");
		strcpy_s(modeDesc, "Write");
		break;
	case FILE_MODE_APPEND:
		strcpy_s(modeS, "a");
		strcpy_s(modeDesc, "Append");
		break;
	default:
		dbg->out(DBG_MSG_FAIL, __func__, "Invalid mode: (%d)", mode);
		break;
	}

	fopen_s(&handle, ffname, modeS);
	if (errno!=0) dbg->out(DBG_MSG_FAIL, __func__, "Error %d", errno);
	savePos();

}
sFileInfo::sFileInfo(s0parmsdef, char* fname_, int mode_, char* fpath_) : s0(s0parmsval) {
	mode=mode_;
	strcpy_s(fpath, MAX_PATH, fpath_);
	strcpy_s(fname, MAX_PATH, fname_);
	sprintf_s(ffname, MAX_PATH, "%s/%s", fpath, fname);

	commonConstructor();
}
sFileInfo::sFileInfo(s0parmsdef, char* ffname_, int mode_) : s0(s0parmsval) {
	mode=mode_;
	strcpy_s(ffname, MAX_PATH, ffname_);
	splitFullFileName(ffname, fpath, fname);

	commonConstructor();
}

sFileInfo::~sFileInfo() {
	fflush(handle);
	fseek(handle, 0, SEEK_END); // seek to end of file
	size_t fsize = ftell(handle); // get current file pointer

	fclose(handle);
	if (fsize==0) remove(ffname);
}
void sFileInfo::savePos() {
	fgetpos(handle, &pos);
}
void sFileInfo::restorePos(){
	fsetpos(handle, &pos);
}


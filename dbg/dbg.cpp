#include "dbg.h"

sDbg::sDbg(s0* parent_, bool verbose_, int dest_, bool timing_, bool pauseOnError_, char* outFilePath_) :s0((new s0Name("%s_Dbg", ((parent_==nullptr) ? "default" : parent_->name->s))), parent_, true) {
	verbose=verbose_; dest=dest_; timing=timing_; pauseOnError=pauseOnError_;
	strcpy_s(outFilePath, MAX_PATH, outFilePath_);
	sprintf_s(outFileName, MAX_PATH, "%s(%p).%s", name->s, parent, (verbose) ? "log" : "err");
	msg[0]='\0'; stack[0]='\0';
	outFile=nullptr;
	if (dest!=DBG_DEST_SCREEN) {
		try {
			outFile=new tFileInfo(this, outFileName, outFilePath, FILE_MODE_WRITE);
		}
		catch (std::exception exc) {
			sprintf_s(errmsg, DBG_MSG_MAXLEN, "%s(): Error trying to create outFile %s/%s . Exception: %s", __func__, outFilePath, outFileName, exc.what());
			throw std::exception(errmsg);
		}
	}
}

sDbg::~sDbg() {
	delete outFile;
}

void sDbg::out(int msgtype, const char* callerFunc_, char* msgMask, ...) {
	char tmpmsg[DBG_MSG_MAXLEN];

	if (msgtype==OBJ_MSG_INFO&&!verbose) return;
	va_list args;
	va_start(args, msgMask);
	vsprintf_s(tmpmsg, OBJ_MSG_MAXLEN, msgMask, args);
	va_end(args);

	char indent[16]=""; for (int t=0; t<stackLevel; t++) strcat_s(indent, 16, "\t");
	sprintf_s(msg, OBJ_MSG_MAXLEN, "%s%s->%s() %s %s \n", indent, parent->name->s, callerFunc_, (msgtype==OBJ_MSG_INFO) ? "INFO:  " : "ERROR: ", tmpmsg);
	strcat_s(stack, DBG_STACK_MAXLEN, "\n"); strcat_s(stack, DBG_STACK_MAXLEN, msg);

	printf("%s", msg);
	if (dest!=DBG_DEST_SCREEN) {
		fprintf_s(outFile->handle, "%s", msg);
	}

}

#include "dbg.h"

sDbg::sDbg(s0name* name_, s0parms* cparms_, s0* parent_) : s0(name_, cparms_, parent_) {

	//-- set default values for each parameter not set in cParms
	if (cparms->pcnt<5) strcpy_s(outFilePath, MAX_PATH, DEFAULT_DBG_FPATH);
	if (cparms->pcnt<4) pauseOnError=DEFAULT_DBG_PAUSERR;
	if (cparms->pcnt<3) timing=DEFAULT_DBG_TIMING;
	if (cparms->pcnt<2) dest=DEFAULT_DBG_DEST;
	if (cparms->pcnt<1) verbose=DEFAULT_DBG_VERBOSITY;

	//-- initialize stack
	stack[0]='\0';
	
	//-- create outFile, if so needed
	char outFileName[MAX_PATH];
	sprintf_s(outFileName, MAX_PATH, "%s(%p).%s", name->s, parent, (verbose) ? "log" : "err");
	if (dest!=DBG_DEST_SCREEN) {
		safespawn0(outFile, tFileInfo, new s0name("%s_File", name->s), new s0parms("%d, %s, %s", FILE_MODE_WRITE, outFilePath, outFileName));
	}
}

sDbg::~sDbg() {
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
	strcat_s(stack, DBG_STACK_MAXLEN, msg); strcat_s(stack, DBG_STACK_MAXLEN, "\n");
	

	printf("%s", msg);
	if (dest!=DBG_DEST_SCREEN) {
		fprintf_s(outFile->handle, "%s", msg);
	}

}

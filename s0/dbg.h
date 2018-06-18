#pragma once
#include "../CommonEnv.h"

#define DEFAULT_DBG_DEST_SCREEN	true
#define DEFAULT_DBG_DEST_FILE	true
#define DEFAULT_DBG_FPATH		"C:/temp/logs"
#define DEFAULT_DBG_FNAME		"Debugger"
#define DEFAULT_DBG_VERBOSITY	true
#define DEFAULT_DBG_TIMING		false
#define DEFAULT_DBG_PAUSERR		true
#define DBG_MSG_MAXLEN			1024
#define DBG_STACK_MAXLEN		32768
//--
#define DBG_MSG_INFO 0
#define DBG_MSG_ERR  1
#define DBG_MSG_FAIL  2
//--

struct sDbgParms {
	int stackLevel;
	bool verbose;
	bool destfile;
	bool destscreen;
	bool timing;
	bool pauseOnError;
	char outfilepath[MAX_PATH];
	char outfilename[MAX_PATH];
	char outfilefullname[MAX_PATH];
	FILE* outfile;
	char msg[DBG_MSG_MAXLEN];
	char stack[DBG_STACK_MAXLEN];

	sDbgParms(bool verbose_=DEFAULT_DBG_VERBOSITY, bool destscreen_=DEFAULT_DBG_DEST_SCREEN, bool destfile_=DEFAULT_DBG_DEST_FILE, char* outfilepath_=DEFAULT_DBG_FPATH) {
		verbose=verbose_; destscreen=destscreen_, destfile=destfile_;
		strcpy_s(outfilepath, MAX_PATH, outfilepath_);
		stack[0]='\0';
	}

	void createOutFile(char* parentName, void* parentAddr) {
		sprintf_s(outfilename, MAX_PATH, "%s(%p)_Dbg.%s", parentName, parentAddr, (verbose)?"log":"err");
		sprintf_s(outfilefullname, MAX_PATH, "%s/%s", outfilepath, outfilename);
		outfile=nullptr;
		fopen_s(&outfile, outfilefullname, "w");
		if (errno!=0) out(DBG_MSG_FAIL, __func__, "Error %d", errno);
	}

	void out(int msgtype, const char* callerFunc_, char* msgMask_, ...) {
		if (msgtype==DBG_MSG_INFO&&!verbose) return;

		char indent[16]=""; for (int t=0; t<stackLevel; t++) strcat_s(indent, 16, "\t");

		va_list va_args;
		va_start(va_args, msgMask_);
		vsprintf_s(msg, DBG_MSG_MAXLEN, msgMask_, va_args); strcat_s(msg, DBG_MSG_MAXLEN, "\n");
		strcat_s(stack, DBG_STACK_MAXLEN, msg); 
		va_end(va_args);

		if(destscreen) printf("%s", msg);
		if (destfile && outfile!=nullptr) fprintf(outfile, "%s", msg);

	}
};

#define newdbg(...) new sDbgParms(__VA_ARGS__)
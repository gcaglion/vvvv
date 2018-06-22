#pragma once
#include "../CommonEnv.h"
#include "../Utils/Utils.h"

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


#define info(msgMask_, ...) dbg->out(DBG_MSG_INFO, __func__, msgMask_, __VA_ARGS__)
#define err(msgMask_, ...) dbg->out(DBG_MSG_ERR, __func__, msgMask_, __VA_ARGS__)
#define fail(msgMask_, ...) dbg->out(DBG_MSG_FAIL, __func__, msgMask_, __VA_ARGS__)

struct sDbg {
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

	EXPORT sDbg(bool verbose_=DEFAULT_DBG_VERBOSITY, bool destscreen_=DEFAULT_DBG_DEST_SCREEN, bool destfile_=DEFAULT_DBG_DEST_FILE, char* outfilepath_=DEFAULT_DBG_FPATH);
	EXPORT ~sDbg();

	EXPORT void createOutFile(char* parentName, void* parentAddr);
	EXPORT void out(int msgtype, const char* callerFunc_, char* msgMask_, ...);

};
#define newdbg(...) new sDbg(__VA_ARGS__)

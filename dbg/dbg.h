#pragma once
#include "../CommonEnv.h"
#include "../s0/s0.h"
#include "../FileInfo/FileInfo.h"
#include "Debugger_enums.h"
/*
#define info(msg_, ...) { dbg->out(OBJ_MSG_INFO, this, __func__, msg_, __VA_ARGS__); }
#define err(msg_, ...) { dbg->out(OBJ_MSG_ERR, this, __func__,  msg_, __VA_ARGS__); }
#define fail(msg_, ...) { dbg->out(OBJ_MSG_FAIL, this, __func__, msg_, __VA_ARGS__); }
*/
#define OBJ_MSG_INFO 0
#define OBJ_MSG_ERR 1
#define OBJ_MSG_FAIL 2
//--
#define DEFAULT_DBG_DEST		DBG_DEST_BOTH
#define DEFAULT_DBG_FPATH		"C:/temp/logs"
#define DEFAULT_DBG_FNAME		"Debugger"
#define DEFAULT_DBG_VERBOSITY	true
#define DEFAULT_DBG_TIMING		false
#define DEFAULT_DBG_PAUSERR		true
#define DBG_MSG_MAXLEN			OBJ_MSG_MAXLEN
#define DBG_STACK_MAXLEN		OBJ_STACK_MAXLEN

struct sDbg : s0 {
	int dest;
	bool verbose;
	bool timing;
	bool pauseOnError;
	tFileInfo* outFile;
	char outFilePath[MAX_PATH];
	char outFileName[MAX_PATH];

	char msg[DBG_MSG_MAXLEN];
	char stack[DBG_STACK_MAXLEN];

	EXPORT sDbg(s0* parent_, bool verbose_=DEFAULT_DBG_VERBOSITY, int dest_=DEFAULT_DBG_DEST, bool timing_=DEFAULT_DBG_TIMING, bool pauseOnError_=DEFAULT_DBG_PAUSERR, char* outFilePath_=DEFAULT_DBG_FPATH);
	EXPORT ~sDbg();

	EXPORT void out(int type, const char* callerFunc_, char* msgMask, ...);


};
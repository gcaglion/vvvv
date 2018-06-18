#pragma once
#include "../CommonEnv.h"
#include "../s0/s0.h"
#include "../FileInfo/FileInfo.h"
#include "Debugger_enums.h"

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

	//-- constructor parameters (in order)
	bool verbose;
	int dest;
	bool timing;
	bool pauseOnError;
	char outFilePath[MAX_PATH];

	//-- internal variables
	tFileInfo* outFile;
	char msg[DBG_MSG_MAXLEN];
	char stack[DBG_STACK_MAXLEN];

	EXPORT sDbg(s0parmsdef);
	EXPORT ~sDbg();

	EXPORT void out(int type, const char* callerFunc_, char* msgMask, ...);


};



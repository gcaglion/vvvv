#pragma once
typedef void * sql_context;



#include "../CommonEnv.h"
#include <math.h>

#ifdef __cplusplus
#undef EXPORT
#define EXPORT extern "C" __declspec(dllexport)
#else
typedef int bool;
#define true 1
#define false 0
#include "../dbg/dbg.h"
#endif
#include "../DBConnection/DBConnection.h"


#define infoC(msgMask_, ...) dbgout(DBG_MSG_INFO, __func__, msgMask_, __VA_ARGS__)
#define errC(msgMask_, ...) dbgout(DBG_MSG_ERR, __func__, msgMask_, __VA_ARGS__)
#define failC(msgMask_, ...) { dbgout(DBG_MSG_ERR, __func__, msgMask_, __VA_ARGS__); throw std::exception(dbgparms->msg);}

//=== DB common functions
EXPORT bool OraConnect(tDbgParms* dbgparms, tDBConnection* DBConnInfo);
EXPORT void OraDisconnect(tDBConnection* DBConnInfo, int Commit);
EXPORT void OraCommit(tDBConnection* DBConnInfo);

//=== Retrieval functions
EXPORT bool Ora_GetFlatOHLCV(tDbgParms* dbgparms, tDBConnection* db, char* pSymbol, char* pTF, char* pDate0, int pRecCount, char** oBarTime, float* oBarData, char* oBaseTime, float* oBaseBar);

//=== Logging functions
EXPORT bool Ora_LogSaveMSE(tDbgParms* dbgparms, tDBConnection* db, int pid, int tid, int mseCnt, float* mseT, float* mseV);
EXPORT bool Ora_LogSaveW(tDbgParms* dbgparms, tDBConnection* db, int pid, int tid, int epoch, int Wcnt, numtype* W);
EXPORT bool Ora_LogSaveClient(tDbgParms* dbgparms, tDBConnection* db, int pid, char* clientName, DWORD startTime, DWORD duration, int simulLen, char* simulStart, bool doTrain, bool doTrainRun, bool doTestRun);
EXPORT bool Ora_LogSaveRun(tDbgParms* dbgparms, tDBConnection* db, int pid, int tid, int setid, int npid, int ntid, int barCnt, int featuresCnt, int* feature, numtype* prediction, numtype* actual);
EXPORT bool Ora_LogLoadW(tDbgParms* dbgparms, tDBConnection* db, int pid, int tid, int epoch, int Wcnt, numtype* oW);

#ifdef __cplusplus
#undef EXPORT
#define EXPORT __declspec(dllexport)
#endif

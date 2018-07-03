// Database Connection - generic (can be used for both data retrieval and logging)
#pragma once
#include "../CommonEnv.h"
#include "DBConnection_enums.h"
#ifdef __cplusplus
#include "../s0/s0.h"
#include "../ConfigMgr/ConfigMgr.h"
#endif

//-- limits
#define DBUSER_MAXLEN 30
#define DBPASSWORD_MAXLEN 30
#define DBCONNSTRING_MAXLEN 30

typedef struct sDBConnection
#ifdef __cplusplus
	: s0
#endif
{
	char DBUser[DBUSER_MAXLEN];
	char DBPassword[DBPASSWORD_MAXLEN];
	char DBConnString[DBCONNSTRING_MAXLEN];
	void* DBCtx;

#ifdef __cplusplus
	EXPORT sDBConnection(s0parmsdef, const char* username, const char* password, const char* connstring);
	EXPORT sDBConnection(s0parmsdef, sCfgKey* cfgKey_);
	EXPORT ~sDBConnection();
#endif

} tDBConnection;

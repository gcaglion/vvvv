#pragma once
#include "../CommonEnv.h"
#include "DataSource.h"
#include "../DBConnection/DBConnection.h"
#include "../ConfigMgr/ConfigMgr.h"
#include "FXData_enums.h"

#define FX_SYMBOL_MAXLEN 8
#define FX_TIMEFRAME_MAXLEN 4

typedef struct sFXData : sDataSource {
	tDBConnection* db=nullptr;
	char Symbol[FX_SYMBOL_MAXLEN];
	char TimeFrame[FX_TIMEFRAME_MAXLEN];
	Bool IsFilled;
#ifdef __cplusplus
	EXPORT sFXData(s0parmsdef, tDBConnection* db_, char* symbol_, char* tf_, Bool isFilled_);
	EXPORT sFXData(s0parmsdef, sCfgKey* cfgKey_);
	EXPORT ~sFXData();
	EXPORT void sFXData_common();
#endif
} tFXData;


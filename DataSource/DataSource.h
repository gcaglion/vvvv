#pragma once
#include "../CommonEnv.h"
#include "../s0/s0.h"
#include "DataSource_enums.h"
#include "../ConfigMgr/ConfigMgr.h"

typedef struct sDataSource : s0 {
	
	int type;

	int featuresCnt;
	Bool calcBW;
	int BWfeatureH;
	int BWfeatureL;

#ifdef __cplusplus
	sDataSource(s0parmsdef, int type_, Bool calcBW_=false, int BWfeatureH_=1, int BWfeatureL_=2);
	sDataSource(s0parmsdef, sCfg* cfgParms_, sCfgKey* cfgKey_);
	sDataSource(s0parmsdef);
	~sDataSource();
#endif

} tDataSource;

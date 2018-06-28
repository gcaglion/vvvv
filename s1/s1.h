#pragma once

#include "../s0/s0.h"
#include "../ConfigMgr/ConfigMgr.h"

struct s1 : s0 {

	EXPORT s1(s0parmsdef) : s0(s0parmsval) {

	}

	EXPORT sDbg* newCfgDbg(sCfg* cfgSet_, char* cfgKeyName_);

};


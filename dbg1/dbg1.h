#pragma once
#include "../dbg/dbg0.h"
#include "../ConfigMgr/ConfigMgr.h"

struct sDbg1 : sDbg0 {

	sCfg* cfgSet;
	sCfgKey* cfgKey;

	sDbg1(sCfg* cfgSet_, sCfgKey* cfgKey_) {
		cfgSet=cfgSet_;
		cfgKey=cfgKey_;

	}
};
#pragma once

#include "../s0/s0.h"
#include "../ConfigMgr/ConfigMgr.h"

#define s1parmsdef s0parmsdef, sCfgKey* cfgObjParmsKey_
#define s1parmsval s0parmsval, cfgObjParmsKey_

struct s1 : s0 {

	sCfgKey* cfg;

	EXPORT s1(s1parmsdef);
	EXPORT virtual ~s1();

	template<class className, class methodName, class ...methodArgs> void _callM(const char* callerFunc_, char* objVarName_, className* obj, char* metS, methodName met, methodArgs... mArgs) {

		svard* callSvard=new svard();
		callSvard->variadic(mArgs...);
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s->%s(%s)", objVarName_, metS, callSvard->fullval);

		try {
			info("%s TRYING  : %s", name, cmd);
			(obj->*met)(mArgs...);
			info("%s SUCCESS : %s", name, cmd);
		}
		catch (std::exception exc) {
			fail("%s FAILURE : %s . Exception: %s", name, cmd, exc.what());
		}
	}

	template <class objT, class ...classArgs> EXPORT objT* _spawn1(const char* callerFunc_, const char* objVarName_, sName* childSname_, sDbg* childDbg_, sCfgKey* childCfg_, classArgs... childCargs) {
		svard* childSvard=new svard();
		childSvard->variadic(childCargs...);
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", objVarName_, typeid(objT).name(), childSvard->fullval);

		objT* retObj;
		try {
			info("%s TRYING  : %s", name, cmd);
			retObj = new objT(this, childSname_, childDbg_, childCfg_, childCargs...);
			info("%s SUCCESS : %s", name, cmd);
			child[childrenCnt]=retObj;
			childrenCnt++;
		}
		catch (std::exception exc) {
			fail("%s FAILURE : %s . Exception: %s", name, cmd, exc.what());
		}
		return retObj;
	}

};

#define safespawn1(objVarName_, className_, objSname_, objDbg_, objCfgKey_, ...) objVarName_ = _spawn1<className_>(__func__, #objVarName_, objSname_, objDbg_, objCfgKey_, __VA_ARGS__)

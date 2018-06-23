#pragma once
#include "../CommonEnv.h"
#include "../dbg/dbg.h"
#include "svard.h"
#include <typeinfo>

#define OBJ_NAME_MAXLEN 128
#define OBJ_MAX_CHILDREN 64
//--
#define OBJ_PARMS_MAXCNT		32
#define OBJ_PARMS_MASK_MAXLEN	125
#define OBJ_PARMS_VAL_MAXLEN	1024

struct sName {
	char s[OBJ_NAME_MAXLEN];
	EXPORT sName(char* nameMask_, ...);
};
#define newsname(nameMask_, ...) new sName(nameMask_, __VA_ARGS__)

#define s0parmsdef s0* parent_, sName* sname_, sDbg* dbg_
#define s0parmsval parent_, sname_, dbg_
struct s0 {

	char name[OBJ_NAME_MAXLEN];
	s0* parent;
	char parentFunc[2048];
	int stackLevel;
	int childrenCnt;
	s0* child[OBJ_MAX_CHILDREN];
	//-- debugging
	sDbg* dbg;
	
	EXPORT s0(s0parmsdef);
	EXPORT virtual ~s0();

	template<class className, class methodName, class ...methodArgs> void _callM(const char* callerFunc_, char* objVarName_, className* obj, char* metS, methodName met, methodArgs... mArgs) {
		svard* callSvard=new svard();
		callSvard->variadic(mArgs...);
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s->%s(%s)", objVarName_, metS, callSvard->fullval);

		try {
			info("TRYING  : %s", cmd);
			(obj->*met)(mArgs...);
			info("SUCCESS : %s", cmd);
		}
		catch (std::exception exc) {
			fail("FAILURE : %s . Exception: %s", cmd, exc.what());
		}
		
	}

	template <class objT, class ...classArgs> objT* _spawn(const char* callerFunc_, char* objVarName_, sName* childSname_, sDbg* childDbg_, classArgs... childCargs){
		svard* childSvard=new svard();
		childSvard->variadic(childCargs...);
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", objVarName_, typeid(objT).name(), childSvard->fullval);

		objT* retObj;
		try {
			info("TRYING  : %s", cmd);
			retObj = new objT(this, childSname_, childDbg_, childCargs...);
			info("SUCCESS : %s", cmd);
			child[childrenCnt]=retObj;
			childrenCnt++;
		}
		catch (std::exception exc) {
			fail("FAILURE : %s . Exception: %s", cmd, exc.what());
		}
		return retObj;

	}

};

#define safecall(className_, objName_, methodName_, ...) _callM<className_>(__func__, objName_->name, objName_, #methodName_, &className_::methodName_, __VA_ARGS__)
#define safespawn(objVarName_, className_, objSname_, objDbg_, ...) objVarName_ = _spawn<className_>(__func__, #objVarName_, objSname_, objDbg_, __VA_ARGS__)



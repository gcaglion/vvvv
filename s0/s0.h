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

	template <class objT, class ...classArgs> objT* _spawn(const char* callerFunc_, sName* childSname_, sDbg* childDbg_, classArgs... childCargs){
		svard* childSvard=new svard();
		childSvard->variadic(childCargs...);
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", childSname_->s, typeid(objT).name(), childSvard->fullval);

		objT* retObj;
		try {
			dbg->out(DBG_MSG_INFO, callerFunc_, "TRYING  : %s", cmd);
			retObj = new objT(this, childSname_, childDbg_, childCargs...);
			dbg->out(DBG_MSG_INFO, callerFunc_, "SUCCESS : %s", cmd);
			child[childrenCnt]=retObj;
			childrenCnt++;
		}
		catch (std::exception exc) {
			dbg->out(DBG_MSG_ERR, callerFunc_, "FAILURE : %s . Exception: %s", cmd, exc.what());
			throw std::exception(dbg->msg);
		}
		return retObj;

	}

};

#define safespawn(objVarName_, className_, objSname_, objDbg_, ...) objVarName_ = _spawn<className_>(__func__, objSname_, objDbg_, __VA_ARGS__)



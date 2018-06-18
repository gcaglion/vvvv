#pragma once
#include "../CommonEnv.h"
#include "svard.h"
#include "dbg.h"

#define CMD_MAXLEN 4096
#define OBJ_NAME_MAXLEN 128
#define OBJ_MAX_CHILDREN 64
//--
#define OBJ_PARMS_MAXCNT		32
#define OBJ_PARMS_MASK_MAXLEN	125
#define OBJ_PARMS_VAL_MAXLEN	1024

#define s0parmsdef   sname* name_, s0* parent_, sDbgParms* dbg_
#define s0parmsval name_, parent_, dbg_

struct sname {
	char fullstring[OBJ_NAME_MAXLEN];

	sname(char* nameMask_, ...) {
		va_list nargs;
		va_start(nargs, nameMask_);
		vsprintf_s(fullstring, OBJ_NAME_MAXLEN, nameMask_, nargs);
		va_end(nargs);
	}

};
#define newname(mask_, ...) new sname(mask_, __VA_ARGS__)

#include <typeinfo>
struct s0 {

	sname* name;
	s0* parent;
	char parentFunc[2048];
	int stackLevel;
	int childrenCnt;
	s0* child[OBJ_MAX_CHILDREN];
	//-- debugging
	sDbgParms* dbg;
	FILE* dbgoutfile;

	char cmd[CMD_MAXLEN]; 
	
	EXPORT s0(s0parmsdef);
	EXPORT virtual ~s0();

	//void blah(s0* objVar_, const char* className_, sname* objName_, svard* objCparms_, bool verbose_, s0* parent_, const char* callerFunc_) {
	void blah(s0* objVar_, const char* className_, sname* objName_, svard* objCparms_, bool verbose_, s0* parent_, const char* callerFunc_) {

		try {
			dbg->out(DBG_MSG_INFO, callerFunc_, "TRYING  : %s = new %s(%s)", objName_->fullstring, className_, objCparms_->fullval);
			//retObj = new objType(objName_, this, objCParms_, objDbgVar_);
			dbg->out(DBG_MSG_INFO, callerFunc_, "SUCCESS : %s = new %s(%s)", objName_->fullstring, className_, objCparms_->fullval);
		}
		catch (std::exception exc) {
			dbg->out(DBG_MSG_ERR, callerFunc_, "FAILURE : %s = new %s(%s) . Exception: %s", objName_->fullstring, className_, objCparms_->fullval, exc.what());
			throw std::exception(dbg->msg);
		}
	}

	#define runcmd(cmd_) cmd;
	template <typename objType> EXPORT void _spawn(const char* parentFunc_, objType* objVar_, sname* objName_, sDbgParms* dbgParms_, svard* objCparms_) {
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", objName_->fullstring, typeid(objType).name(), objCparms_->fullval);
		try {
			dbg->out(DBG_MSG_INFO, parentFunc_, "TRYING  : %s", cmd);
			runcmd(cmd);
			dbg->out(DBG_MSG_INFO, parentFunc_, "SUCCESS : %s", cmd);
		}
		catch (std::exception exc) {
			dbg->out(DBG_MSG_ERR, parentFunc_, "FAILURE : %s . Exception: %s", cmd, exc.what());
			throw std::exception(dbg->msg);
		}
	}
/*	template <typename objType> EXPORT objType* _spawn(const char* parentFunc_, sname* objName_, sDbgParms* dbgParms_, svard* objCparms_) {
		objType* retObj=nullptr;
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", objName_->fullstring, typeid(objType).name(), objCparms_->fullval);
		try {
			dbg->out(DBG_MSG_INFO, parentFunc_, "TRYING  : %s", cmd);
			runcmd(cmd);
			dbg->out(DBG_MSG_INFO, parentFunc_, "SUCCESS : %s", cmd);
		}
		catch (std::exception exc) {
			dbg->out(DBG_MSG_ERR, parentFunc_, "FAILURE : %s . Exception: %s", cmd, exc.what());
			throw std::exception(dbg->msg);
		}
		return retObj;
	}
*/
};


#define sp0m(objType_, objName_, objCparms_){ \
	objType_* objName_ = nullptr; \
	sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", objName_->name->fullstring, typeid(objType_).name(), objCparms_->fullval); \
}
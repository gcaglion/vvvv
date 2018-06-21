#pragma once
#include "../CommonEnv.h"
#include "dbg.h"

#define OBJ_NAME_MAXLEN 128
#define OBJ_MAX_CHILDREN 64
//--
#define OBJ_PARMS_MAXCNT		32
#define OBJ_PARMS_MASK_MAXLEN	125
#define OBJ_PARMS_VAL_MAXLEN	1024

#include "svard.h"
#include <typeinfo>

struct s0 {

	char name[OBJ_NAME_MAXLEN];
	s0* parent;
	char parentFunc[2048];
	int stackLevel;
	int childrenCnt;
	s0* child[OBJ_MAX_CHILDREN];
	//-- debugging
	sDbgParms* dbg;
	FILE* dbgoutfile;
	
	EXPORT s0(s0* parent_, sDbgParms* dbg_, char* name_);
	EXPORT virtual ~s0();
	EXPORT s0(char* name_, ...);
	EXPORT void setParms(s0* parent, sDbgParms* dbg_);
	//EXPORT static char* getName(char* oName_, char* nameMask_, ...);

	 template <class objT, class ...classArgs> EXPORT objT* ___spawn(const char* callerFunc_, s0* childs0p_, sDbgParms* childDbg_, classArgs... objCargs) {

		 childs0p_->setParms(this, childDbg_);

		svard* childSvard=new svard();

		childSvard->variadic(objCargs...);
		char cmd[CMD_MAXLEN]; sprintf_s(cmd, CMD_MAXLEN, "%s = new %s(%s)", childs0p_->name, typeid(objT).name(), childSvard->fullval);

		objT* retObj;
		try {
			childs0p_->dbg=childDbg_;
			dbg->out(DBG_MSG_INFO, callerFunc_, "TRYING  : %s", cmd);
			retObj = new objT(childs0p_, objCargs...);
			dbg->out(DBG_MSG_INFO, callerFunc_, "SUCCESS : %s", cmd);
		}
		catch (std::exception exc) {
			dbg->out(DBG_MSG_ERR, callerFunc_, "FAILURE : %s . Exception: %s", cmd, exc.what());
			throw std::exception(dbg->msg);
		}
		return retObj;

	}


private:
	void setParent(s0* parent_) { parent=parent_; }
	void setDbgParms(sDbgParms* dbg_) { dbg=dbg_; }


};


#define newname(nameMask_, ...) new s0(nameMask_, __VA_ARGS__)

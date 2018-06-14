#pragma once
#include "../CommonEnv.h"
#include "../s0/s0.h"
#include "../dbg/dbg.h"

#define S1

struct s1 :s0 {
	sDbg* dbg;

	EXPORT s1(s0name* name_, s0parms* cparms_, s0* parent_, sDbg* dbg_);
	EXPORT ~s1();

	template <typename objType> EXPORT objType* safespwn1(const char* parentFunc_, char* className_, s0name* objNameVar_, s0parms* objParms_, sDbg* objDbgVar_) {
		objType* retObj=nullptr;
		try {
			dbg->out(OBJ_MSG_INFO, parentFunc_, "TRYING  : %s = new %s(%s)", objNameVar_->s, className_, objParms_->fullstring );
			retObj = new objType(objNameVar_, objParms_, this, objDbgVar_);
			dbg->out(OBJ_MSG_INFO, parentFunc_, "SUCCESS : %s = new %s(%s)", objNameVar_->s, className_, objParms_->fullstring);
		}
		catch (std::exception exc) {
			dbg->out(OBJ_MSG_ERR, parentFunc_, "FAILURE : %s = new %s(%s) . Exception: %s", objNameVar_->s, className_, objParms_->fullstring, exc.what());
			throw std::exception(dbg->msg);
		}

		return retObj;
	}

};

#define safespawn1(objname_, classname_, s0name_, s0parms_, dbg_) (objname_) = safespwn1<classname_>(__func__, #classname_, (s0name_), (s0parms_), (dbg_) );

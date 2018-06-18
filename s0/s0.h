#pragma once
#include "../CommonEnv.h"
#include "svard.h"

#define CMD_MAXLEN 4096
#define OBJ_NAME_MAXLEN 128
#define OBJ_MAX_CHILDREN 64
//--
#define OBJ_MSG_INFO 0
#define OBJ_MSG_ERR  1
#define OBJ_MSG_FAIL  2
#define OBJ_DEFAULT_VERBOSE true
//--
#define OBJ_MSG_MAXLEN		1024
#define OBJ_STACK_MAXLEN	32768
//--
#define OBJ_PARMS_MAXCNT		32
#define OBJ_PARMS_MASK_MAXLEN	125
#define OBJ_PARMS_VAL_MAXLEN	1024

#define s0parmsdef svard* name_, s0* parent_, bool verbose_
#define s0parmsval name_, parent_, verbose_

struct s0 {

	//char name[OBJ_NAME_MAXLEN];
	svard* name;
	s0* parent;
	char parentFunc[2048];
	int stackLevel;
	int childrenCnt;
	s0* child[OBJ_MAX_CHILDREN];
	//-- debugging
	bool verbose;
	char msg[OBJ_MSG_MAXLEN];
	char stack[OBJ_STACK_MAXLEN];

	EXPORT s0(s0parmsdef);
	EXPORT virtual ~s0();

	EXPORT void out(int msgtype, const char* callerFunc_, svard* msgvard);
	EXPORT void out(int msgtype, const char* callerFunc_, char* msgMask_, ...);


	template <typename objType> EXPORT objType* _spawn(const char* parentFunc_, char* className_, char* objName_, svard* objCparms_) {
		objType* retObj=nullptr;
		try {
			out(OBJ_MSG_INFO, parentFunc_, "TRYING  : %s = new %s(%s)", objName_, className_, objCparms_->fullstring);
			//retObj = new objType(objName_, this, objCParms_, objDbgVar_);
			out(OBJ_MSG_INFO, parentFunc_, "SUCCESS : %s = new %s(%s)", objName_, className_, objCparms_->fullstring);
		}
		catch (std::exception exc) {
			out(OBJ_MSG_ERR, parentFunc_, "FAILURE : %s = new %s(%s) . Exception: %s", objName_, className_, objCparms_->fullstring, exc.what());
			throw std::exception(msg);
		}
	}

};


#define s0spawn(objName_, objType, objCparms_) {}
#define s0safespawn(objName_, objType, objCparms_) {}

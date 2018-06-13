#pragma once
#include "../CommonEnv.h"

#define CMD_MAXLEN 4096
#define OBJ_NAME_MAXLEN 128
#define OBJ_MAX_CHILDREN 64
//--
#define OBJ_MSG_MAXLEN		1024
#define OBJ_STACK_MAXLEN	32768
//--
#define OBJ_PARMS_MAXCNT		32
#define OBJ_PARMS_MASK_MAXLEN	125
#define OBJ_PARMS_VAL_MAXLEN	1024

struct s0name {
	char s[OBJ_NAME_MAXLEN];

	s0name(char* nameMask_, ...) {
		va_list nameArgs;
		va_start(nameArgs, nameMask_);
		vsprintf_s(s, OBJ_NAME_MAXLEN, nameMask_, nameArgs);
		va_end(nameArgs);
	}

};

struct s0parms {
	char mask[OBJ_PARMS_MASK_MAXLEN];
	int  pcnt;
	char ptype[OBJ_PARMS_MAXCNT];	// 's', 'd', 'f', 'p'. 
	char   pvalS[OBJ_PARMS_MAXCNT][OBJ_PARMS_VAL_MAXLEN];
	int    pvalI[OBJ_PARMS_MAXCNT];
	numtype pvalF[OBJ_PARMS_MAXCNT];
	long*   pvalP[OBJ_PARMS_MAXCNT];
	char fullstring[OBJ_PARMS_MASK_MAXLEN];

	EXPORT s0parms(const char* mask_, ...);

};

struct s0 {

	s0name* name;
	s0parms* cparms;	// class-specific constructor parms
	s0* parent;
	char parentFunc[2048];
	int stackLevel;
	int childrenCnt;
	s0* child[OBJ_MAX_CHILDREN];
	char errmsg[OBJ_MSG_MAXLEN];

	EXPORT s0(s0name* name_, s0parms* cparms_, s0* parent_, bool noDelete_);
	EXPORT ~s0();

	template <typename objType> EXPORT objType* safespwn0(const char* parentFunc_, char* className_, s0name* objNameVar_, s0parms* objParms_, bool noDelete_=false) {
		objType* retObj=nullptr;
		try {
			retObj = new objType(objNameVar_, objParms_, this);
		}
		catch (std::exception exc) {
			throw exc;
		}
		return retObj;
	}

};

#define newname(mask_, ...) new s0name(mask_, __VA_ARGS__)
#define newparms(mask_, ...) new s0parms(mask_, __VA_ARGS__)
#define safespawn0(objname_, classname_, s0name_, s0parms_, nodelete_) (objname_)= safespwn0<classname_>(__func__, #classname_, (s0name_), (s0parms_), (nodelete_) );

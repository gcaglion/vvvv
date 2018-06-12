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

struct s0Name {
	char s[OBJ_NAME_MAXLEN];

	s0Name(char* nameMask_, ...) {
		va_list nameArgs;
		va_start(nameArgs, nameMask_);
		vsprintf_s(s, OBJ_NAME_MAXLEN, nameMask_, nameArgs);
		va_end(nameArgs);
	}

};

struct s0 {
	//-- generic
	//char name[OBJ_NAME_MAXLEN];
	s0Name* name;

	s0* parent;
	int stackLevel;
	int childrenCnt;
	s0* child[OBJ_MAX_CHILDREN];
	char errmsg[OBJ_MSG_MAXLEN];

	//EXPORT bool setName(char* nameMask, ...);

	EXPORT s0(s0Name* name_, s0* parent_, bool noDelete=false);
	EXPORT ~s0();


};

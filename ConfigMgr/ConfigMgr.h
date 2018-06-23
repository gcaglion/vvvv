#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLLINE_MAXLEN	1024
//--
#define XMLKEY_MAXCNT	1024
//--
#define XMLKEY_NAME_MAXLEN	1024
//--
#define XMLPARM_MAXCNT		1000
#define XMLPARM_NAME_MAXLEN	64
#define XMLPARM_VAL_MAXCNT	128
#define XMLPARM_VAL_MAXLEN	32
//--
#define XMLKEY 0
#define XMLPARM 1

struct sConfigItem: s0 {
	int type;
	FILE* parmsFile=nullptr;
	fpos_t pos;

	int childPcnt;
	sConfigItem* childP[OBJ_MAX_CHILDREN];

	EXPORT sConfigItem(s0parmsdef, FILE* parmsFile_, int type_);

	EXPORT void parse(FILE* parmsFile_);

};
struct sConfigMgr : s0 {

	FILE* parmsFile=nullptr;
	int CLoverridesCnt;
	char** CLoverride;

	sConfigItem* rootItem;

	EXPORT sConfigMgr(s0parmsdef, char* pFileFullName, int CLoverridesCnt_=0, char* CLoverride_[]=nullptr);
	EXPORT ~sConfigMgr();

};
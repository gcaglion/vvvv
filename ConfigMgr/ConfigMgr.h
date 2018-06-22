#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLLINE_MAXLEN	1024
//--
#define XMLKEY_MAXCNT	1024
//--
#define XMLKEY_NAME_MAXLEN	1024
//--
#define XMLPARM_MAXCNT		100
#define XMLPARM_NAME_MAXLEN	64
#define XMLPARM_VAL_MAXCNT	128
#define XMLPARM_VAL_MAXLEN	32
//--
struct sConfigParm : s0 {
	char pname[XMLPARM_NAME_MAXLEN];
	int  valsCnt;
	char val[XMLPARM_VAL_MAXCNT][XMLPARM_VAL_MAXLEN];

	sConfigParm(s0parmsdef, char* name_, char* fullValString_);
};
struct sConfigKey : s0 {
	char kname[XMLKEY_NAME_MAXLEN];
	sConfigParm* parm[XMLPARM_MAXCNT];
	sConfigKey* key[XMLKEY_MAXCNT];
	int parmsCnt;

	sConfigKey(s0parmsdef, char* kname_);

	void addParm(char* pname_, char* fullValString_);
};

struct sConfigMgr : s0 {

	FILE* parmsFile=nullptr;
	int CLoverridesCnt;
	char** CLoverride;

	int keysCnt=0;
	int foundParmId;

	sConfigKey* key[XMLKEY_MAXCNT];

	EXPORT sConfigMgr(s0parmsdef, char* pFileFullName, int CLoverridesCnt_=0, char* CLoverride_[]=nullptr);
	EXPORT ~sConfigMgr();

	void parse();

};
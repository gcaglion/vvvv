#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLLINE_MAXLEN	1024
//--
#define XMLKEY_MAXCNT	1024
//--
#define XMLITEMS_MAXCNT	1024
//--
#define XMLKEY_SHORTNAME_MAXLEN	64
//--
#define XMLPARM_MAXCNT		1000
#define XMLPARM_NAME_MAXLEN	64
#define XMLPARM_FULLNAME_MAXLEN	XMLKEY_NAME_MAXLEN+XMLPARM_NAME_MAXLEN
#define XMLPARM_VAL_MAXCNT	128
#define XMLPARM_VAL_MAXLEN	1024
//--
#define XMLKEY 0
#define XMLPARM 1
//--

struct sConfigFile : s0 {

};

struct sConfig :s0 {

	FILE* parmsFile;
	int CLoverridesCnt;
	char** CLoverride;

	EXPORT sConfig(s0parmsdef, const char* pFileFullName, int CLoverridesCnt_=0, char* CLoverride_[]=nullptr);
	EXPORT ~sConfig();
};

struct sConfigParm : s0 {
	char shortName[XMLKEY_SHORTNAME_MAXLEN];
	char valS[XMLPARM_VAL_MAXCNT*XMLPARM_VAL_MAXLEN];

	EXPORT sConfigParm(s0parmsdef, const char* shortName_, const char* valS_);
};

struct sConfigKey : s0 {
	char shortName[XMLKEY_SHORTNAME_MAXLEN];
	char startLabel[XMLKEY_SHORTNAME_MAXLEN];
	char endLabel[XMLKEY_SHORTNAME_MAXLEN];
	char vLine[XMLLINE_MAXLEN];

	fpos_t startPos, endPos;

	EXPORT sConfigKey(s0parmsdef, const char* shortName_);

	bool sConfigKey::gotoEnd();
};

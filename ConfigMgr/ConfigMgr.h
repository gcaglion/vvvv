#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLFILE_LINE_MAXLEN	2048
//--
#define XMLKEY_MAXCNT		1024
#define XMLKEY_PATH_MAXLEN	1024
#define XMLKEY_NAME_MAXLEN	64
#define XMLKEY_PARM_MAXCNT	32
#define XMLKEY_PARM_NAME_MAXLEN XMLKEY_NAME_MAXLEN
#define XMLKEY_PARM_VALS_MAXLEN	256

struct sCfgParm {
	//-- id props
	fpos_t pos;
	char name[XMLKEY_PARM_NAME_MAXLEN];
	char valS[XMLKEY_PARM_VALS_MAXLEN];

	sCfgParm(char* name_, char* valS_, fpos_t pos_);

};
struct sCfgKey {
	//-- id props
	fpos_t pos;
	char path[XMLKEY_PATH_MAXLEN];
	char name[XMLKEY_NAME_MAXLEN];
	char fname[XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN];
	//-- parent props
	sCfgKey* parentKey;
	//-- children props
	int parmsCnt;
	sCfgParm* parm[XMLKEY_PARM_MAXCNT];

	sCfgKey();
	sCfgKey(char* path_, char* keyLine_, fpos_t pos_, sCfgKey* parentKey_);

};

struct sCfg : s0 {
	FILE* cfgFile;
	int keysCnt;
	sCfgKey* key[XMLKEY_MAXCNT];
	sCfgKey* currentKey;

	EXPORT sCfg(s0parmsdef, const char* cfgFileFullName);

private:
	char line[XMLFILE_LINE_MAXLEN];
};

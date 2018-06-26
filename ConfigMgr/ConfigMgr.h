#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLFILE_LINE_MAXLEN	2048
//--
#define XMLKEY_MAXCNT		1024
#define XMLKEY_PATH_MAXLEN	1024
#define XMLKEY_NAME_MAXLEN	OBJ_NAME_MAXLEN
#define XMLKEY_PARM_MAXCNT	32
#define XMLKEY_PARM_NAME_MAXLEN XMLKEY_NAME_MAXLEN
#define XMLKEY_PARM_VALS_MAXLEN	256

struct sConfigFile : s0 {
	FILE* parmsFile;

	int keysCnt;
	char keyPath[XMLKEY_MAXCNT][XMLKEY_PATH_MAXLEN];
	char keyName[XMLKEY_MAXCNT][XMLKEY_NAME_MAXLEN];
	int keyParentId[XMLKEY_MAXCNT];
	int keyChildId[XMLKEY_MAXCNT][XMLKEY_MAXCNT];

	fpos_t keyPos[XMLKEY_MAXCNT];
	int  keyParmsCnt[XMLKEY_MAXCNT];
	char keyParmName[XMLKEY_MAXCNT][XMLKEY_PARM_MAXCNT][XMLKEY_PARM_NAME_MAXLEN];
	char keyParmValS[XMLKEY_MAXCNT][XMLKEY_PARM_MAXCNT][XMLKEY_PARM_VALS_MAXLEN];
	fpos_t keyParmPos;
	char line[XMLFILE_LINE_MAXLEN];

	sConfigFile(s0parmsdef, const char* pFileFullName);
};

struct sConfig :s0 {

	sConfigFile* srcFile;
	int CLoverridesCnt;
	char** CLoverride;

	EXPORT sConfig(s0parmsdef, const char* pFileFullName, int CLoverridesCnt_=0, char* CLoverride_[]=nullptr);
	EXPORT ~sConfig();
};

/*struct sConfigKey : s0 {
	char shortName[XMLKEY_SHORTNAME_MAXLEN];
	char startLabel[XMLKEY_SHORTNAME_MAXLEN];
	char endLabel[XMLKEY_SHORTNAME_MAXLEN];
	char vLine[XMLLINE_MAXLEN];

	fpos_t startPos, endPos;

	EXPORT sConfigKey(s0parmsdef, const char* shortName_);

	bool sConfigKey::gotoEnd();
};

struct sConfigParm : s0 {
	char shortName[XMLKEY_SHORTNAME_MAXLEN];
	char valS[XMLPARM_VAL_MAXCNT*XMLPARM_VAL_MAXLEN];

	EXPORT sConfigParm(s0parmsdef, const char* shortName_, const char* valS_);
};

*/
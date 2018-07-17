#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLFILE_LINE_MAXLEN	2048
//--
#define XMLKEY_MAXCNT		1024
#define XMLKEY_NAME_MAXLEN	OBJ_NAME_MAXLEN
#define XMLKEY_MAXDEPTH		OBJ_MAX_CHILDREN+XMLKEY_NAME_MAXLEN
#define XMLKEY_PATH_MAXLEN	XMLKEY_MAXDEPTH*(XMLKEY_NAME_MAXLEN+1)
#define XMLKEY_PARM_MAXCNT	OBJ_MAX_CHILDREN
#define XMLKEY_PARM_NAME_MAXLEN XMLKEY_NAME_MAXLEN
#define XMLKEY_PARM_VAL_MAXCNT	OBJ_MAX_CHILDREN
#define XMLKEY_PARM_VAL_MAXLEN	256

struct sCfgParm : s0 {
	//-- id props
	int valScnt;
	char** valS;
	sCfgParm* currentParm;

	sCfgParm(s0parmsdef, char* valS_);
	~sCfgParm();

	EXPORT void getVal(int* oVal);
	EXPORT void getVal(char** oVal);
	EXPORT void getVal(numtype* oVal);
	EXPORT void getVal(bool* oVal);
	//--
	EXPORT void getVal(int** oVal);
	EXPORT void getVal(char*** oVal);
	EXPORT void getVal(numtype** oVal);
	EXPORT void getVal(bool** oVal);

private:
	int intVar;
	char* charPVar;
	numtype numtypeVar;
	bool boolVar;
	int* intArrVar;
	char** charPArrVar;
	numtype* numtypeArrVar;
	bool* boolArrVar;
};

struct sCfgKey : s0 {

	int parmsCnt;
	//sCfgParm* currentParm;

	EXPORT sCfgKey(s0parmsdef, char* keyLine_);
	EXPORT ~sCfgKey();

};

struct sCfg : s0 {
	FILE* cfgFile;

	EXPORT static void split(const char* fullDesc, char* oKeyDesc, char* oParmDesc);

	EXPORT sCfg(s0parmsdef, const char* cfgFileFullName);
	EXPORT ~sCfg();

	EXPORT void setKey(const char* dest);

	EXPORT sDbg* newdbg(char* cfgKeyName_);

	/*template<typename T> T get(const char* fullParmName_) {
		T ret;
		char parmKey[XMLKEY_PATH_MAXLEN];
		char parmDesc[XMLKEY_NAME_MAXLEN];
		sCfgKey* bkpKey=currentKey;
		split(fullParmName_, parmKey, parmDesc);
		safecall(sCfg, this, setKey, parmKey);
		if (currentKey->findParm(parmDesc)) currentKey->currentParm->getVal(&ret);
		return ret;
	}
	*/
private:
	char line[XMLFILE_LINE_MAXLEN];
	bool buildFullKey(const char* iDest_, char* oFullDest_);
};


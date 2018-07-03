#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLFILE_LINE_MAXLEN	2048
//--
#define XMLKEY_MAXCNT		1024
#define XMLKEY_MAXDEPTH		32
#define XMLKEY_NAME_MAXLEN	64
#define XMLKEY_PATH_MAXLEN	XMLKEY_MAXDEPTH*(XMLKEY_NAME_MAXLEN+1)
#define XMLKEY_PARM_MAXCNT	32
#define XMLKEY_PARM_NAME_MAXLEN XMLKEY_NAME_MAXLEN
#define XMLKEY_PARM_VAL_MAXCNT	32
#define XMLKEY_PARM_VAL_MAXLEN	256

struct sCfgParm {
	//-- id props
	fpos_t pos;
	char name[XMLKEY_PARM_NAME_MAXLEN];
	int valScnt;
	char** valS;


	sCfgParm(char* name_, char* valS_, fpos_t pos_);
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

struct sCfgKey {
	//-- id props
	fpos_t pos;
	int depth;
	char path[XMLKEY_PATH_MAXLEN];
	char name[XMLKEY_NAME_MAXLEN];
	char fname[XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN];
	//-- parent props
	sCfgKey* parentKey;
	//-- children props
	int parmsCnt;
	sCfgParm* parm[XMLKEY_PARM_MAXCNT];
	sCfgParm* currentParm;

	sCfgKey();
	sCfgKey(sCfgKey* parentKey_, char* keyLine_, fpos_t pos_);
	EXPORT ~sCfgKey();

	EXPORT bool findParm(const char* pDesc_);

};

struct sCfg : s0 {
	FILE* cfgFile;
	int keysCnt;
	sCfgKey* key[XMLKEY_MAXCNT];
	sCfgKey* currentKey;

	EXPORT static void split(const char* fullDesc, char* oKeyDesc, char* oParmDesc);

	EXPORT sCfg(s0parmsdef, const char* cfgFileFullName);
	EXPORT ~sCfg();

	EXPORT bool findKey(const char* dest);
	EXPORT void setKey(const char* dest);

	EXPORT sDbg* newdbg(char* cfgKeyName_);

	template<typename T> T get(const char* fullParmName_) {
		T ret;
		char parmKey[XMLKEY_PATH_MAXLEN];
		char parmDesc[XMLKEY_NAME_MAXLEN];
		sCfgKey* bkpKey=currentKey;
		split(fullParmName_, parmKey, parmDesc);
		safecall(sCfg, this, setKey, parmKey);
		if (currentKey->findParm(parmDesc)) currentKey->currentParm->getVal(&ret);
		return ret;
	}

private:
	char line[XMLFILE_LINE_MAXLEN];
	bool buildFullKey(const char* iDest_, char* oFullDest_);
};

#define getParmVal(pVarName_, sCfgVarName_, pDesc_) { \
	if(typeid(pVarName_)==typeid(int)) pVarName_=sCfgVarName_->get<int>(pDesc_); \
}
	

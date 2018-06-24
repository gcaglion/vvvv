#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#define XMLLINE_MAXLEN	1024
//--
#define XMLKEY_MAXCNT	1024
//--
#define XMLITEMS_MAXCNT	1024
//--
#define XMLKEY_NAME_MAXLEN	1024
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
#define XML_MAX_RECURSION	4

struct sConfigItem : s0 {

	FILE* parmsFile;
	int CLoverridesCnt;
	char** CLoverride;

	sConfigItem* item[OBJ_MAX_CHILDREN];
	//--
	int type;
	//--
	//-- KeyDesc, ParmDesc are stored in s0::name
	//--
	EXPORT sConfigItem(s0parmsdef, int type_, char* desc_, char* val_=nullptr);
	EXPORT sConfigItem(s0parmsdef, char* pFileFullName, int CLoverridesCnt_=0, char* CLoverride_[]=nullptr);
	
	EXPORT void parse();

};
struct sConfigProps : s0 {

	FILE* parmsFile=nullptr;
	int CLoverridesCnt;
	char** CLoverride;

	int itemsCnt;
	sConfigItem* item[XMLITEMS_MAXCNT];

	int parmsCnt;
	char parmName[XMLPARM_MAXCNT][XMLPARM_NAME_MAXLEN];
	int parmValsCnt[XMLPARM_MAXCNT];
	char*** parmVal;
	int foundParmId;

	char currentKey[XMLKEY_NAME_MAXLEN];
	char soughtParmFull[XMLPARM_FULLNAME_MAXLEN];
	
	EXPORT sConfigProps(s0parmsdef, char* pFileFullName, int CLoverridesCnt_=0, char* CLoverride_[]=nullptr);
	EXPORT ~sConfigProps();

	EXPORT void parse();
	EXPORT void decode(int elementId, int* oVal);

	template <typename T> EXPORT void get(T* oVar, const char* soughtParmDesc_, int* oListLen=nullptr) {

		buildSoughtParmFull(soughtParmDesc_);

		//-- lookup parm name&val
		foundParmId=findParmId();
		if (foundParmId<0) fail("could not find parm %s. currentKey=%s", soughtParmDesc_, currentKey);

		//-- set oListLen (if passed)
		if (oListLen!=nullptr) (*oListLen)=parmValsCnt[foundParmId];
		//-- call type-specific getx(), which in turn uses Fully-qualified parameter name
		getx(oVar);

	}

	//-- type-specific: int(with or without enums), numtype, char*
	EXPORT void getx(int* oVar);
	EXPORT void getx(bool* oVar);
	EXPORT void getx(char* oVar);
	EXPORT void getx(numtype* oVar);
	//-- type-specific, arrays: int(with or without enums), numtype, char*
	EXPORT void getx(int** oVar);
	EXPORT void getx(bool** oVar);
	EXPORT void getx(char** oVar);
	EXPORT void getx(numtype** oVar);

private:
	void buildSoughtParmFull(const char* soughtParmDesc_);


}; 

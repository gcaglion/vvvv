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
#define XML_MAX_RECURSION	3

struct sConfigItem : s0 {

	FILE* parmsFile;
	fpos_t pos;
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
	
	EXPORT void parse(fpos_t* startKeyPos_);
	EXPORT void decode(int elementId, int* oVal);

	int postItemsCnt;
	fpos_t postItemPos[OBJ_MAX_CHILDREN];

	template <typename T> EXPORT void get(T* oVar, const char* soughtParmDesc_, int* oListLen=nullptr) {
	}

};

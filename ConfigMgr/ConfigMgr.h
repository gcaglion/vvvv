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
#define XMLKEY_PARM_VALS_MAXLEN	256

struct sCfgParm {
	//-- id props
	fpos_t pos;
	char name[XMLKEY_PARM_NAME_MAXLEN];
	char valS[XMLKEY_PARM_VALS_MAXLEN];


	sCfgParm(char* name_, char* valS_, fpos_t pos_);

	void get(int* oVal) {
		(*oVal)=atoi(valS);
	}
	void get(char** oVal) {
		strcpy_s((*oVal), XMLKEY_PARM_VALS_MAXLEN, valS);
	}
	void get(numtype* oVal) {
		(*oVal)=(numtype)atof(valS);
	}
	void get(bool* oVal) {
		(*oVal)=(strcmp(valS, "TRUE")==0);
	}

private:
	int intVar;
	char* charPVar;
	numtype numtypeVar;
	bool boolVar;
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

	sCfgKey();
	sCfgKey(sCfgKey* parentKey_, char* keyLine_, fpos_t pos_);
	~sCfgKey();

};

struct sCfg : s0 {
	FILE* cfgFile;
	int keysCnt;
	sCfgKey* key[XMLKEY_MAXCNT];
	sCfgKey* currentKey;

	EXPORT sCfg(s0parmsdef, const char* cfgFileFullName);
	EXPORT ~sCfg();

	EXPORT sCfgKey* setKey(const char* dest);

	template<typename T> T get(const char* fullParmName_) {
		T ret;
		bool found=false;
		bool read=false;

		char keyfname[XMLKEY_MAXDEPTH*XMLKEY_NAME_MAXLEN];
		char pname[XMLKEY_PARM_NAME_MAXLEN];

		sCfgKey* bkpKey=currentKey;
		int lastSepPos=instr('/', fullParmName_, true);
		memcpy(&keyfname[0], fullParmName_, lastSepPos); keyfname[lastSepPos]='\0';
		strcpy_s(pname, XMLKEY_PARM_NAME_MAXLEN, &fullParmName_[lastSepPos+1]); UpperCase(pname, pname);
		setKey(keyfname);
		for (int p=0; p<currentKey->parmsCnt; p++) {
			if (strcmp(pname, currentKey->parm[p]->name)==0) {
				found=true;
				currentKey->parm[p]->get(&ret);
				break;
			}
		}
		currentKey=bkpKey;

		if (found) {
			return ret;
		} else {
			fail("could not find parameter %s in key %s", fullParmName_, currentKey);
		}
	}

private:
	char line[XMLFILE_LINE_MAXLEN];
	bool findKey(const char* dest);
};

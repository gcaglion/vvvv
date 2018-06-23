#include "ConfigMgr.h"


sConfigMgr::sConfigMgr(s0parmsdef, char* pFileFullName, int CLoverridesCnt_, char* CLoverride_[]) : s0(s0parmsval) {

	CLoverridesCnt=CLoverridesCnt_; CLoverride=CLoverride_;
	//-- handle command-line overrides ...

	//-- open file
	fopen_s(&parmsFile, pFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", pFileFullName, errno);

	//-- set root item
	safespawn(rootItem, sConfigItem, newsname("RootKey"), dbg, parmsFile, XMLKEY);
	//-- recursively parse root item
	safecall(sConfigItem, rootItem, parse, parmsFile);

}
sConfigMgr::~sConfigMgr() {}

sConfigItem::sConfigItem(s0parmsdef, FILE* parmsFile_, int type_) : s0(s0parmsval) {
	parmsFile=parmsFile_; childPcnt=0; type=type_;
	info("sConfigItem %s created.", name);
	if (type==XMLKEY) safecall(sConfigItem, this, parse, parmsFile_);
}

void sConfigItem::parse(FILE* parmsFile_) {
	char vLine[XMLLINE_MAXLEN];
	size_t llen;
	char readKeyDesc[XMLKEY_NAME_MAXLEN];
	char readParmDesc[XMLPARM_NAME_MAXLEN];
	char readParmVal[XMLPARM_VAL_MAXLEN];
	char fullKey[XMLKEY_NAME_MAXLEN]="";

	while (fgets(vLine, XMLLINE_MAXLEN, parmsFile_)!=NULL) {
		//-- strip spaces & tabs
		stripChar(vLine, ' ');
		stripChar(vLine, '\t');
		stripChar(vLine, '\n');
		llen=strlen(vLine);
		if (llen==0) continue;
		//UpperCase(vLine);

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			UpperCase(readKeyDesc);
			if (strlen(fullKey)>0) strcat_s(fullKey, XMLKEY_NAME_MAXLEN, ".");
			strcat_s(fullKey, XMLKEY_NAME_MAXLEN, readKeyDesc);

			safespawn(childP[childPcnt], sConfigItem, newsname("childKey_%d_%s", childPcnt, readKeyDesc), dbg, parmsFile, XMLKEY);

		} else 	if (vLine[0]=='<' && vLine[1]=='/' && vLine[llen-1]=='>') {
			//-- key end
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[2], llen-3); readKeyDesc[llen-3]='\0';
			UpperCase(readKeyDesc);
			return;
		} else {
			//-- parameter
			if (!getValuePair(vLine, readParmDesc, readParmVal, '=')) fail("wrong parameter format <name> = <value> in line: %s", vLine);
			UpperCase(readParmDesc);
			//-- create parameter under current key
			safespawn(childP[childPcnt], sConfigItem, newsname("childP%d_name", childPcnt), dbg, parmsFile, XMLPARM);
			//--
		}

	}

}

/*
void sConfigMgr::parse() {
	char vLine[XMLLINE_MAXLEN];
	size_t llen;
	char readKeyDesc[XMLKEY_NAME_MAXLEN];
	char readParmDesc[XMLPARM_NAME_MAXLEN];
	char readParmVal[XMLPARM_VAL_MAXLEN];
	char fullKey[XMLKEY_NAME_MAXLEN]="";

	rewind(parmsFile);
	while (fgets(vLine, XMLLINE_MAXLEN, parmsFile)!=NULL) {
		//-- strip spaces & tabs
		stripChar(vLine, ' ');
		stripChar(vLine, '\t');
		stripChar(vLine, '\n');
		llen=strlen(vLine);
		if (llen==0) continue;
		//UpperCase(vLine);

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			UpperCase(readKeyDesc);
			if (strlen(fullKey)>0) strcat_s(fullKey, XMLKEY_NAME_MAXLEN, ".");
			strcat_s(fullKey, XMLKEY_NAME_MAXLEN, readKeyDesc);

			_spawn
			safespawn(key[keysCnt], sConfigKey, newsname("%s_key[%d]", name, keysCnt), dbg, fullKey);
			keysCnt++;
		} else 	if (vLine[0]=='<' && vLine[1]=='/' && vLine[llen-1]=='>') {
			//-- key end
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[2], llen-3); readKeyDesc[llen-3]='\0';
			UpperCase(readKeyDesc);

		} else {
			//-- parameter
			if (!getValuePair(vLine, readParmDesc, readParmVal, '=')) fail("wrong parameter format <name> = <value> in line: %s", vLine);
			UpperCase(readParmDesc);
			//-- add parameter full name to parmName[][]
			key[keysCnt]->addParm(readParmDesc, readParmVal);
			safecall(sConfigKey, key[keysCnt], addParm, readParmDesc, readParmVal);
		}

	}

}
*/
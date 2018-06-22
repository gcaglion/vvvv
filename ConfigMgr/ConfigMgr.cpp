#include "ConfigMgr.h"

sConfigParm::sConfigParm(s0parmsdef, char* name_, char* fullValString_) : s0(s0parmsval) {
	strcpy_s(name, XMLPARM_NAME_MAXLEN, name_);
	valsCnt=cslToArray(fullValString_, ',', (char**)val);
}
sConfigKey::sConfigKey(s0parmsdef, char* kname_) : s0(s0parmsval) {
	//-- strip fullKey of the rightmost key
	int lastDotPos=instr('.', kname_, true);
	if (lastDotPos<0) fail("Invalid key name (%s). No '.' found", kname_);
	memcpy_s(kname, XMLKEY_NAME_MAXLEN, kname_, lastDotPos);
	name[lastDotPos]='\0';
	//--
	parmsCnt=0;
}
void sConfigKey::addParm(char* pname_, char* fullValString_) {
	safespawn(parm[parmsCnt], sConfigParm, newsname("Key<%s>Parm<%s>", kname, pname_), dbg, pname_, fullValString_);
	parmsCnt++;
}


sConfigMgr::sConfigMgr(s0parmsdef, char* pFileFullName, int CLoverridesCnt_, char* CLoverride_[]) : s0(s0parmsval) {

	CLoverridesCnt=CLoverridesCnt_; CLoverride=CLoverride_;
	//-- handle command-line overrides ...

	//-- open file
	fopen_s(&parmsFile, pFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", pFileFullName, errno);

	//-- parse
	safecall(sConfigMgr, this, parse);

}
sConfigMgr::~sConfigMgr() {}

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
#include "ConfigMgr.h"

bool skipLine(char* line) {
	if (strlen(line)==0) return true;
	if (line[0]=='#') return true;
	return false;
}
void cleanLine(char* line) {
	stripChar(line, ' ');
	stripChar(line, '\t');
	stripChar(line, '\n');
}
bool isKeyStart(char* line) {
	return (line[0]=='<' && line[1]!='/' && line[strlen(line)-1]=='>');
}
bool isKeyEnd(char* line) {
	return (line[0]=='<' && line[1]=='/' && line[strlen(line)-1]=='>');
}

sCfgParm::sCfgParm(char* name_, char* valS_, fpos_t pos_) {
	pos=pos_;
	strcpy_s(name, XMLKEY_PARM_NAME_MAXLEN, name_);
	strcpy_s(valS, XMLKEY_PARM_VALS_MAXLEN, valS_);
	UpperCase(valS);
}
sCfgKey::sCfgKey() {
	pos=0;
	path[0]='\0';
	name[0]='\0';
	fname[0]='\0';
	parentKey=nullptr;
	parmsCnt=0;
}
sCfgKey::sCfgKey(char* path_, char* keyLine_, fpos_t pos_, sCfgKey* parentKey_) {
	pos=pos_;
	if (strlen(path_)==0) {
		path[0]='\0'; 
	} else {
		strcpy_s(path, XMLKEY_PATH_MAXLEN, path_);
	}
	memcpy_s(name, XMLKEY_NAME_MAXLEN, &keyLine_[1], strlen(keyLine_)-2); name[strlen(keyLine_)-2]='\0';
	sprintf_s(fname, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, "%s.%s", path, name);
	parentKey=parentKey_;
	parmsCnt=0;
}

sCfg::sCfg(s0parmsdef, const char* cfgFileFullName) : s0(s0parmsval) {

	//-- open file
	fopen_s(&cfgFile, cfgFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", cfgFileFullName, errno);

	//-- load flat Keys and Parms strings
	keysCnt=0;
	fpos_t currentPos;  
	currentKey = new sCfgKey();
	char pname[XMLKEY_PARM_NAME_MAXLEN]; char pval[XMLKEY_PARM_VALS_MAXLEN];

	while (fgets(line, XMLFILE_LINE_MAXLEN, cfgFile)!=NULL) {
		cleanLine(line);				//-- strip spaces & tabs
		if (skipLine(line)) continue;	// empty line or comment

		fgetpos(cfgFile, &currentPos);
		if (isKeyStart(line)) {
			//-- new sKey
			key[keysCnt] = new sCfgKey(currentKey->fname, line, currentPos, ((keysCnt>0) ? key[keysCnt-1] : (sCfgKey*)nullptr));
			//-- update current Key 
			currentKey=key[keysCnt];
			//-- update keysCnt
			keysCnt++;
		} else 	if (isKeyEnd(line)) {
			//-- current key becomes current key's parent
			currentKey=currentKey->parentKey;
		} else {
			//-- new sParm
			if (!getValuePair(line, pname, pval, '=')) fail("wrong parameter format: %s", line);
			currentKey->parm[currentKey->parmsCnt]= new sCfgParm(pname, pval, currentPos);
			currentKey->parmsCnt++;
		}

	}

}

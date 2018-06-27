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
	//strcpy_s(name, XMLKEY_PARM_NAME_MAXLEN, name_); 
	//strcpy_s(valS, XMLKEY_PARM_VALS_MAXLEN, valS_); UpperCase(valS);	
	UpperCase(name_, name);
	UpperCase(valS_, valS);
}
sCfgKey::sCfgKey() {
	pos=0;
	path[0]='\0';
	name[0]='\0';
	fname[0]='\0';
	parentKey=nullptr;
	parmsCnt=0;

}
sCfgKey::sCfgKey(sCfgKey* parentKey_, char* keyLine_, fpos_t pos_) {
	pos=pos_;
	parentKey=parentKey_;
	if (parentKey==nullptr) {
		path[0]='\0'; 
	}
	memcpy_s(name, XMLKEY_NAME_MAXLEN, &keyLine_[1], strlen(keyLine_)-2); name[strlen(keyLine_)-2]='\0';
	UpperCase(name, name);
	strcpy_s(path, XMLKEY_PATH_MAXLEN, parentKey->fname);
	sprintf_s(fname, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, "%s/%s", path, name);
	parmsCnt=0;
}
sCfgKey::~sCfgKey(){
	for (int p=0; p<parmsCnt; p++) delete parm[p];
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
			key[keysCnt] = new sCfgKey(currentKey, line, currentPos);
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

	//-- finally, set currentKey = root
	currentKey=key[0];
}
sCfg::~sCfg() {
	for (int k=0; k<keysCnt; k++) delete key[k];
}
void sCfg::setKey(const char* dest_) {
	char dest[XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN];
	char fname[XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN];

	UpperCase(dest_, dest);
	//-- first, establish key full name based on modifiers ('/','.', ... )
	if (dest[0]=='.' && dest[1]=='.') {
		currentKey=currentKey->parentKey;
		if (strlen(dest)>2) {
			sprintf_s(fname, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, "%s/%s", currentKey->fname, &dest[3]);
		} else {
			return;
		}
	} else if (dest[0]=='/') {
		if (strlen(dest)>1) {
			strcpy_s(fname, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, dest);
		} else {
			currentKey=key[0]->parentKey;
			return;
		}
	} else {
		sprintf_s(fname, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, "%s/%s", currentKey->fname, dest);
	}

	//-- then, find key using full name
	bool found=false;
	for (int k=0; k<keysCnt; k++) {
		if (strcmp(fname, key[k]->fname)==0) {
			currentKey = key[k];
			found=true;
			break;
		}
	}
	if (!found) fail("Key %s not found.", dest);
}

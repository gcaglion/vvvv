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
	valS=(char**)malloc(XMLKEY_PARM_VAL_MAXCNT*sizeof(char*)); for (int v=0; v<XMLKEY_PARM_VAL_MAXCNT; v++) valS[v]=(char*)malloc(XMLKEY_PARM_VAL_MAXLEN);
	UpperCase(name_, name);
	valScnt=cslToArray(valS_, ',', valS);
	for (int v=0; v<valScnt; v++) UpperCase(valS_, valS[v]);
}
sCfgParm::~sCfgParm() {
	for (int v=0; v<XMLKEY_PARM_VAL_MAXCNT; v++) free(valS[v]);
	free(valS);
}
//--
void sCfgParm::getVal(int* oVal){ return(getVal(&oVal)); }
void sCfgParm::getVal(char** oVal){ return(getVal(&oVal)); }
void sCfgParm::getVal(numtype* oVal) { return(getVal(&oVal)); }
void sCfgParm::getVal(bool* oVal){ return(getVal(&oVal)); }
//--
void sCfgParm::getVal(int** oVal){
	for (int v=0; v<valScnt; v++) {
		if (isnumber(valS[v])) {
			(*oVal[v])=atoi(valS[v]);
		} else {
			//----- decode...
		}
	}
}
void sCfgParm::getVal(char*** oVal){
	for (int v=0; v<valScnt; v++) {
		strcpy_s((*oVal[v]), XMLKEY_PARM_VAL_MAXLEN, valS[v]);
	}
}
void sCfgParm::getVal(numtype** oVal){
	for (int v=0; v<valScnt; v++) {
		(*oVal[v])=(numtype)atof(valS[v]);
	}
}
void sCfgParm::getVal(bool** oVal){
	for (int v=0; v<valScnt; v++) {
		(*oVal[v]) = (strcmp(valS[v], "TRUE")==0);
	}
}



sCfgKey::sCfgKey() {
	pos=0;
	path[0]='\0';
	depth=0;
	name[0]='\0';
	fname[0]='\0';
	parentKey=nullptr;
	parmsCnt=0;
	currentParm=nullptr;
}
sCfgKey::sCfgKey(sCfgKey* parentKey_, char* keyLine_, fpos_t pos_) {
	pos=pos_;
	parentKey=parentKey_;
	if (parentKey==nullptr) {
		path[0]='\0'; 
		depth=0;
	} else {
		depth=parentKey->depth+1;
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
bool sCfgKey::findParm(const char* pDesc_){
	char pDesc[XMLKEY_PARM_NAME_MAXLEN];
	UpperCase(pDesc_, pDesc);

	for (int p=0; p<parmsCnt; p++) {
		if (strcmp(pDesc, parm[p]->name)==0) {
			currentParm=parm[p];
			return true;
		}
	}
	return false;
}

sCfg::sCfg(s0parmsdef, const char* cfgFileFullName) : s0(s0parmsval) {

	//-- open file
	fopen_s(&cfgFile, cfgFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", cfgFileFullName, errno);

	//-- load flat Keys and Parms strings
	keysCnt=0;
	fpos_t currentPos;  
	currentKey = new sCfgKey();
	char pname[XMLKEY_PARM_NAME_MAXLEN];
	char pvalFull[XMLKEY_PARM_VAL_MAXCNT*XMLKEY_PARM_VAL_MAXLEN];

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
			if (!getValuePair(line, pname, pvalFull, '=')) fail("wrong parameter format: %s", line);
			UpperCase(pvalFull, pvalFull);
			currentKey->parm[currentKey->parmsCnt]= new sCfgParm(pname, pvalFull, currentPos);
			currentKey->parmsCnt++;
			currentKey->currentParm++;
		}

	}

	//-- finally, set currentKey = root
	currentKey=key[0];
}
sCfg::~sCfg() {
	for (int k=0; k<keysCnt; k++) delete key[k];
}

bool sCfg::buildFullKey(const char* iDest_, char* oFullDest_) {
	bool found=false;

	//-- first, establish key full name based on modifiers ('/','.', ... )
	if (iDest_[0]=='.' && iDest_[1]=='.') {
		currentKey=currentKey->parentKey;
		if (strlen(iDest_)>2) {
			sprintf_s(oFullDest_, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, "%s/%s", currentKey->fname, &iDest_[3]);
		} else {
			found=true;
		}
	} else if (iDest_[0]=='/') {
		if (strlen(iDest_)>1) {
			strcpy_s(oFullDest_, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, iDest_);
		} else {
			currentKey=key[0]->parentKey;
			found=true;
		}
	} else {
		sprintf_s(oFullDest_, XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN, "%s/%s", currentKey->fname, iDest_);
	}
	return found;
}

bool sCfg::findKey(const char* dest_) {
	char dest[XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN];
	char fname[XMLKEY_PATH_MAXLEN+XMLKEY_NAME_MAXLEN];

	UpperCase(dest_, dest);
	if (strcmp(dest, currentKey->fname)==0) return true;

	//-- first, establish key full name based on modifiers ('/','.', ... ), then, find key using full name
	bool found=buildFullKey(dest, fname);
	if(!found) {
		for (int k=0; k<keysCnt; k++) {
			if (strcmp(fname, key[k]->fname)==0) {
				currentKey = key[k];
				found=true;
				break;
			}
		}
	}
	return found;
}
void sCfg::setKey(const char* dest) {
	if (!findKey(dest)) fail("could not find Key %s . currentKey = %s", dest, currentKey->fname);
}

void sCfg::split(const char* fullDesc, char* oKeyDesc, char* oParmDesc) {
	int lastDotPos=instr('/', fullDesc, true);
	if (lastDotPos<0) {
		oKeyDesc[0]='\0';
		strcpy_s(oParmDesc, XMLKEY_PARM_NAME_MAXLEN, fullDesc);
	} else {
		memcpy_s(oKeyDesc, XMLKEY_PARM_NAME_MAXLEN, fullDesc, lastDotPos);
		oKeyDesc[lastDotPos]='\0';
		memcpy_s(oParmDesc, XMLKEY_NAME_MAXLEN, &fullDesc[lastDotPos+1], strlen(fullDesc)-lastDotPos);
		oParmDesc[strlen(fullDesc)-lastDotPos]='\0';
	}
}
sDbg* sCfg::newdbg(char* cfgKeyName_) {

	//-- prepare sDbg defaults
	bool verbose_=DEFAULT_DBG_VERBOSITY; bool dbgtoscreen_=DEFAULT_DBG_TO_SCREEN; bool dbgtofile_=DEFAULT_DBG_TO_FILE; char* outfilepath_=DEFAULT_DBG_FPATH;
	//-- this is needed because...
	char outfilepath[XMLKEY_PARM_VAL_MAXLEN]; strcpy_s(outfilepath, XMLKEY_PARM_VAL_MAXLEN, outfilepath_);
	char* dioporco=&outfilepath[0];
	//-- backup currentKey
	sCfgKey* bkpKey=currentKey;
	//-- go to child Key
	setKey(cfgKeyName_);
	//-- find <Debugger> key
	if (findKey("Debugger")) {
		//-- if found, override default values
		if (currentKey->findParm("Verbose")) currentKey->currentParm->getVal(&verbose_);
		if (currentKey->findParm("ScreenOutput")) currentKey->currentParm->getVal(&dbgtoscreen_);
		if (currentKey->findParm("FileOutput")) currentKey->currentParm->getVal(&dbgtofile_);
		if (currentKey->findParm("OutputFileFullName")) currentKey->currentParm->getVal(&dioporco);
	}
	//-- restore original key
	currentKey=bkpKey;

	//-- spawn and return new debugger
	return (new sDbg(verbose_, dbgtoscreen_, dbgtofile_, outfilepath));

}

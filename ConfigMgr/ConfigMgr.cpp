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

sCfgParm::sCfgParm(s0parmsdef, char* parmLine_) : s0(s0parmsval) {

	valS=(char**)malloc(XMLKEY_PARM_VAL_MAXCNT*sizeof(char*)); for (int v=0; v<XMLKEY_PARM_VAL_MAXCNT; v++) valS[v]=(char*)malloc(XMLKEY_PARM_VAL_MAXLEN);
	int tmp=cslToArray(parmLine_, '=', valS);
	if(tmp!=2) fail("wrong parameter format: %s", parmLine_);
	valScnt=cslToArray(valS[0], ',', valS);
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



sCfgKey::sCfgKey(s0parmsdef, char* keyLine_) : s0(s0parmsval) {

	memcpy_s(name, XMLKEY_NAME_MAXLEN, &keyLine_[1], strlen(keyLine_)-2); name[strlen(keyLine_)-2]='\0';
	parmsCnt=childrenCnt;

}
sCfgKey::~sCfgKey(){}

sCfg::sCfg(s0parmsdef, const char* cfgFileFullName) : s0(s0parmsval) {

	//-- open file
	fopen_s(&cfgFile, cfgFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", cfgFileFullName, errno);

	while (fgets(line, XMLFILE_LINE_MAXLEN, cfgFile)!=NULL) {
		cleanLine(line);				//-- strip spaces & tabs
		if (skipLine(line)) continue;	// empty line or comment

		if (isKeyStart(line)) {
			//-- new sKey
			safespawn(currentChild, sCfgKey, newsname("tempKeyName"), dbg, line);

		} else 	if (isKeyEnd(line)) {
			//-- current key becomes current key's parent
			currentChild=currentChild->parent;
		} else {
			//-- new sParm
			safespawn(currentChild, sCfgParm, newsname("key[%d]->parm[%d]"), dbg, line);
		}

	}

	//-- finally, set currentKey = root
	currentChild=child[0];
}

sCfg::~sCfg() {}

void sCfg::setKey(const char* dest) {
	if (!findChild(dest)) fail("could not find Key %s . currentKey = %s", dest, currentChild->fullName);
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
	char outfilepath[MAX_PATH]; strcpy_s(outfilepath, MAX_PATH, outfilepath_); char* outfileP=&outfilepath[0];

	//-- backup currentKey
	s0* bkpKey=currentChild;
	//-- go to child Key
	setKey(cfgKeyName_);
	//-- find <Debugger> key
	if (findChild("Debugger")) {
		//-- if found, override default values
		if (findChild("Verbose")) (((sCfgParm*)currentChild))->getVal(&verbose_);
		if (findChild("ScreenOutput")) ((sCfgParm*)currentChild)->getVal(&dbgtoscreen_);
		if (findChild("FileOutput")) ((sCfgParm*)currentChild)->getVal(&dbgtofile_);
		if (findChild("OutFilePath")) ((sCfgParm*)currentChild)->getVal(&outfileP);
	}
	//-- restore original key
	currentChild=bkpKey;

	//-- spawn and return new debugger
	return (new sDbg(verbose_, dbgtoscreen_, dbgtofile_, outfileP));

}

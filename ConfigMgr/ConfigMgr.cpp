#include "ConfigMgr.h"

bool isValid(char* pLine) {
	stripChar(pLine, ' ');
	stripChar(pLine, '\t');
	stripChar(pLine, '\n');
	if (strlen(pLine)==0) return false;
	if (pLine[0]=='#') return false;
	return true;
}
bool stripLastStep(char* fullDesc, char* oStrippedDesc) {
	int lastDotPos=instr('.', fullDesc, true);
	if (lastDotPos<0) return false;
	memcpy_s(oStrippedDesc, strlen(fullDesc), fullDesc, lastDotPos);
	oStrippedDesc[lastDotPos]='\0';
	return true;
}

sConfigProps::sConfigProps(s0parmsdef, char* pFileFullName, int CLoverridesCnt_, char* CLoverride_[]) : s0(s0parmsval) {

	itemsCnt=0;
	parmsCnt=0;
	
	CLoverridesCnt=CLoverridesCnt_; CLoverride=CLoverride_;
	//-- handle command-line overrides ...

	//-- malloc parmsvals
	parmVal=(char***)malloc(XMLPARM_MAXCNT*sizeof(char**));
	for (int p=0; p<XMLPARM_MAXCNT; p++) {
		parmVal[p]=(char**)malloc(XMLPARM_VAL_MAXCNT*sizeof(char*));
		for (int e=0; e<XMLPARM_VAL_MAXCNT; e++) {
			parmVal[p][e]=(char*)malloc(XMLPARM_VAL_MAXLEN);
		}
	}
	
	//-- open file
	fopen_s(&parmsFile, pFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", pFileFullName, errno);

	//-- parse
	safecall(sConfigProps, this, parse);

}
sConfigProps::~sConfigProps() {
	for (int p=0; p<XMLPARM_MAXCNT; p++) {
		for (int e=0; e<XMLPARM_VAL_MAXCNT; e++) {
			free(parmVal[p][e]);
		}
		free(parmVal[p]);
	}
	free(parmVal);

}

void sConfigProps::parse() {
	char vLine[XMLLINE_MAXLEN];
	size_t llen;
	char readKeyDesc[XMLKEY_NAME_MAXLEN];
	char readParmDesc[XMLPARM_NAME_MAXLEN];
	char readParmVal[XMLPARM_VAL_MAXCNT*XMLPARM_VAL_MAXLEN];

	char fullKey[XMLKEY_NAME_MAXLEN]="";

	//rewind(parmsFile);
	while (fgets(vLine, XMLLINE_MAXLEN, parmsFile)!=NULL) {
		//-- strip spaces & tabs
		stripChar(vLine, ' ');
		stripChar(vLine, '\t');
		stripChar(vLine, '\n');
		llen=strlen(vLine);
		if (llen==0) continue;
		if (vLine[0]=='#') continue;	// comment

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			UpperCase(readKeyDesc);
			if (strlen(fullKey)>0) strcat_s(fullKey, XMLKEY_NAME_MAXLEN, ".");
			strcat_s(fullKey, XMLKEY_NAME_MAXLEN, readKeyDesc);
			safespawn(item[itemsCnt], sConfigItem, newsname(readKeyDesc), dbg, XMLKEY, readKeyDesc);
		} else 	if (vLine[0]=='<' && vLine[1]=='/' && vLine[llen-1]=='>') {
			//-- key end
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[2], llen-3); readKeyDesc[llen-3]='\0';
			UpperCase(readKeyDesc);
			//-- strip fullKey of the rightmost key
			stripLastStep(fullKey, fullKey);
		} else {
			//-- parameter
			if (!getValuePair(vLine, readParmDesc, readParmVal, '=')) fail("wrong parameter format: %s", readParmVal);
			UpperCase(readParmDesc);
			safespawn(item[itemsCnt], sConfigItem, newsname(readParmDesc), dbg, XMLPARM, readParmDesc, readParmVal);

		}

	}

}
void sConfigProps::buildSoughtParmFull(const char* soughtParmDesc_) {
	char soughtKey[XMLKEY_NAME_MAXLEN];
	if (soughtParmDesc_[0]=='.'||strlen(currentKey)==0) {
		soughtKey[0]='\0';
	} else {
		strcpy_s(soughtKey, XMLKEY_NAME_MAXLEN, currentKey);
		strcat_s(soughtKey, ".");
	}
	strcpy_s(soughtParmFull, XMLKEY_NAME_MAXLEN, soughtKey);
	strcat_s(soughtParmFull, soughtParmDesc_);
	UpperCase(soughtParmFull);
}

//-- specific, single value: int(with or without enums), numtype, char*
void sConfigProps::getx(int* oVar) {
	getx(&oVar);
}
void sConfigProps::getx(bool* oVar) {
	getx(&oVar);
}
void sConfigProps::getx(char* oVar) {
	getx(&oVar);
}
void sConfigProps::getx(numtype* oVar) {
	getx(&oVar);
}

//-- specific, arrays: int(with or without enums), numtype, char*
void sConfigProps::getx(int** oVar) {
	for (int e=0; e<parmValsCnt[foundParmId]; e++) {
		if (isnumber(parmVal[foundParmId][e])) {
			(*oVar)[e]=atoi(parmVal[foundParmId][e]);
		} else {
			safecall(sConfigProps, this, decode,e, &oVar[0][e]);
		}
	}
}
void sConfigProps::getx(bool** oVar) {
	for (int e=0; e<parmValsCnt[foundParmId]; e++) {
		UpperCase(parmVal[foundParmId][e]);
		(*oVar)[e]=(strcmp(parmVal[foundParmId][e], "TRUE")==0);
	}
}
void sConfigProps::getx(char** oVar) {
	for (int e=0; e<parmValsCnt[foundParmId]; e++) {
		for (int i=0; i<strlen(oVar[e]); i++) oVar[e][i]=parmVal[foundParmId][e][i];
		//memcpy_s(oVar[e], strlen(oVar[e])+1, parmVal[foundParmId][e], XML_MAX_PARAM_VAL_LEN);
		//strcpy_s(oVar[e], strlen(oVar[e])+1, parmVal[foundParmId][e]);
		//strcpy(oVar[e], parmVal[foundParmId][e]);
		//strcpy_s(oVar[e], XML_MAX_PARAM_VAL_LEN, parmVal[foundParmId][e]);
	}
}
void sConfigProps::getx(numtype** oVar) {
	for (int e=0; e<parmValsCnt[foundParmId]; e++) {
		(*oVar)[e]=(numtype)atof(parmVal[foundParmId][e]);
	}
}

sConfigItem::sConfigItem(s0parmsdef, int type_, char* desc_, char* val_) : s0(s0parmsval) {
	type=type_;
	parmsFile=((sConfigItem*)parent)->parmsFile;

	//-- parse
	if(type==XMLKEY) safecall(sConfigItem, this, parse);

}
sConfigItem::sConfigItem(s0parmsdef, char* pFileFullName, int CLoverridesCnt_, char* CLoverride_[]) : s0(s0parmsval) {

	CLoverridesCnt=CLoverridesCnt_; CLoverride=CLoverride_;
	//-- handle command-line overrides ...

	//-- open file
	fopen_s(&parmsFile, pFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", pFileFullName, errno);

	//-- parse
	safecall(sConfigItem, this, parse);

}
void sConfigItem::parse() {

	size_t llen;
	char vLine[XMLLINE_MAXLEN];
	char readKeyDesc[XMLKEY_NAME_MAXLEN];
	char readParmDesc[XMLPARM_NAME_MAXLEN];
	char readParmVal[XMLPARM_VAL_MAXCNT*XMLPARM_VAL_MAXLEN];
	char fullKey[XMLKEY_NAME_MAXLEN]="";

	while (fgets(vLine, XMLLINE_MAXLEN, parmsFile)!=NULL) {
		//-- strip spaces & tabs
		stripChar(vLine, ' ');
		stripChar(vLine, '\t');
		stripChar(vLine, '\n');
		llen=strlen(vLine);
		if (llen==0) continue;			// empty line
		if (vLine[0]=='#') continue;	// comment

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			UpperCase(readKeyDesc);
			if (strlen(fullKey)>0) strcat_s(fullKey, XMLKEY_NAME_MAXLEN, ".");
			strcat_s(fullKey, XMLKEY_NAME_MAXLEN, readKeyDesc);
			safespawn(item[childrenCnt], sConfigItem, newsname(readKeyDesc), dbg, XMLKEY, readKeyDesc);
		} else 	if (vLine[0]=='<' && vLine[1]=='/' && vLine[llen-1]=='>') {
			//-- key end
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[2], llen-3); readKeyDesc[llen-3]='\0';
			UpperCase(readKeyDesc);
			//-- strip fullKey of the rightmost key
			stripLastStep(fullKey, fullKey);
		} else {
			//-- parameter
			if (!getValuePair(vLine, readParmDesc, readParmVal, '=')) fail("wrong parameter format: %s", readParmVal);
			UpperCase(readParmDesc);
			safespawn(item[childrenCnt], sConfigItem, newsname(readParmDesc), dbg, XMLPARM, readParmDesc, readParmVal);

		}

	}

}

#include "ConfigMgr.h"


sConfigProps::sConfigProps(s0parmsdef, char* pFileFullName, int CLoverridesCnt_, char* CLoverride_[]) : s0(s0parmsval) {

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

void sConfigProps::parse() {
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
		if (vLine[0]=='#') continue;	// comment

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			UpperCase(readKeyDesc);
			if (strlen(fullKey)>0) strcat_s(fullKey, XMLKEY_NAME_MAXLEN, ".");
			strcat_s(fullKey, XMLKEY_NAME_MAXLEN, readKeyDesc);
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
			//-- add parameter full name to parmName[][]
			strcpy_s(parmName[parmsCnt], XMLKEY_NAME_MAXLEN, fullKey);
			strcat_s(parmName[parmsCnt], XMLKEY_NAME_MAXLEN, ".");
			strcat_s(parmName[parmsCnt], XMLKEY_NAME_MAXLEN, readParmDesc);
			//-- also add parameter value[s] split array parameters
			parmValsCnt[parmsCnt]=cslToArray(readParmVal, ',', parmVal[parmsCnt]);
			parmsCnt++;
		}

	}

}

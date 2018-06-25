#include "ConfigMgr.h"

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

bool skipLine(char* line) {
	if (strlen(line)==0) return true;
	if (line[0]=='#') return true;
	return false;
}
void cleanLine(char* line){
	stripChar(line, ' ');
	stripChar(line, '\t');
	stripChar(line, '\n');
}
void sConfigItem::parse() {

	size_t llen;
	char vLine[XMLLINE_MAXLEN];
	char readKeyDesc[XMLKEY_NAME_MAXLEN];
	char readParmDesc[XMLPARM_NAME_MAXLEN];
	char readParmVal[XMLPARM_VAL_MAXCNT*XMLPARM_VAL_MAXLEN];

	while (fgets(vLine, XMLLINE_MAXLEN, parmsFile)!=NULL) {
		cleanLine(vLine);	//-- strip spaces & tabs
		if (skipLine(vLine)) continue;			// empty line or comment
		llen=strlen(vLine);

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			UpperCase(readKeyDesc);
			//-- save key start position 
			safespawn(item[childrenCnt], sConfigItem, newsname("%s.%s", name, readKeyDesc), dbg, XMLKEY, name);
		} else 	if (vLine[0]=='<' && vLine[1]=='/' && vLine[llen-1]=='>') {
			//-- key end
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[2], llen-3); readKeyDesc[llen-3]='\0';
			UpperCase(readKeyDesc);
			return;
		} else {
			//-- parameter
			if (!getValuePair(vLine, readParmDesc, readParmVal, '=')) fail("wrong parameter format: %s", readParmVal);
			UpperCase(readParmDesc);
			safespawn(item[childrenCnt], sConfigItem, newsname("%s.%s", name, readParmDesc), dbg, XMLPARM, readParmDesc, readParmVal);			
		}

	}

}

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
bool isParm(char* line) {
	return (!isKeyStart(line) && !isKeyEnd(line));
}

sConfigFile::sConfigFile(s0parmsdef, const char* pFileFullName) : s0(s0parmsval) {
	int llen;

	//-- open file
	fopen_s(&parmsFile, pFileFullName, "r");
	if (errno!=0) fail("Could not open configuration file %s . Error %d", pFileFullName, errno);

	//-- load flat Keys and Parms strings
	keysCnt=0;
	char currentPath[XMLKEY_PATH_MAXLEN]=".";
	int currentKey=0;

	while (fgets(line, XMLFILE_LINE_MAXLEN, parmsFile)!=NULL) {
		cleanLine(line);				//-- strip spaces & tabs
		if (skipLine(line)) continue;	// empty line or comment
		llen=(int)strlen(line);

		//-- set current XML path

		if (line[0]=='<' && line[1]!='/' && line[llen-1]=='>') {
			//-- key start
			
			//-- set KeyPath = currentPath
			strcpy_s(keyPath[keysCnt], XMLKEY_PATH_MAXLEN, currentPath);
			//-- set KeyName
			memcpy_s(keyName[keysCnt], XMLKEY_NAME_MAXLEN, &line[1], llen-2); keyName[keysCnt][llen-2]='\0';
			//-- set Key parent
			keyParentId[keysCnt]=keysCnt;
			//-- save key start position 
			fgetpos(parmsFile, &keyPos[keysCnt]);
			//-- update current path 
			strcat_s(currentPath, XMLKEY_PATH_MAXLEN, keyName[keysCnt]); strcat_s(currentPath, XMLKEY_PATH_MAXLEN, ".");

			//-- reset keyParmsCnt
			keyParmsCnt[keysCnt]=0;
			//-- update current Key 
			currentKey=keysCnt;

			//-- update keysCnt
			keysCnt++;

		} else 	if (line[0]=='<' && line[1]=='/' && line[llen-1]=='>') {
			//-- key end

			//-- set currentPath one level up
			currentPath[instr('.', currentPath, true)]='\0';
			currentPath[instr('.', currentPath, true)+1]='\0';
			//-- current key becomes current key's parent
			currentKey=keyParentId[keysCnt-1];

		} else {
			//-- parameter

			if (!getValuePair(line, keyParmName[keysCnt-1][keyParmsCnt[keysCnt-1]], keyParmValS[keysCnt-1][keyParmsCnt[keysCnt-1]], '=')) fail("wrong parameter format: %s", keyParmValS[keysCnt-1][keyParmsCnt[keysCnt-1]]);
			UpperCase(keyParmValS[keysCnt-1][keyParmsCnt[keysCnt-1]]);
			//--
			//safespawn(item[childrenCnt], sConfigItem, newsname("%s.%s", name, readParmDesc), dbg, XMLPARM, keyParmName[keysCnt][keyParmsCnt[keysCnt]], keyParmValS[keysCnt][keyParmsCnt[keysCnt]]);
		}

	}


}

sConfig::sConfig(s0parmsdef, const char* pFileFullName, int CLoverridesCnt_, char* CLoverride_[]) : s0(s0parmsval) {

	//-- open parameters file, and load all keys and parms
	safespawn(srcFile, sConfigFile, newsname("%s_cfgFile", name), dbg, pFileFullName);

	//-- handle command-line overrides ...
	CLoverridesCnt=CLoverridesCnt_; CLoverride=CLoverride_;

	//-- create Keys and Parms
	for (int k=0; k<srcFile->keysCnt; k++) {

	}

}
sConfig::~sConfig() {}
/*
sConfigParm::sConfigParm(s0parmsdef, const char* shortName_, const char* valS_) : s0(s0parmsval) {
	strcpy_s(shortName, XMLKEY_SHORTNAME_MAXLEN, shortName_);
	strcpy_s(valS, XMLPARM_VAL_MAXCNT*XMLPARM_VAL_MAXLEN, valS_);
}

bool sConfigKey::gotoEnd(){
	while (fgets(vLine, XMLLINE_MAXLEN, ((sConfig*)parent)->parmsFile)!=NULL) {
		if (strcmp(vLine, endLabel)==0) {
			fgetpos(((sConfig*)parent)->parmsFile, &endPos);
			return true;
		}
	}
	return false;
}

sConfigKey::sConfigKey(s0parmsdef, const char* shortName_) : s0(s0parmsval) {
	strcpy_s(shortName, XMLKEY_SHORTNAME_MAXLEN, shortName_);
	sprintf_s(startLabel, XMLKEY_SHORTNAME_MAXLEN, "<%s>", shortName);
	sprintf_s(endLabel, XMLKEY_SHORTNAME_MAXLEN, "</%s>", shortName);

	//-- startPos is current file pos
	fgetpos(((sConfig*)parent)->parmsFile, &startPos);
	//-- to set endPos, we need to find end label </...>
	if (!gotoEnd()) fail("Key %s is not closed", startLabel);


}

*/

/*sConfigItem::sConfigItem(s0parmsdef, int type_, const char* shortName_, const char* parmValS_) : s0(s0parmsval) {
	type=type_;
	strcpy_s(shortName, XMLKEY_SHORTNAME_MAXLEN, shortName_);
	parmsFile=((sConfigItem*)parent)->parmsFile;
	//-- startPos is current file pos
	fgetpos(parmsFile, &startPos);
	//-- to set endPos, we need to find end label </...>
	char endLabel[XMLKEY_SHORTNAME_MAXLEN];
	sprintf_s(endLabel, XMLKEY_SHORTNAME_MAXLEN, "</%s>", shortName);
	//-- if this is a key, look for, and create all parameters under this key
	if (type==XMLKEY) {
		while (fgets(vLine, XMLLINE_MAXLEN, parmsFile)!=NULL) {
			cleanLine(vLine);						//-- strip spaces & tabs
			if (skipLine(vLine)) continue;			// empty line or comment
			//llen=strlen(vLine);

			if (isParm(vLine)) {
				if (!getValuePair(vLine, readParmDesc, readParmVal, '=')) fail("wrong parameter format: %s", readParmVal);
				safespawn(item[childrenCnt], sConfigItem, newsname("%s.%s", name, readParmDesc), dbg, XMLPARM, readParmDesc, readParmVal);
			}
			//-- then look for section end label, end exit
			if (strcmp(vLine, endLabel)==0) {
				//-- set endPos and exit
				fsetpos(parmsFile, &endPos);
				return;
			}
		}
		fail("end label %s not found", endLabel);
	}

}
*/
/*void sConfigItem::parse(fpos_t startPos_) {

	rewind(parmsFile);
	fsetpos(parmsFile, &startPos_);
	while (fgets(vLine, XMLLINE_MAXLEN, parmsFile)!=NULL) {
		cleanLine(vLine);	//-- strip spaces & tabs
		if (skipLine(vLine)) continue;			// empty line or comment
		llen=strlen(vLine);

		if (vLine[0]=='<' && vLine[1]!='/' && vLine[llen-1]=='>') {
			//-- key start
			memcpy_s(readKeyDesc, XMLKEY_NAME_MAXLEN, &vLine[1], llen-2); readKeyDesc[llen-2]='\0';
			//-- save key start position 
			fgetpos(parmsFile, &startPos);
			//-- create key
			safespawn(item[childrenCnt], sConfigItem, newsname("%s.%s", name, readKeyDesc), dbg, XMLKEY, name);
			//-- find and save
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
*/
#include "s1.h"

sDbg* s1::newCfgDbg(sCfg* cfgSet_, char* cfgKeyName_) {

	//-- prepare sDbg defaults
	bool verbose_=DEFAULT_DBG_VERBOSITY; bool dbgtoscreen_=DEFAULT_DBG_TO_SCREEN; bool dbgtofile_=DEFAULT_DBG_TO_FILE; char* outfilepath_=DEFAULT_DBG_FPATH;
	//-- backup currentKey
	sCfgKey* bkpKey=cfgSet_->currentKey;
	//-- go to child Key
	cfgSet_->setKey(cfgKeyName_);
	//-- find <Debugger> key
	if (cfgSet_->findKey("Debugger")) {
		//-- if found, override default values
		if (cfgSet_->currentKey->findParm("Verbose")) cfgSet_->currentKey->currentParm->getVal(&verbose_);
		if (cfgSet_->currentKey->findParm("ScreenOutput")) cfgSet_->currentKey->currentParm->getVal(&dbgtoscreen_);
		if (cfgSet_->currentKey->findParm("FileOutput")) cfgSet_->currentKey->currentParm->getVal(&dbgtofile_);
		if (cfgSet_->currentKey->findParm("OutputFileFullName")) cfgSet_->currentKey->currentParm->getVal(&outfilepath_);
	}
	//-- restore original key
	cfgSet_->currentKey=bkpKey;

	//-- spawn and return new debugger
	return (new sDbg(verbose_, dbgtoscreen_, dbgtofile_, outfilepath_));

}

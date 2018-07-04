#include "s0.h"

sName::sName(char* nameMask_, ...) {
	va_list va_args;
	va_start(va_args, nameMask_);
	vsprintf_s(s, OBJ_NAME_MAXLEN, nameMask_, va_args);
	va_end(va_args);
	stripChar(s, ' ');
}

s0::s0(s0parmsdef){

	//-- 1. sets class-specific constructor parameters.
	parent=parent_; childrenCnt=0;
	strcpy_s(name, OBJ_NAME_MAXLEN, sname_->s);
	delete sname_;

	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
	}

	if (dbg_==nullptr) {
		dbg=new sDbg(DEFAULT_DBG_VERBOSITY, DEFAULT_DBG_TO_SCREEN, DEFAULT_DBG_TO_FILE, DEFAULT_DBG_FPATH);
		dbg->stackLevel=stackLevel;
		if (dbg->dbgtofile && dbg->outfile==nullptr) dbg->createOutFile(name, this);
	} else {
		dbg=dbg_;
	}

}

s0::~s0() {
	 for (int c=childrenCnt-1; c>=0; c--) {
		 delete child[c];
	 }
	 delete dbg;
 }

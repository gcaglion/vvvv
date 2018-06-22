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

	//-- create new sDbgParms* object inside s0 constructor, and copy dbg_ parms into it
	dbg=new sDbg(*dbg_);
	//-- we can now delete dbg_
	delete dbg_;
	//-- sets dbg stackLevel and creates dbg outfile AFTER dbg creation, to get s0 object name
	dbg->stackLevel=stackLevel;
	if (dbg->destfile) dbg->createOutFile(name, this);

}

s0::~s0() {
	 for (int c=childrenCnt-1; c>=0; c--) {
		 delete child[c];
	 }
	 delete dbg;
 }

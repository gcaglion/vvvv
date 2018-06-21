#include "s0.h"

s0::s0(s0* parent_, sDbgParms* dbg_, char* name_) {

	//-- 1. sets class-specific constructor parameters.
	parent=parent_; dbg=dbg_; ; childrenCnt=0;
	strcpy_s(name, OBJ_NAME_MAXLEN, name_);

	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		parent->child[parent->childrenCnt]=this;
		parent->childrenCnt++;
	}

	//-- sets dbg stackLevel and creates dbg outfile AFTER dbg creation, to get s0 object name
	dbg->stackLevel=stackLevel;
	if (dbg->destfile) dbg->createOutFile(name, this);

}


s0::s0(char* nameMask_, ...) {
	va_list va_args;
	va_start(va_args, nameMask_);
	vsprintf_s(name, OBJ_NAME_MAXLEN, nameMask_, va_args);
	va_end(va_args);
}

s0::~s0() {
	 for (int c=childrenCnt-1; c>=0; c--) {
		 delete child[c];
	 }

 }

void s0::setParms(s0* parent_, sDbgParms* dbg_) {
	parent=parent_; dbg=dbg_; ; childrenCnt=0;

	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		parent->child[parent->childrenCnt]=this;
		parent->childrenCnt++;
	}

	//-- sets dbg stackLevel and creates dbg outfile AFTER dbg creation, to get s0 object name
	dbg->stackLevel=stackLevel;
	if (dbg->destfile) dbg->createOutFile(name, this);

}
#include "s0.h"

s0::s0(s0parmsdef) {

	//-- 1. sets class-specific constructor parameters.
	name=name_; parent=parent_; childrenCnt=0; dbg=dbg_;
	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		parent->child[parent->childrenCnt]=this;
		parent->childrenCnt++;
	}

	//-- sets dbg stackLevel and creates dbg outfile AFTER dbg creation, to get s0 object name
	dbg->stackLevel=stackLevel;
	if(dbg->destfile) dbg->createOutFile(name->fullstring, this);

}

 s0::~s0() {
	for (int c=childrenCnt-1; c>=0; c--) {
		delete child[c];
	}

}

 
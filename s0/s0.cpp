#include "s0.h"

s0::s0(s0Name* name_, s0* parent_, bool noDelete) {

	name=name_; parent=parent_; childrenCnt=0;
	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		if (!noDelete) {
			parent->child[parent->childrenCnt]=this;
			parent->childrenCnt++;
		}
	}

}

s0::~s0() {
	for (int c=childrenCnt-1; c>=0; c--) {
		delete child[c];
	}

}

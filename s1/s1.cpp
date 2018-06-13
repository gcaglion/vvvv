#include "s1.h"


s1::s1(s0name* name_, s0parms* cparms_, s0* parent_, sDbg* dbg_) : s0(name_, cparms_, parent_) {

	//-- sets dbg
	if (dbg_==nullptr) {
		safespawn0(dbg, sDbg, new s0name("%s_Dbg", name->s), new s0parms(""));
	} else {
		dbg=dbg_;
	}
}

s1::~s1() {
}

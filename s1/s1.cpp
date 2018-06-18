#include "s1.h"


s1::s1(s0parmsdef, sDbg* dbg_) : s0(s0parmsval) {

	//-- sets dbg
	if (dbg_==nullptr) {
		safespawn0(dbg, sDbg, new s0name("%s_Dbg", name->s), new s0parms(""));
	} else {
		dbg=dbg_;
	}
}

s1::~s1() {
}

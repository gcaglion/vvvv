#include "s1.h"

s1::s1(s1parmsdef) : s0(s0parmsval) {
	cfg=cfgObjParmsKey_;

}
s1::~s1() {
	delete cfg;
}

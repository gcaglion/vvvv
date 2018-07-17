#include "DataSource.h"


//=== sDataSource
sDataSource::sDataSource(s0parmsdef, int type_, Bool calcBW_, int BWfeatureH_, int BWfeatureL_) : s0(s0parmsval) {
	type=type_; calcBW=calcBW_; BWfeatureH=BWfeatureH_; BWfeatureL=BWfeatureL_;
}
sDataSource::sDataSource(s0parmsdef, sCfg* cfgParms_, sCfgKey* cfgKey_) : s0(s0parmsval) {
	parms->get(&type, "Type");
}
sDataSource::sDataSource(s0parmsdef) : s0(s0parmsval) {}
sDataSource::~sDataSource() {}
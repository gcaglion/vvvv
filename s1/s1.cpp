#include "s1.h"


s1::s1(s0Name* name_, s0* parent_, sDbg* dbg_, s1Parms* cParms_) : s0(name_, parent_, true) {

	//-- 1. sets class-specific constructor parameters.
	cParms=cParms_;
	//-- 2. sets dbg
	if (dbg_==nullptr) {
		try {
			dbg=new sDbg(this);
		}
		catch (std::exception exc) {
			sprintf_s(errmsg, sizeof(errmsg), "%s(): Error trying to create dbg. Exception: %s", __func__, exc.what());
			throw std::exception(errmsg);
		}
	} else {
		dbg=dbg_;
	}
}


s1::~s1() {
	delete dbg;
}

void s1::cmdprep(char* whatmask_, ...) {
	strcpy_s(whatmask, CMD_MAXLEN, whatmask_);

	va_list whatargs;
	va_start(whatargs, whatmask_);

	vsprintf_s(what, CMD_MAXLEN, whatmask, whatargs);
	va_end(whatargs);

	sprintf_s(trymsg, CMD_MAXLEN, "TRYING : %s", what);
	sprintf_s(successmsg, CMD_MAXLEN, "SUCCESS: %s", what);
	sprintf_s(failuremask, CMD_MAXLEN, "FAILURE: %s", what);
	strcat_s(failuremask, CMD_MAXLEN, " . Exception: %s");

}

void s1::_sc(s0* caller_, const char* func_, char* desc_, ...) {

}
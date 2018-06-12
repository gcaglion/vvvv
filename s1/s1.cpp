#include "s1.h"

s1parms::s1parms(bool autofill, char* mask_, ...) {
	strcpy_s(mask, OBJ_PARMS_MASK_MAXLEN, mask_);
	pcnt=0;
	for (int i=0; i<strlen(mask); i++) {
		if (mask[i]==37) {
			ptype[pcnt]=mask[i+1];
			pcnt++;
		}
	}

	va_list vargs;
	if (autofill) {
		va_start(vargs, mask);
		for (int p=0; p<pcnt; p++) {
			switch (ptype[p]) {
			case 's':
				strcpy_s(pvalS[p], OBJ_PARMS_VAL_MAXLEN, va_arg(vargs, char*));
				break;
			case 'd':
				pvalI[p] = va_arg(vargs, int);
				break;
			case 'f':
				pvalF[p] = va_arg(vargs, double);
				break;
			case 'p':
				pvalP[p] = va_arg(vargs, long);
				break;
			default:
				break;
			}
		}
		va_end(vargs);
	}

}
void s1parms::fill(...) {
	va_list vargs;
	va_start(vargs, mask);
	for (int p=0; p<pcnt; p++) {
		switch (ptype[p]) {
		case 's':
			strcpy_s(pvalS[p], OBJ_PARMS_VAL_MAXLEN, va_arg(vargs, char*));
			break;
		case 'd':
			pvalI[p] = va_arg(vargs, int);
			break;
		case 'f':
			pvalF[p] = va_arg(vargs, double);
			break;
		case 'p':
			pvalP[p] = va_arg(vargs, long);
			break;
		default:
			break;
		}
	}
	va_end(vargs);
}

s1::s1(s0Name* name_, s0* parent_, sDbg* dbg_, s1parms* cParms_) : s0(name_, parent_, true) {

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

#include "s0.h"

s0parms::s0parms(const char* mask_, ...) {
	char pstring[OBJ_PARMS_VAL_MAXLEN];
	strcpy_s(mask, OBJ_PARMS_MASK_MAXLEN, mask_);

	//-- 1. set parameters number and types
	pcnt=0;
	for (int i=0; i<strlen(mask); i++) {
		if (mask[i]==37) {
			ptype[pcnt]=mask[i+1];
			pcnt++;
		}
	}
	ptype[pcnt]='\0';

	//-- 2. set parameters values
	va_list vargs;
	va_start(vargs, mask);
	//-- get rid of the first 
	char* m=va_arg(vargs, char*);

	fullstring[0]='\0';
	for (int p=0; p<pcnt; p++) {
		if (p>0) strcat_s(fullstring, OBJ_PARMS_MASK_MAXLEN, ", ");
		switch (ptype[p]) {
		case 's':
			strcpy_s(pvalS[p], OBJ_PARMS_VAL_MAXLEN, va_arg(vargs, char*));
			sprintf_s(pstring, OBJ_PARMS_VAL_MAXLEN, "\"%s\"", pvalS[p]);
			break;
		case 'd':
			pvalI[p] = va_arg(vargs, int);
			sprintf_s(pstring, OBJ_PARMS_VAL_MAXLEN, "%d", pvalI[p]);
			break;
		case 'f':
			pvalF[p] = va_arg(vargs, numtype);
			sprintf_s(pstring, OBJ_PARMS_VAL_MAXLEN, "%f", pvalF[p]);
			break;
		case 'p':
			pvalP[p] = va_arg(vargs, long*);
			sprintf_s(pstring, OBJ_PARMS_VAL_MAXLEN, "%p", pvalP[p]);
			break;
		default:
			break;
		}
		strcat_s(fullstring, OBJ_PARMS_MASK_MAXLEN, pstring);
	}
	va_end(vargs);

}

s0::s0(s0name* name_, s0parms* cparms_, s0* parent_) {

	//-- 1. sets class-specific constructor parameters.
	cparms=cparms_;
	name=name_; parent=parent_; childrenCnt=0;
	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		//*if (!noDelete_) {
			parent->child[parent->childrenCnt]=this;
			parent->childrenCnt++;
		//}
	}

}

s0::~s0() {
	for (int c=childrenCnt-1; c>=0; c--) {
		delete child[c];
	}

}

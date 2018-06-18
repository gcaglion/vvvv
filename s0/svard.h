#pragma once
#include "../CommonEnv.h"

#define PARMS_MAXCNT	32
#define PARM_MASK_LEN	8
#define PARM_VAL_MAXLEN	1024

struct svard {
	int  pcnt;
	char pmask[PARMS_MAXCNT][PARM_MASK_LEN];	// "%s", "%d%, "%f", "p". 
	char   pvalS[PARMS_MAXCNT][PARM_VAL_MAXLEN];
	int    pvalI[PARMS_MAXCNT];
	numtype pvalF[PARMS_MAXCNT];
	long*   pvalP[PARMS_MAXCNT];
	char fullval[PARMS_MAXCNT*PARM_VAL_MAXLEN];

	void select(const char* a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "\"%s\", "); }
	void select(char* a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "\"%s\", "); }
	void select(int a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "%d, "); }
	void select(numtype a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "%f, "); }
	void select(long* a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "%p, "); }

	template <class T> void addParm(T a){
		sprintf_s(pvalS[pcnt], PARM_VAL_MAXLEN, pmask[pcnt], a);
		strcat_s(fullval, PARMS_MAXCNT*PARM_VAL_MAXLEN, pvalS[pcnt]);
		pcnt++;
	}

	template <class T> void variadic(T a) {
		select(a);
		addParm(a);
	}

	template <class T, class ...Args> void variadic(T a, Args... args) {
		select(a);
		addParm(a);
		variadic(args...);
	}
	template <class T, class ...Args> svard* getsvard(T a, Args... args) {
		variadic(a, args...);
		if (pcnt>0) fullval[strlen(fullval)-2]='\0';
		return this;
	}

	svard() {
		pcnt=0;
		fullval[0]='\0'; //fullmask[0]='\0';
	}
	
};

#define newsvard(...) { \
(new svard())->getsvard(__VA_ARGS__) \
}


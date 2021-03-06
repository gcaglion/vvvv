#pragma once
#include "../CommonEnv.h"

#define PARMS_MAXCNT	32
#define PARM_MASK_LEN	8
#define PARM_VAL_MAXLEN	1024

#define CMD_MAXLEN 4096

struct svard {
	int  pcnt;
	bool lastp;
	char pmask[PARMS_MAXCNT][PARM_MASK_LEN];	// "%s", "%d%, "%f", "p". 
	char   pvalS[PARMS_MAXCNT][PARM_VAL_MAXLEN];
	int    pvalI[PARMS_MAXCNT];
	numtype pvalF[PARMS_MAXCNT];
	long*   pvalP[PARMS_MAXCNT];
	char fullval[PARMS_MAXCNT*PARM_VAL_MAXLEN];
#ifdef __cplusplus
	void select(const char* a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "\"%s\", "); }
	void select(char* a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "\"%s\", "); }
	void select(int a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "%d, "); }
	void select(numtype a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "%f, "); }
	void select(void* a) { strcpy_s(pmask[pcnt], PARM_MASK_LEN, "%p, "); }

	template <class T> void addParm(T a) {
		sprintf_s(pvalS[pcnt], PARM_VAL_MAXLEN, pmask[pcnt], a);
		strcat_s(fullval, PARMS_MAXCNT*PARM_VAL_MAXLEN, pvalS[pcnt]);
		pcnt++;
	}

	void variadic() {}
	
	void cutLastComma(){
		fullval[strlen(fullval)-2]='\0';
		lastp=true;
	}

	template <class T> void variadic(T a) {
		select(a);
		addParm(a);
		if (pcnt==1) cutLastComma();
	}

	template <class T, class ...Args> void variadic(T a, Args... args) {
		select(a);
		addParm(a);
		variadic(args...);
		if (pcnt>0 && !lastp) cutLastComma();
	}

	svard() {
		pcnt=0;
		lastp=false;
		fullval[0]='\0';
	}
#endif

};


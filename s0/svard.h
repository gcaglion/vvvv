#pragma once
#include "../CommonEnv.h"

#define PARMS_MAXCNT		32
#define PARMS_MASK_MAXLEN	125
#define PARMS_VAL_MAXLEN	1024

/*struct svard {
	int  pcnt;
	char ptype[PARMS_MAXCNT];	// 's', 'd', 'f', 'p'. 
	char   pvalS[PARMS_MAXCNT][PARMS_VAL_MAXLEN];
	int    pvalI[PARMS_MAXCNT];
	numtype pvalF[PARMS_MAXCNT];
	long*   pvalP[PARMS_MAXCNT];
	char mask[PARMS_MASK_MAXLEN];
	char fullstring[PARMS_MASK_MAXLEN];

	svard(char* mask_=nullptr) {
		pcnt=0;
		ptype[0]='\0';
		if (mask_!=nullptr) {
			strcpy_s(mask, PARMS_MASK_MAXLEN, mask_);
		}
	}

	void select(const char* a) { strcpy_s(pvalS[pcnt], PARMS_VAL_MAXLEN, a); ptype[pcnt]='s'; pcnt++; }
	void select(char* a) { strcpy_s(pvalS[pcnt], PARMS_VAL_MAXLEN, a); ptype[pcnt]='s'; pcnt++; }
	void select(int a) { pvalI[pcnt]=a; ptype[pcnt]='d'; pcnt++; }
	void select(numtype a) { pvalF[pcnt]=a; ptype[pcnt]='f'; pcnt++; }
	void select(long* a) { pvalP[pcnt]=a; ptype[pcnt]='p'; pcnt++; }

	template <class T> void variadic(T a) {
		select(a);
	}

	template <class T, class ...Args> void variadic(T a, Args... args) {
		select(a);
		variadic(args...);
	}


};
*/
struct svard {
	int  pcnt;
	char pmask[PARMS_MAXCNT][3];	// "%s", "%d%, "%f", "p". 
	char   pvalS[PARMS_MAXCNT][PARMS_VAL_MAXLEN];
	int    pvalI[PARMS_MAXCNT];
	numtype pvalF[PARMS_MAXCNT];
	long*   pvalP[PARMS_MAXCNT];
	//char baremask[PARMS_MAXCNT*3];
	//char fullstring[PARMS_MAXCNT*PARMS_VAL_MAXLEN];

	void select(const char* a) { 
		strcpy_s(pmask[pcnt], 3, "%s");  
	}
	void select(char* a) {
		strcpy_s(pmask[pcnt], 3, "%s");
	}
	void select(int a) {
		strcpy_s(pmask[pcnt], 3, "%d");
	}
	void select(numtype a) {
		strcpy_s(pmask[pcnt], 3, "%f");
	}
	void select(long* a) {
		strcpy_s(pmask[pcnt], 3, "%p");
	}

	template <class T> void variadic(T a) {
		select(a);
		sprintf_s(pvalS[pcnt], PARMS_VAL_MAXLEN, pmask[pcnt], a);
		//strcat_s(baremask, PARMS_MAXCNT*2, pvalS[pcnt]);
		//strcat_s(baremask, PARMS_MAXCNT*2, ",");
		pcnt++;
	}

	template <class T, class ...Args> void variadic(T a, Args... args) {
		select(a);
		variadic(args...);
	}

	template <class T, class ...Args> svard(T a, Args... args) {
		pcnt=0;
		//baremask[0]='\0';
		variadic(a, args...);
	}

	char* getFullString(char* mask_) {
//		sprintf_s(fullstring, PARMS_MAXCNT*PARMS_VAL_MAXLEN, mask_,  )
	}
};


#define newsvard0(...) new svard(__VA_ARGS__)
#define newname(mask_, ...) 



#define sets0name(mask_, ...) sprintf_s(name, OBJ_NAME_MAXLEN, __VA_ARGS__)
#define newname(mask_, ...) (new svard(__VA_ARGS__))->getFullString(mask_))


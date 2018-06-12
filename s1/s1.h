#pragma once
#include "../CommonEnv.h"
#include "../s0/s0.h"
#include "../dbg/dbg.h"

struct spmask {
	char mask[OBJ_PARMS_MASK_MAXLEN];
	int  pcnt;
	char ptype[OBJ_PARMS_MAXCNT];	// 's', 'd', 'f', 'p'. 

	spmask(char* mask_) {
		strcpy_s(mask, OBJ_PARMS_MASK_MAXLEN, mask_);
		pcnt=0;
		for (int i=0; i<strlen(mask); i++) {
			if (mask[i]==37) {
				ptype[pcnt]=mask[i+1];
				pcnt++;
			}
		}
	}

	void fill(...) {
		char   pvalS[OBJ_PARMS_MAXCNT][OBJ_PARMS_VAL_MAXLEN];
		int    pvalI[OBJ_PARMS_MAXCNT];
		float  pvalF[OBJ_PARMS_MAXCNT];
		long   pvalP[OBJ_PARMS_MAXCNT];
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
				pvalF[p] = va_arg(vargs, float);
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

};

struct s1Parms {
	char className[MAX_CLASS_NAME];
	char pmask[OBJ_PARMS_MASK_MAXLEN];
	int pcnt;


	s1Parms(char* className_, char* pmask_, ...) {
		/*strcpy_s(pmask, OBJ_PARMS_MASK_MAXLEN, pmask_);
		pcnt=argcnt(pmask);

		va_list pargs;
		va_start(pargs, parmsMask_);
		va_copy(pargs2, pargs);
		va_end(pargs);
		strcpy_s(className, MAX_CLASS_NAME, className_);
	*/}

	~s1Parms() {
	}
};

struct s1 :s0 {
	s1Parms* cParms;
	sDbg* dbg;

	EXPORT s1(s0Name* name_, s0* parent_, sDbg* dbg_, s1Parms* cParms_);
	EXPORT ~s1();

	EXPORT void _sc(s0* caller_, const char* func_, char* desc_, ...);

	EXPORT void cmdprep(char* whatmask_, ...);
	char whatmask[CMD_MAXLEN];
	char what[CMD_MAXLEN];
	char trymsg[CMD_MAXLEN];
	char successmsg[CMD_MAXLEN];
	char failuremsg[CMD_MAXLEN];
	char failuremask[CMD_MAXLEN];
	char actualcmd[CMD_MAXLEN];

	char cmdmask[CMD_MAXLEN];
	char cmd[CMD_MAXLEN];

	char spawnargs[CMD_MAXLEN];
	
	template <typename T> EXPORT void safespwn(T* s1objvar_, s0Name* s0objnamevar_, sDbg* s1objdbgvar_, s1Parms* s1objcparms_, const char* callerFunc_) {
	/*	char inp[CMD_MAXLEN];
		vsprintf_s(inp, CMD_MAXLEN, s1objcparms_->parmsMask, s1objcparms_->pargs2);
		sprintf_s(whatmask, CMD_MAXLEN, "%s = new %s (%s)", s0objnamevar_->s, s1objcparms_->className, inp);
		//sprintf_s(what, CMD_MAXLEN, whatmask, )
		sprintf_s(trymsg, CMD_MAXLEN,		"TRYING : %s ", what);
		sprintf_s(successmsg, CMD_MAXLEN,	"SUCCESS: %s", what);
		sprintf_s(failuremask, CMD_MAXLEN,	"FAILURE: %s", what);
		strcat_s(failuremask, CMD_MAXLEN,	" . Exception: %s");
*/
		try {
			dbg->out(OBJ_MSG_INFO, callerFunc_, trymsg);
			s1objvar_=new T(s0objnamevar_, this, s1objdbgvar_, s1objcparms_);
			dbg->out(OBJ_MSG_INFO, callerFunc_, successmsg);
		}
		catch (std::exception exc) {
			dbg->out(OBJ_MSG_ERR, callerFunc_, failuremask, exc.what());
			throw std::exception(dbg->msg);
		}
	}
};

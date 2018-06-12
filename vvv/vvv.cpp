#include "../CommonEnv.h"

#include "../s0/s0.h"
#include "../s1/s1.h"
#include "../FileInfo/FileInfo.h"

/*void sc(char* icmdMask_, char* ocmd, ...) {
	char cmd[CMD_MAXLEN];
	va_list args;
	va_start(args, icmdMask_);
	vsprintf_s(ocmd, CMD_MAXLEN, icmdMask_, args);
	va_end(args);

}
*/

struct sParmMgr :s1 {

	int p1;
	int p2;
	tFileInfo* parmsFile=nullptr;

	sParmMgr(s0Name* name_, s0* parent_, sDbg* dbg_, s1Parms* cParms_) : s1(name_, parent_, dbg_, cParms_) {

		//cmdprep("open parameters file %s/%s for read", parmsFilePath_, parmsFileName_);
		//cmdrun(parmsFile=new tFileInfo(this, parmsFileName_, parmsFilePath_, FILE_MODE_READ));


//-- Original

/*		try {
			dbg->out(OBJ_MSG_INFO, __func__, "TRYING : open parameters file %s/%s", parmsFilePath_, parmsFileName_);
			parmsFile=new tFileInfo(this, parmsFileName_, parmsFilePath_, FILE_MODE_READ);
			dbg->out(OBJ_MSG_INFO, __func__, "SUCCESS: open parameters file %s/%s", parmsFilePath_, parmsFileName_);
		}
		catch (std::exception exc) {
			dbg->out(OBJ_MSG_ERR, __func__, "FAILURE: open parameters file %s/%s . Exception: %s", parmsFilePath_, parmsFileName_, exc.what());
			throw std::exception(dbg->msg);
		}
	//--
*/
	}

	void met(int p) {
		printf("ppppppppppp=%d\n", p);
	}
};

struct sRoot : s1 {

	sParmMgr* XMLparms=nullptr;

	sRoot(sDbg* rootDbg_=nullptr) : s1(new s0Name("root%d",99), nullptr, rootDbg_, nullptr) {

		//-- spawn XMLparms
		char* xmlfname="rootparms.xml";
		char* xmlfpath="C:/temp";
		
		s1Parms* pppp=new s1Parms("sParmMgr", "%s, %s", xmlfname, xmlfpath);
		//safespwn<sParmMgr>(XMLparms, new s0Name("rootXMLparms_%d", 88), nullptr, new s1Parms("sParmMgr", "%s, %s", xmlfname, xmlfpath), __func__);
		safespwn<sParmMgr>(XMLparms, new s0Name("rootXMLparms_%d", 88), nullptr, pppp, __func__);
		/*
		try {
			dbg->out(OBJ_MSG_INFO, __func__, trymsg);
			XMLparms=new sParmMgr(new s0Name("rootXMLparms_%d", 88), this, nullptr, new s1Parms("%s, %s", xmlfname, xmlfpath));
			dbg->out(OBJ_MSG_INFO, __func__, successmsg);
		}
		catch (std::exception exc) {
			dbg->out(OBJ_MSG_ERR, __func__, failuremask, exc.what());
			throw std::exception(dbg->msg);
		}
*/
	//-- Original
/*
	try {
			dbg->out(OBJ_MSG_INFO, __func__, "TRYING : spawn XMLparms(%s/%s)", xmlfpath, xmlfname);
			XMLparms=new sParmMgr(new s0Name("rootXMLparms_%d", 88), this, nullptr, xmlfname, xmlfpath);
			dbg->out(OBJ_MSG_INFO, __func__, "SUCCESS: spawn XMLparms(%s/%s)", xmlfpath, xmlfname);
		}
		catch (std::exception exc) {
			dbg->out(OBJ_MSG_ERR, __func__, "FAILURE: spawn XMLparms(%s/%s). Exception: %s", xmlfpath, xmlfname, exc.what());
			throw std::exception(dbg->msg);
		}
*/
	}

	~sRoot() {
		delete XMLparms;
	}

};


int main(int argc, char* argv[]) {
	int ret;



	//sDbg* rootdbg=new sDbg(nullptr);

	sRoot* root=nullptr;
	try {
		root=new sRoot();
		printf("main() successful.\n");
		ret=0;
	}
	catch (std::exception exc) {
		printf("main() failed. exception=%s\n", exc.what());
		ret=-1;
	}

	delete root;

	system("pause");
	return ret;
}

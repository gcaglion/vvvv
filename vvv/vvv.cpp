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

	sParmMgr(s0Name* name_, s0* parent_, sDbg* dbg_, s1parms* cParms_) : s1(name_, parent_, dbg_, cParms_) {

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
		
		s1parms* sp1= new s1parms(true, "%s, %s");

		//safespwn<sParmMgr>(XMLparms, new s0Name("rootXMLparms_%d", 88), nullptr, new s1Parms("sParmMgr", "%s, %s", xmlfname, xmlfpath), __func__);
	}

	~sRoot() {
		delete XMLparms;
	}

};


int main(int argc, char* argv[]) {
	int ret=3;
	int* retp=&ret;

	s1parms* sp1= new s1parms(false, "%s, %s");
	sp1->fill("blah", "kaz");
	s1parms* sp1f= new s1parms(true, "%s, %s", "blah", "kaz");

	/*/
	spmask* m0=new spmask("blah %s = %s - %s");
	m0->fill("kkk", "lllll", "mmmmmmm");
	spmask* m1=new spmask("blah %s = %d %f");
	m1->fill("kkk", 1, 3.5);
	spmask* m2=new spmask("blah %s = %d %p %f");
	m2->fill("kkk", 1, retp, 3.5);
*/
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

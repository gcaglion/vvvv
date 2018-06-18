#include "../CommonEnv.h"

#include "../s0/s0.h"
#include "../FileInfo/FileInfo.h"

/*
struct sParmMgr :s1 {

	//-- constructor parameters (in order)
	char* parmsFilePath;
	char* parmsFileName;
	//-- internal variables
	tFileInfo* parmsFile=nullptr;

	sParmMgr(s0parmsdef, sDbg* dbg_) : s1(s0parmsval, dbg_) {

		safespawn0(parmsFile, tFileInfo, newname("%s_pfile", name), newparms("%d, %s, %s", FILE_MODE_READ, cparms->pvalS[0], cparms->pvalS[1]));
	}

	void met(int p) {
		printf("ppppppppppp=%d\n", p);
	}
};

struct sKaz :s1 {
	int p1;

	sKaz(s0parmsdef, sDbg* dbg_) : s1(s0parmsval, dbg_) {
		p1=9;
	}
};

struct sRoot : s1 {

	sParmMgr* xmlparms=nullptr;

	sRoot(sDbg* rootDbg_=nullptr) : s1(newname("root%d",99), nullptr, nullptr, rootDbg_) {

		//-- spawn XMLparms
		char* xmlfname="rootparms.xml";
		char* xmlfpath="C:/temp";
		
		//xmlparms=safespwn1(__func__, "SParmMgr", newname("rootXMLparms_%d", 88), newparms("%s, %s", xmlfpath, xmlfname), nullptr);
		//safespawn1(xmlparms, sParmMgr, newname("rootXMLparms_%d", 88), newparms("%s, %s", xmlfpath, xmlfname), nullptr);

		xmlparms->met(1);

	}

	~sRoot() {
	}

};
*/

struct sRoots0 : s0 {

	//-- root-level objects
	tFileInfo* f1=nullptr;

	sRoots0(s0parmsdef) : s0(s0parmsval) {

		//sname* f1name=new sname("f%dname");
		//f1name->variadic(1);
		svard* f1parms=newsvard("dioporco.f1.log", FILE_MODE_WRITE, "C:/temp");
		printf("calling new file with (%s)", f1parms->fullval);
		//f1parms->variadic("dioporco.f1.log", FILE_MODE_WRITE, "C:/temp");

		//f1=_spawn<tFileInfo>(__func__, "tFileInfo", f1name, f1parms);


	}

};




int main(int argc, char* argv[]) {
	int ret;


	sRoots0* root=nullptr;
	try {
		root=new sRoots0(newname("root_%d", 99), nullptr, true);
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

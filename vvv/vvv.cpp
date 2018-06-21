#include "../CommonEnv.h"

#include "../s0/s0.h"
#include "../s0/svard.h"
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

struct sK {
	s0* s0p;

	int p1; char* p2;

	sK(s0* s0p_, int p1_, char* p2_) {
		s0p=s0p_; p1=p1_; p2=p2_;
	}

};



struct sRoot {
	s0* s0p;

	sK* sK1;

	sRoot(s0* s0p_) {
		s0p=s0p_; 
		s0p->setParms(nullptr, newdbg());

		int vp1=3; char* vp2="vp2";
		
		sK1 = s0p->___spawn<sK>(__func__,  newname("sk%dname", 1), newdbg(), vp1, vp2);
		
	}

};



int main(int argc, char* argv[]) {
	int ret;



		
	sRoot* root=nullptr;
	try {
		root=new sRoot(new s0(nullptr, newdbg(), "root"));

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

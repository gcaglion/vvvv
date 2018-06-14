#include "../CommonEnv.h"

#include "../s0/s0.h"
#include "../s1/s1.h"
#include "../FileInfo/FileInfo.h"


struct sParmMgr :s1 {

	//-- constructor parameters (in order)
	char* parmsFilePath;
	char* parmsFileName;
	//-- internal variables
	tFileInfo* parmsFile=nullptr;

	sParmMgr(s0name* name_, s0parms* cparms_, s0* parent_, sDbg* dbg_) : s1(name_, cparms_, parent_, dbg_) {

		safespawn0(parmsFile, tFileInfo, newname("%s_pfile", name), newparms("%d, %s, %s", FILE_MODE_READ, cparms->pvalS[0], cparms->pvalS[1]));
	}

	void met(int p) {
		printf("ppppppppppp=%d\n", p);
	}
};

struct sKaz :s1 {
	int p1;

	sKaz(s0name* name_, s0parms* cparms_, s0* parent_, sDbg* dbg_) : s1(name_, cparms_, parent_, dbg_) {
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
		safespawn1(xmlparms, sParmMgr, newname("rootXMLparms_%d", 88), newparms("%s, %s", xmlfpath, xmlfname), nullptr);

		xmlparms->met(1);

	}

	~sRoot() {
	}

};


template <typename... Types> struct foo {};

template < typename... Types1, template <typename...> class T , typename... Types2, template <typename...> class V , typename U > void bar(const T<Types1...>&, const V<Types2...>&, const U& u) {
	std::cout<<sizeof...(Types1)<<std::endl;
	std::cout<<sizeof...(Types2)<<std::endl;
	std::cout<<u<<std::endl;
}


int main(int argc, char* argv[]) {
	int ret;


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

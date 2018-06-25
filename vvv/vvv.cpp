#include "../CommonEnv.h"

#include "../s0/s0.h"
#include "../ConfigMgr/ConfigMgr.h"

struct sQ : s0 {
	int p1; char* p2;

	sQ(s0parmsdef, int p1_, char* p2_) : s0(s0parmsval) {
		p1=p1_; p2=p2_;
		if (p1==2) fail("forced failure; p1=%d", p1);
	}

	void met1(int mp1, char* mp2) {
		printf("MMMMMMMMMMM\n");
	}
	void met2(int mp1, char* mp2) {
		printf("NNNNNNNNNNN\n");
	}

	~sQ() {}
};

struct sRoot : s0 {

	sConfigItem* xmlForecasterRoot;

	sRoot(sDbg* dbg_) : s0(nullptr, newsname("root"), dbg_) {}

	void run() {

		char* configFile="c:/temp/client.xml";
		safespawn(xmlForecasterRoot, sConfigItem, newsname("Forecaster XML root Key"), newdbg(), configFile);


	}

	~sRoot(){}

};

int main(int argc, char* argv[]) {
	int ret=1;

	sRoot* root=nullptr;
	try {
		root=new sRoot(newdbg());
		root->run();
		printf("main() successful.\n");
		ret=0;
	}
	catch (std::exception exc) {
		printf("main() failed. exception=%s\n", exc.what());
		printf("root stack:\n%s\n", root->dbg->stack);
		ret=-1;
	}

	delete root;

	system("pause");
	return ret;
}

#include "../CommonEnv.h"

#include "../s0/s0.h"

struct sQ : s0 {
	int p1; char* p2;

	sQ(s0parmsdef, int p1_, char* p2_) : s0(s0parmsval) {
		p1=p1_; p2=p2_;
		if (p1==2) {
			fail("forced failure; p1=%d", p1);
		}
	}

	~sQ() {}
};

struct sRoot : s0 {
	//s0* s0p;

	sQ* sQ1;
	sQ* sQ2;
	sQ* sQ3;

	sRoot(sDbg* dbg_) : s0(nullptr, newsname("root"), dbg_) {
	}

	void run() {

		char* vp1="11111GGGG";
		char* vp2="22222GGGG";
		char* vp3="33333GGFF";
		sQ1= _spawn<sQ>(__func__, newsname("dd"), newdbg(), 3, vp3);

		safespawn(sQ1, sQ, newsname("sQ%dname", 1), newdbg(), 1, vp1);
		safespawn(sQ2, sQ, newsname("sQ%dname", 2), newdbg(), 2, vp2);
		safespawn(sQ3, sQ, newsname("sQ%dname", 3), newdbg(), 3, vp3);
	}

	~sRoot(){}

};



int main(int argc, char* argv[]) {
	int ret;
		
	sRoot* root=nullptr;
	try {
		root=new sRoot(newdbg());
		root->run();
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

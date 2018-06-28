#include "../CommonEnv.h"

#include "../s1/s1.h"
#include "../ConfigMgr/ConfigMgr.h"

struct s1A : s1 {
	int p1;

	s1A(s1parmsdef, int p1_): s1(s1parmsval) {
		p1=p1_;
	}
};

struct sRoot : s1 {

	sCfg* xmlForecasterCfg;
	s1A* s1A0;

	sRoot(sDbg* dbg_) : s1(nullptr, newsname("root"), dbg_, nullptr) {}

	void run() {

		safespawn0(xmlForecasterCfg, sCfg, newsname("Forecaster XML main config"), newdbg(), "c:/temp/client.xml");

		//-- absolute key
		safecall(sCfg, xmlForecasterCfg, setKey, "/Forecaster/Data/Train/Dataset");
		//-- sub key
		safecall(sCfg, xmlForecasterCfg, setKey, "TimeSerie/DataSource/FileData");
		//-- ..
		safecall(sCfg, xmlForecasterCfg, setKey, "..");
		//-- /
		safecall(sCfg, xmlForecasterCfg, setKey, "/");
		//-- sub key
		safecall(sCfg, xmlForecasterCfg, setKey, "Forecaster/Debugger");
		//-- ../<key>
		safecall(sCfg, xmlForecasterCfg, setKey, "../Engine");

		int maxEpochs=xmlForecasterCfg->get<int>("Custom/Core0/Training/MaxEpochs");

		safespawn1(s1A0, s1A, newsname("TimeSerie%d", 99), xmlForecasterCfg->currentKey, 99);

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

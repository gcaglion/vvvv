#include "../CommonEnv.h"

#include "../s0/s0.h"
#include "../ConfigMgr/ConfigMgr.h"

struct sRoot : s0 {

	sCfg* xmlForecasterCfg;

	sRoot(sDbg* dbg_) : s0(nullptr, newsname("root"), dbg_) {}

	void run() {

		safespawn(xmlForecasterCfg, sCfg, newsname("Forecaster XML main config"), newdbg(), "c:/temp/client.xml");

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

#include "../CommonEnv.h"

#include "../ConfigMgr/ConfigMgr.h"

struct sForecaster : s0 {
	int p1;

	sForecaster(s0parmsdef, int p1_) : s0(s0parmsval) {
		p1=p1_;
	}
};

struct sRoot : s0 {

	sCfg* xmlForecasterCfg;
	sForecaster* frc1;

	sRoot(sDbg* rootDbg_) : s0(nullptr, newsname("root"), rootDbg_) {}

	void run() {

		safespawn(xmlForecasterCfg, sCfg, newsname("Forecaster XML main config"), defaultdbg, "c:/temp/client.xml");

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

		int maxEpochs;
		getParmVal(maxEpochs, xmlForecasterCfg, "Custom/Core0/Training/MaxEpochs");

		safespawn(frc1, sForecaster, newsname("Forecaster%d", 99), xmlForecasterCfg->newdbg("/Forecaster"), 99);

	}

	~sRoot(){}

};

int main(int argc, char* argv[]) {
	int ret=1;

	sRoot* root=nullptr;
	try {
		root=new sRoot(defaultdbg);
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

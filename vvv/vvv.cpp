#include "../CommonEnv.h"

#include "../ConfigMgr/ConfigMgr.h"
#include "../DBConnection/DBConnection.h"

struct sForecaster : s0 {
	int p1;

	sForecaster(s0parmsdef, int p1_) : s0(s0parmsval) {
		p1=p1_;
	}
};

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair {};

template<class ...Args1> struct zip {
	template<class ...Args2> struct with {
		typedef Tuple<Pair<Args1, Args2>...> type;
		//        Pair<Args1, Args2>... is the pack expansion
		//        Pair<Args1, Args2> is the pattern
	};
};

// Pair<Args1, Args2>... expands to
// Pair<short, unsigned short>, Pair<int, unsigned int> 
// T1 is Tuple<Pair<short, unsigned short>, Pair<int, unsigned>>

struct sPPP {
	int p;

	sPPP(int p_) { p=p_; }

};

struct sRoot : s0 {

	sCfg* xmlForecasterCfg;
	sDBConnection* dbc1;

	sRoot(sDbg* rootDbg_) : s0(nullptr, newsname("root"), rootDbg_) {}

	void run() {

		sPPP* sfr1=new sVar<sPPP> ("PPP_%d", 99);


		safespawn(xmlForecasterCfg, sCfg, newsname("Forecaster XML main config"), nulldbg, "c:/temp/client.xml");

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

		safespawn(dbc1, sDBConnection, newsname("DBConnection%d", 1), xmlForecasterCfg->newdbg("/Forecaster/Data/Train/DataSet/TimeSerie/DataSource/FXData/DBConnection"), "system", "manager", "Algo");

	}

	~sRoot(){}

};

int main(int argc, char* argv[]) {
	int ret=1;

	sRoot* root=nullptr;
	try {
		root=new sRoot(nulldbg);
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

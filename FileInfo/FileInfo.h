#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#include <stdio.h>
#include <time.h>
#include "../Utils/Utils.h"
#include "FileInfo_enums.h"


typedef struct sFileInfo : s0 {

	//-- constructor parameters (in order)
	int mode;
	char Path[MAX_PATH];
	char Name[MAX_PATH];

	//-- internal variables
	FILE* handle;
	fpos_t pos;
	char FullName[MAX_PATH];
	char modeS[2];
	char modeDesc[30];

#ifdef __cplusplus

	EXPORT sFileInfo(s0name* name_, s0parms* cParms_, s0* parent_);
	EXPORT ~sFileInfo();
	EXPORT void savePos();
	EXPORT void restorePos();

private:
	char errmsg[1024]; 
	void setModeS();
#endif

} tFileInfo;

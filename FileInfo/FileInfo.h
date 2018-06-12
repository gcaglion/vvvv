#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#include <stdio.h>
#include <time.h>
#include "../Utils/Utils.h"
#include "FileInfo_enums.h"


typedef struct sFileInfo : s0 {

	char Path[MAX_PATH];
	char Name[MAX_PATH];
	char FullName[MAX_PATH];
	FILE* handle;
	fpos_t pos;

	int mode;
	char modeS[2];
	char modeDesc[30];

#ifdef __cplusplus

	EXPORT void sFileInfo_common();
	EXPORT sFileInfo(s0* parent_, char* Name_, char* Path_, int mode_);
	EXPORT sFileInfo(s0* parent_, char* FullName_, int mode_);
	EXPORT ~sFileInfo();
	EXPORT void savePos();
	EXPORT void restorePos();

private:
	char errmsg[1024]; 
	void setModeS();
#endif

} tFileInfo;

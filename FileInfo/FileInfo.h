#pragma once

#include "../CommonEnv.h"
#include "../s0/s0.h"

#include <stdio.h>
#include <time.h>
#include "../Utils/Utils.h"
#include "FileInfo_enums.h"


typedef struct sFileInfo {
	s0* s0p;

	//-- constructor parameters (in order)
	char fpath[MAX_PATH];
	char fname[MAX_PATH];
	char ffname[MAX_PATH];
	int mode;

	//-- internal variables
	FILE* handle;
	fpos_t pos;
	char modeS[2];
	char modeDesc[30];

	//-- constructor parameters sets

	void commonConstructor();
	EXPORT sFileInfo(s0* s0p_, char* fname_, int mode_, char* fpath_);
	EXPORT sFileInfo(s0* s0p_, char* ffname_, int mode_);
	EXPORT ~sFileInfo();
	EXPORT void savePos();
	EXPORT void restorePos();

} tFileInfo;

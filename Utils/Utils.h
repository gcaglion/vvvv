#pragma once

#include "../CommonEnv.h"
#include <time.h>

EXPORT char* MyGetCurrentDirectory();
EXPORT Bool getCurrentPath(char* oPath);
EXPORT int cslToArray(const char* csl, char Separator, char** StrList);
EXPORT void splitFullFileName(char* iFullName, char* oPath, char* oName);
EXPORT char* substr(char* str, int start, int len);
EXPORT char* right(char* str, int len);
EXPORT char* left(char* str, int len);
EXPORT int  instr(char soughtChar, const char* intoStr, bool fromRight);
EXPORT int argcnt(const char* mask);
EXPORT void UpperCase(const char* istr, char* ostr);
EXPORT void removeQuotes(char* istr, char* ostr);
EXPORT void stripChar(char* istr, char c);
EXPORT Bool getValuePair(char* istr, char* oName, char* oVal, char eqSign);
EXPORT Bool isnumber(char* str);
EXPORT Bool isInList(int soughtVal, int listLen, int* list);
EXPORT void gettimestamp(char* timeS, size_t timeSsize);


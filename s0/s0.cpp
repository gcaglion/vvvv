#include "s0.h"

s0::s0(s0parmsdef) {

	//-- 1. sets class-specific constructor parameters.
	name=name_; parent=parent_; childrenCnt=0; verbose=verbose_;
	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		parent->child[parent->childrenCnt]=this;
		parent->childrenCnt++;
	}

}

 s0::~s0() {
	for (int c=childrenCnt-1; c>=0; c--) {
		delete child[c];
	}

}

 void s0::out(int msgtype, const char* callerFunc_, svard* msgvard) {
	 if (msgtype==OBJ_MSG_INFO&&!verbose) return;

	 char tmpmsg[OBJ_MSG_MAXLEN];

	 char indent[16]=""; for (int t=0; t<stackLevel; t++) strcat_s(indent, 16, "\t");
	 sprintf_s(msg, OBJ_MSG_MAXLEN, "%s%s->%s() %s %s \n", indent, parent->name, callerFunc_, (msgtype==OBJ_MSG_INFO) ? "INFO:  " : "ERROR: ", tmpmsg);
	 strcat_s(stack, OBJ_STACK_MAXLEN, msg); strcat_s(stack, OBJ_STACK_MAXLEN, "\n");

	 printf("%s", msg);

 }

 void s0::out(int msgtype, const char* callerFunc_, char* mshmask_, ...) {}
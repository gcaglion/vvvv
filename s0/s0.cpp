#include "s0.h"

sName::sName(char* nameMask_, ...) {
	va_list va_args;
	va_start(va_args, nameMask_);
	vsprintf_s(s, OBJ_NAME_MAXLEN, nameMask_, va_args);
	va_end(va_args);
	stripChar(s, ' ');
}

s0::s0(s0parmsdef){

	//-- 1. sets class-specific constructor parameters.
	parent=parent_; childrenCnt=0; currentChild=nullptr;
	strcpy_s(name, OBJ_NAME_MAXLEN, sname_->s);
	delete sname_;

	if (parent==nullptr) {
		stackLevel=0;
	} else {
		stackLevel=parent->stackLevel+1;
		sprintf_s(fullName, OBJ_NAME_MAXLEN*OBJ_MAX_DEPTH, "%s/%s", parent->name, name);
	}
	buildfullName();

	//-- create new sDbgParms* object inside s0 constructor, and copy dbg_ parms into it
	dbg=new sDbg(*dbg_);
	//-- we can now delete dbg_
	//delete dbg_;
	//-- sets dbg stackLevel and creates dbg outfile AFTER dbg creation, to get s0 object name
	dbg->stackLevel=stackLevel;
	if (dbg->dbgtofile) dbg->createOutFile(name, this);

}

s0::~s0() {
	 for (int c=childrenCnt-1; c>=0; c--) {
		 delete child[c];
	 }
	 delete dbg;
 }

bool s0::findChild(const char* childName_) {
	if (_stricmp(childName_, currentChild->fullName)==0) return true;

	//-- first, establish key full name based on modifiers ('/','.', ... ), then, find key using full name
	bool found=buildfullName(childName_);
	if (!found) {
		for (int c=0; c<childrenCnt; c++) {
			if (_stricmp(childName_, child[c]->fullName)==0) {
				currentChild = child[c];
				found=true;
				break;
			}
		}
	}
	return found;
}

bool s0::buildfullName(const char* name_) {
	bool found=false;

	if (name_==nullptr) name_=name;
	//-- first, establish key full name based on modifiers ('/','.', ... )
	if (name_[0]=='.' && name_[1]=='.') {
		currentChild=currentChild->parent;
		if (strlen(name_)>2) {
			sprintf_s(fullName, OBJ_NAME_MAXLEN*OBJ_MAX_DEPTH, "%s/%s", currentChild->fullName, &name_[3]);
		} else {
			found=true;
		}
	} else if (name_[0]=='/') {
		if (strlen(name_)>1) {
			strcpy_s(fullName, OBJ_NAME_MAXLEN*OBJ_MAX_DEPTH, name_);
		} else {
			currentChild=currentChild->parent;
			found=true;
		}
	} else {
		sprintf_s(fullName, OBJ_NAME_MAXLEN*OBJ_MAX_DEPTH, "%s/%s", (parent==nullptr)?"":parent->fullName, name_);
	}
	return found;
}


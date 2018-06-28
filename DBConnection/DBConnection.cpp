#include "DBConnection.h"

//=== sDBConnection
sDBConnection::sDBConnection(s0parmsdef, const char* username, const char* password, const char* connstring) : s0(s0parmsval) {
	strcpy_s(DBUser, DBUSER_MAXLEN, username);
	strcpy_s(DBPassword, DBPASSWORD_MAXLEN, password);
	strcpy_s(DBConnString, DBCONNSTRING_MAXLEN, connstring);
	DBCtx=NULL;
}
sDBConnection::~sDBConnection() {

}
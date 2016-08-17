#pragma once
#include <tchar.h>
#include "windows.h"
#include "sql.h"
#include "sqlext.h"

namespace DB
{
	struct user
	{
		SQLINTEGER	UID;
		SQLWCHAR	UserID[40];
		SQLWCHAR	PassWord[40];
	};

	class CDataBase
	{
	public:
		CDataBase() = default;
		~CDataBase() = default;

		SQLHENV hEnv;
		SQLHDBC hDbc;
		SQLHSTMT hStmt;

		bool Init();
		void Destroy();

		bool CreateUser(TCHAR* testID, TCHAR* testPW);
		bool Login(TCHAR* testID, TCHAR* testPW);
		bool DeleteUser(TCHAR* testID, TCHAR* testPW);

	private:
		SQLWCHAR* ODBC_NAME = (SQLWCHAR*)L"mydb";
		SQLWCHAR* ODBC_ID = (SQLWCHAR*)L"root";
		SQLWCHAR* ODBC_PW = (SQLWCHAR*)L"sys0920";
	};
}

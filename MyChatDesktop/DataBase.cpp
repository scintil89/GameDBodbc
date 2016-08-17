#include "DataBase.h"
#include <string.h>
#include <iostream>

namespace DB
{
	bool CDataBase::Init()
	{
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLAllocHandle" << std::endl;
			return false;
		}


		if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLSetEnvAttr" << std::endl;
			return false;
		}

		if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLAllocHandle" << std::endl;
			return false;
		}

		if (SQLConnect(hDbc, ODBC_NAME, SQL_NTS, ODBC_ID, SQL_NTS, ODBC_PW, SQL_NTS) != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLConnect" << std::endl;
			return false;
		}

		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLAllocHandle" << std::endl;
			return false;
		}

		std::cout << "CLEAR : DBConnect" << std::endl;

		return true;
	}

	void CDataBase::Destroy()
	{
		if (hStmt)
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

		if (hDbc)
			SQLDisconnect(hDbc);

		if (hDbc)
			SQLFreeHandle(SQL_HANDLE_DBC, hDbc);

		if (hEnv)
			SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	}

	bool CDataBase::CreateUser(TCHAR* testID, TCHAR* testPW)
	{
		//insert into users(UserID, PassWord) values('bb', '22');
		//TCHAR* testID;
		//TCHAR* testPW;

// 		TCHAR* query1 = L"INSERT INTO USERS(UserID, PassWord) VALUES('";
// 		TCHAR* query2 = L"', '";
// 		TCHAR* query3 = L"')";

		TCHAR* query1 = L"CALL CREATEUSER('";
		TCHAR* query2 = L"', '";
		TCHAR* query3 = L"')";

		TCHAR buf[512] = { '\0', };
		wcscat_s(buf, query1);
		wcscat_s(buf, testID);
		wcscat_s(buf, query2);
		wcscat_s(buf, testPW);
		wcscat_s(buf, query3);

		//std::cout << buf << std::endl;

		auto ret = SQLExecDirectW(hStmt, buf, SQL_NTS);

		if (ret != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLExecDirectW" << std::endl;
			return false;
		}

		return true;
	}


	bool CDataBase::Login(TCHAR* testID, TCHAR* testPW)
	{
		//select UID from users where UserID = 'TEST1' and PassWord = '123123';
		//TCHAR* testID = L"test004";
		//TCHAR* testPW = L"test110";

		TCHAR* query1 = L"SELECT UserID FROM Users WHERE UserID = '";
		TCHAR* query2 = L"' and PassWord = '";
		TCHAR* query3 = L"'";

// 		TCHAR* query1 = L"CALL CHECKUSERtst('";
// 		TCHAR* query2 = L"', '";
// 		TCHAR* query3 = L"')";

		TCHAR buf[512] = { '\0', };
		wcscat_s(buf, query1);
		wcscat_s(buf, testID);
		wcscat_s(buf, query2);
		wcscat_s(buf, testPW);
		wcscat_s(buf, query3);

		//std::cout << buf << std::endl;

		auto ret = SQLExecDirectW(hStmt, buf, SQL_NTS);

		if (ret != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLExecDirectW" << std::endl;
			return false;
		}

// 		ret = SQLMoreResults(hStmt);
// 
// 		if ( (ret == SQL_NO_DATA) )
// 		{
// 			return false;
// 		}

		SQLFetch(hStmt);

		TCHAR result[10];
		SQLINTEGER indicator;

		ret = SQLGetData(hStmt, 1, SQL_C_WCHAR, &result, sizeof(TCHAR), &indicator);

		if (ret != SQL_SUCCESS_WITH_INFO )
		{
			return false;
		}


		return true;
	}

	bool CDataBase::DeleteUser(TCHAR* testID, TCHAR* testPW)
	{
		//delete from users where UserID = 'Test1' and PassWord = '123123'
		//TCHAR* testID = L"test001";
		//TCHAR* testPW = L"test110";

		TCHAR* query1 = L"DELETE FROM Users WHERE UserID = '";
		TCHAR* query2 = L"' AND PassWord = '";
		TCHAR* query3 = L"'";

		TCHAR buf[512] = { '\0', };
		wcscat_s(buf, query1);
		wcscat_s(buf, testID);
		wcscat_s(buf, query2);
		wcscat_s(buf, testPW);
		wcscat_s(buf, query3);

		auto ret = SQLExecDirectW(hStmt, buf, SQL_NTS);

		if (ret != SQL_SUCCESS)
		{
			std::cout << "ERROR : SQLExecDirectW" << std::endl;
			return false;
		}

		return true;
	}
}
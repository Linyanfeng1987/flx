// Runtest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "db/VspdCToMySQL.h"


int _tmain(int argc, _TCHAR* argv[])
{
	VspdCToMySQL sqlObj;
	char* host="localhost";
	char* user="root";
	unsigned int port = 3366;
	char* passwd="101050";
	char* dbname=""; 
	char* charset = "GBK";//֧������
	string strMsg = "";//��Ϣ����
	char* Msg = "";

	sqlObj.ConnMySQL(host,"",dbname,user,passwd,charset,strMsg);

	string strSqlFormat = "insert into core.newTable ( name, value ) value ( 'testName1', '2018��8��20��22:47:22');";
	sqlObj.ExecuteSql(strSqlFormat.c_str());

	printf("hello lyf");
	return 0;
}


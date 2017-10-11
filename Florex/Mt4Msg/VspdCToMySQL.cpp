
#include <stdio.h>
#include "VspdCToMySQL.h"
#pragma comment(lib, "libmysql.lib")  

VspdCToMySQL::VspdCToMySQL(void)
{
}


VspdCToMySQL::~VspdCToMySQL(void)
{
}

//��ʼ������
bool VspdCToMySQL::ConnMySQL(char *host,char * port ,char * Db,char * user,char* passwd,char * charset, string &strMsg)
{
	bool bRes = true;

	if( mysql_init(&mysql) == NULL )
	{
		bRes  = false;
	}    

	if (bRes && mysql_real_connect(&mysql,host,user,passwd,Db,0,NULL,0) == NULL)
	{
		bRes  = false;
	}    

	if(bRes && mysql_set_character_set(&mysql,"GBK") != 0)
	{
		bRes  = false;
	}
	
	if (!bRes)
	{
		strMsg = mysql_error(&mysql);
		return false;
	}
	return true;
}

//��ѯ����
string VspdCToMySQL::SelectData(const char * SQL,int Cnum,char * Msg)
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf_s(sql,SQL);
	int rnum = 0;
	char rg = '\n';//�и���
	char cg = ',';//�ֶθ���

	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "select ps_info Error";
		return "";
	}
	m_res = mysql_store_result(&mysql);

	if(m_res==NULL)
	{
		Msg = "select username Error";
		return "";
	}
	string str("");
	while(m_row = mysql_fetch_row(m_res))
	{
		for(int i = 0;i < Cnum;i++)
		{
			str += m_row[i];
			str += cg;
		}
		str += rg;             
		rnum++;
	}

	mysql_free_result(m_res);

	return str;
}

//��������
bool VspdCToMySQL::ExecuteSql(const char * SQL,char * Msg)
{
	char sql[2048];
	sprintf_s(sql,SQL);
	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "ExecuteSql Data Error";
		return false;
	}
	return true;
}

//�ر����ݿ�����
void VspdCToMySQL::CloseMySQLConn()
{
	mysql_close(&mysql);
}
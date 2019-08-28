#pragma once

#include <string>
#include "mysql.h"
using   namespace   std;

class VspdCToMySQL
{
public:
	//����
	MYSQL mysql;

	/*
	���캯����ϡ������
	*/
	VspdCToMySQL();
	~VspdCToMySQL();

	/*
	��Ҫ�Ĺ��ܣ�
	��ʼ�����ݿ�
	�������ݿ�
	�����ַ���

	��ڲ�����
	host ��MYSQL������IP
	port:���ݿ�˿�
	Db�����ݿ�����
	user�����ݿ��û�
	passwd�����ݿ��û�������
	charset��ϣ��ʹ�õ��ַ���
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	int ��0��ʾ�ɹ���1��ʾʧ��
	*/
	bool ConnMySQL(char* host, char* port, char* Db, char* user, char* passwd, char* charset, string& strMsg);

	/*
	��Ҫ�Ĺ��ܣ�
	��ѯ����

	��ڲ�����
	SQL����ѯ��SQL���
	Cnum:��ѯ������
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	string ׼�����÷��ص����ݣ�������¼����0x06����,�����λ��0x05����
	��� ���صĳ��ȣ� 0�����ʾ����
	*/
	string SelectData(const char* SQL, int Cnum, char* Msg);

	/*
	��Ҫ���ܣ�
	��������

	��ڲ���
	SQL����ѯ��SQL���
	Msg:���ص���Ϣ������������Ϣ

	���ڲ�����
	int ��0��ʾ�ɹ���1��ʾʧ��
	*/
	bool ExecuteSql(const char* SQL);

	/*
	��Ҫ���ܣ�
	�ر����ݿ�����
	*/
	void CloseMySQLConn();

	void startTransaction();

	void commit();
};

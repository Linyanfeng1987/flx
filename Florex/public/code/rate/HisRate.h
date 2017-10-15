#pragma once
#include <string>

using namespace std;
class HisRate
{
public:
	HisRate(void);
	~HisRate(void);

	string rateName;
	long int time;         // ���ڿ�ʼʱ��
	int timeStepType;
	double   open;         // ���̼�
	double   high;         // ������߼�
	double   low;          // ������ͼ�
	double   close;        // ���̼�
	unsigned int     tick_volume;  // ����������
	int      spread;       // ���
	unsigned int     real_volume;  // ������

	double percentSpead_s;
	string timeFormat;

	string toString();
	void loadByLine(string line);
	string toSqlString();
};


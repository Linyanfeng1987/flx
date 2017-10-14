#pragma once
#include <string>

using namespace std;
class HisRate
{
public:
	HisRate(void);
	~HisRate(void);

	long int time;         // ���ڿ�ʼʱ��
	int timeStepType;
	double   open;         // ���̼�
	double   high;         // ������߼�
	double   low;          // ������ͼ�
	double   close;        // ���̼�
	unsigned int     tick_volume;  // ����������
	int      spread;       // ���
	unsigned int     real_volume;  // ������

	string toString();
};


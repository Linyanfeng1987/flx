#pragma once
#include <string>

using namespace std;

class CProcessConfig
{
public:
	CProcessConfig();
	~CProcessConfig();

	string processName;
	// process�ı�־λ
	int porcessFlag;
	// ��Сʱ�䲽���� ��λ��
	int minTimeStep;

private:
	
};



#pragma once
#include <string>
#include <map>

using namespace std;

class CProcessConfig
{
public:
	CProcessConfig();
	~CProcessConfig();

	string processTypeName;
	// process�ı�־λ
	int porcessFlag;
	// ��Сʱ�䲽���� ��λ��
	int minTimeStep;

	map<string, string> rates;
private:
	
};



#pragma once
#include <string>
#include <map>
#include <list>

using namespace std;
/*
processName����ʶΨһ��һ������
����������ɣ����»�������

processType ��ʶ�㷨�ĺ��Ĳ���
timeStep ��ʶ����ʱ���ȣ�ͨ�����㷨�Ĳ�����������û��ʱ��Ŀ�ȣ���ô��Ϊ0
rate  ��ʶ���õĻ��Ҷ�

�����������processName

�����������εı�ʶ

������ϵ�������������������Դ�������ԭʼ���ݣ���ֱ����rate

dependOnList �洢��������ϵ��
���б�ʶ���� processTypeName �� timeStep�� ����ʹ�õ�ʱ��ƴ��rate��Ψһ��ʶ����

*/

/*
CRow ���ڱ�ʶ������ϵ���Լ�������Ϣ��
*/

class CProcessType
{
public:
	CProcessType();
	~CProcessType();

	string getProcessName();
	string getType();
	bool compare(string strFlag);

public:

	//string rate;
	string processTypeName;

	// process�ı�־λ
	//int porcessFlag;

	// ������ ��λ��
	time_t timeStep;

	list<string> dependOnTypeList;
private:
};

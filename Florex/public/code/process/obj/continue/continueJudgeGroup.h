#pragma once
#include "continueJudgeObj.h"
#include "LinkedHashMap.h"
using namespace std;
class CContinueJudgeGroup
{
public:
	CContinueJudgeGroup(int maxObjNumber, double stepLevelPersent);

	bool isContinueGoOn(int& level, CRateValue& curValue, CRateValue& startValue, CRateValue& tryEndValue, int curDirect );
	int isContinueStart(double& stepPersent);

	void init(double minStepValuePersent, double minStepSpeedPersent, double retrcementValue, double retrcementSpead, double stopSpead);
protected:
	Linked_map<int, PContinueJudgeObj> judgeGroup;

	int maxObjNumber;
	// ÿ������ �ߵȼ�*����= �͵ȼ�
	double stepLevelPersent;


	// ����ﵽ��С���˱����������ڴ�����������, ��λ��ǧ�ֱ�
	double minStepValuePersent;
	double minStepSpeedPersent;
	//////////////////////////////////////////////////////////////////////////
	// �����жϱ���
	// �س�ֵ�����س�С�ڴ�ֵ��Ϊ����δ�жϣ�������Ϊ�����ն�
	double retrcementValue;
	// ����ʼֵ������С���ʣ���λ s?h��
	double stopSpead;
	// �س�����
	double retrcementSpead;
};

typedef shared_ptr<CContinueJudgeGroup> PContinueJudgeGroup;
#define newContinueJudgeGroup(T1,T2) make_shared<CContinueJudgeGroup>(T1,T2);
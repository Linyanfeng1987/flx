#pragma once
#include "continueJudgeObj.h"
#include "LinkedHashMap.h"
#include "process/obj/function/fun1.h"
using namespace std;


class CContinueJudgeGroup
{
public:
	CContinueJudgeGroup(int maxObjNumber, double stepLevelPersent, PBaseFun retrcementCalcFun);

	emumContinueStatus isContinueGoOn(int& level, PRateValue curValue, PRateValue startValue, PRateValue& tryEndValue, int curDirect );
	int isContinueStart(double& stepPersent);

	void init(double minStepValuePersent, double retrcementSpead);
protected:
	Linked_map<int, PContinueJudgeObj> judgeGroup;

	int maxObjNumber;
	// ÿ������ �ߵȼ�*����= �͵ȼ�
	double stepLevelPersent;


	// ����ﵽ��С���˱����������ڴ�����������, ��λ��ǧ�ֱ�
	double minStepValuePersent;
	//double minStepSpeedPersent;
	//////////////////////////////////////////////////////////////////////////
	// �����жϱ���
	// �س�ֵ�����س�С�ڴ�ֵ��Ϊ����δ�жϣ�������Ϊ�����ն�
	double retrcementValue;
	PBaseFun retrcementCalcFun;
	// ����ʼֵ������С���ʣ���λ s?h��
	//double stopSpead;
	// �س�����
	double retrcementSpead;
};

typedef shared_ptr<CContinueJudgeGroup> PContinueJudgeGroup;
#define newContinueJudgeGroup(T1,T2,T3) make_shared<CContinueJudgeGroup>(T1,T2,T3)
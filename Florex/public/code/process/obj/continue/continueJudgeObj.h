#pragma once
#include <list>
#include <map>
#include "process/obj/rateValue.h"
#include "continueValue.h"
#include "LinkedHashMap.h"
#include <memory>

using namespace std;
// �����и����A
// �����з��� 
// �������ж���1�س��ķ��ȣ�

// ��һ��ʱ��Σ�һ�������ϣ�������
// ��ʼ����жϣ���һ�����յ㣿�ǲ�ͬ����ֵ��������ͬ���յ㣿
// ���Զ����ֵ�� ��ֵ��׼ȷ�ԣ� 
// ����������л�ƽ�ʣ�
// ��ζ��巽�����ȷ�ԣ�
// �Ƿ����ͳ�ƣ�manager�� �Ȳ�����manager����

// ˼·��
// 1. Ҫ��ɳɳ�����¼�ɳ����̣�
// 2. �Ǿ�Ҫ֪���ɳ��ı�׼
// 3. �Ƿ���ںϲ���һ˵���ϲ���ԭ��ʱ������������������ǰ���жϣ��ϲ��߼���Ϊ����
// 4. �����߳ɳ����ģ��˼·�Ϻ�
// 5. �ɳ��ı�׼���������У�
// 6. �����Ա��CContinueJudgeObj��������¼�����֣��ɳ�
//				��׼�����飺�������ɣ��洢���л�
//				��׼�����ж���ʼ�������жϣ��ɳ���׼������ֱ�ӱ��ⲿ���ʣ������õ�level��
//				builder����׼�ļ��ϣ���ʼ�����ж�+obj����
//				continus�����obj�Ĵ洢


class CContinueJudgeObj
{
public:
	CContinueJudgeObj(int continueLevel);

	
	
	void init(double minStepValuePersent, double minStepSpeedPersent, double retrcementValue, double retrcementSpead, double stopSpead);

	bool isContinueStart_s(const CRateValue& curValue, CRateValue& startValue);
	bool isContinueStart(double& stepPersent);
	bool isContinueGoOn(CRateValue& curValue, CRateValue& startValue, CRateValue& tryEndValue, int& curDirect);

	int getLevel(){return continueLevel;}
protected:
	bool add(const CRateValue& curValue, CRateValue& startValue, CRateValue& tryEndValue, int& curDirect );
	
	
	// ֹͣ��������¼������������У���µ�����
	//bool stopContinue(CRateValue& stopValue, CRateValue& startValue, CRateValue& tryEndValue);

	// �����ȼ� 
	int continueLevel;

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

typedef shared_ptr<CContinueJudgeObj> PContinueJudgeObj;
#define newContinueJudgeObj(T) make_shared<CContinueJudgeObj>(T);
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

enum emumContinueStatus
{
	continue_stop = -1,  // �ж�
	continue_lowDown,	// ����
	continue_keep,		// ���֣�δ������
	continue_groupUp	// ����
};

class CContinueJudgeObj
{
public:
	CContinueJudgeObj(int continueLevel);

	static double getStepPersent(PRateValue curValue, PRateValue startValue);

	void init(double minStepValuePersent, double retrcementValue, double retrcementSpead);

	bool isContinueStart_s(const PRateValue curValue, PRateValue startValue);
	bool isContinueStart(double& stepPersent);
	//emumContinueStatus isContinueGoOn(PRateValue curValue, PRateValue startValue, PRateValue tryEndValue, int& curDirect, double& curRetrcementSpead, PContinueValue& pContinueValue);
	emumContinueStatus isContinueGoOn(PRateValue curValue, PContinueValue pContinueValue);

	bool isLowDown(double& curRetrcementSpead);
	int getLevel() { return continueLevel; }
protected:
	bool add(const PRateValue curValue, PRateValue startValue, PRateValue tryEndValue, int& curDirect);

	// ֹͣ��������¼������������У���µ�����
	//bool stopContinue(PRateValue stopValue, PRateValue startValue, PRateValue tryEndValue);

	// �����ȼ�
	int continueLevel;

	// ����ﵽ��С���˱����������ڴ�����������, ��λ��ǧ�ֱ�
	double minStepValuePersent;
	//double minStepSpeedPersent;
	//////////////////////////////////////////////////////////////////////////
	// �����жϱ���
	// �س�ֵ�����س�С�ڴ�ֵ��Ϊ����δ�жϣ�������Ϊ�����ն�
	double retrcementValue;
	// ����ʼֵ������С���ʣ���λ s?h��
	//double stopSpead;
	// �س����� ���ڽ��������ȼ�
	double retrcementSpead;
};

typedef shared_ptr<CContinueJudgeObj> PContinueJudgeObj;
#define newContinueJudgeObj(T) make_shared<CContinueJudgeObj>(T)
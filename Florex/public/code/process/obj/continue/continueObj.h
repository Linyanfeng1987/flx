#pragma once
#include <list>
#include <map>
#include "process/obj/rateValue.h"
#include "continueValue.h"
#include "LinkedHashMap.h"
#include <memory>
#include "continueJudgeGroup.h"
#include "process/decision/continueDecision.h"

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
// 6. �����Ա��CContinueObj��������¼�����֣��ɳ�
//				��׼�����飺�������ɣ��洢���л�
//				��׼�����ж���ʼ�������жϣ��ɳ���׼������ֱ�ӱ��ⲿ���ʣ������õ�level
//				builder����׼�ļ��ϣ���ʼ�����ж�+obj����
//				continus�����obj�Ĵ洢


class CContinueObj
{
public:
	CContinueObj(PContinueJudgeGroup pJudgeGroup, list<PContinueDecision> *_decisions);
	void init(PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& judegLevel);

	unsigned long long getTagId(){ return tagId;}

	emumContinueStatus isContinueGoOn(PRateValue curValue);

	void CContinueObj::stopContinue(PRateValue curValue);

	PContinueValue getContinueValue(){return pContinueValue;}

	PContinueJudgeGroup getJudgeGroup(){return pJudgeGroup;}

	int getCurLevel(){return pContinueValue->direct;}
protected:
	void levelChange(int newLevel, PRateValue curValue);
	indexType tagId;
	static indexType tagIdCount;

	// ���� +1 �� -1
	//int curDirect;
	//PRateValue startValue;
	// ͬ������Զ��ֵ
	//PRateValue tryEndValue;

	//int maxLevel;
	// �����ȼ� 
	//int curLevel;
	// �ϴ��ϱ���ֵ
	//CRateValue lastValue;
	//list<int> levelStep;
	emumContinueStatus curStatus;

	PContinueValue pContinueValue;
	PContinueJudgeGroup pJudgeGroup;
	list<PContinueDecision> *decisions;
	int keepCount;
};

typedef shared_ptr<CContinueObj> PContinueObj;
#define newContinueObj(T,T2) make_shared<CContinueObj>(T,T2)
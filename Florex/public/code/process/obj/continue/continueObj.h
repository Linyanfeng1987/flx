#pragma once
#include <list>
#include <map>
#include "process/obj/rateValue.h"
#include "continueValue.h"
#include "LinkedHashMap.h"
#include <memory>
#include "continueJudgeGroup.h"
#include "continueSubsection.h"
#include "continueFinder.h"

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
	CContinueObj(PContinueSubsection pCurSubsection, int curDir);

	void setId(long objId){this->objId = objId;}
	long getId(){ return objId;}

	emumContinueStatus isContinueGoOn(PRateValue curValue);

	list<PContinueSubsection>& getSubsections(){return subsections;}

protected:
	void curLowDown(PRateValue curValue, emumContinueStatus curContinueStatus );
	void curKeep(PRateValue curValue, emumContinueStatus curContinueStatus );

	PContinueSubsection pCurSubsection;
	PContinueSubsection pReserveSubsecton;

	PContinueFinder pFinder;
	list<PContinueSubsection> subsections;
	long objId;
	emumContinueStatus curObjStatus;
	int curDir;
};

typedef shared_ptr<CContinueObj> PContinueObj;
#define newContinueObj(T1,T2) make_shared<CContinueObj>(T1,T2)
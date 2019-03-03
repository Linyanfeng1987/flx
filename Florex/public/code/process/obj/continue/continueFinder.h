#pragma once
#include "continueObj.h"
#include <map>
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


// Ѱ����С������obj�������ɶ���
class CContinueFinder
{
public:
	CContinueFinder(PContinueJudgeGroup pJudgeGroup);
	void setStart(PRateValue curValue, int expDir){this->startValue = curValue; this->expDir = expDir;}
	PContinueObj tryFindNew(PRateValue curValue);
	bool isStart(){return nullptr != startValue;}

	void setId(long finderId){this->finderId = finderId;}
	long getId(){ return finderId;}
protected:
	long finderId;
	int expDir;
	PRateValue startValue;
	PContinueJudgeGroup pJudgeGroup;
};

typedef shared_ptr<CContinueFinder> PContinueFinder;
#define newContinueFinder(T) make_shared<CContinueFinder>(T)
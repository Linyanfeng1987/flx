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

	bool add(PRateValue curValue);
	
	void init();

	void setId(long finderId){this->finderId = finderId;}
	long getId(){ return finderId;}
protected:

	long finderId;

	void tryFindNew(PRateValue curValue);
	void addToObj(PRateValue curValue);
	// ���� +1 �� -1
	//map<int, CRateValue> flagValue;
	//int curContinueDirect;
	PRateValue startValue;

	long objIndex;

	// ֻ����������������һ������һ��
	map<int, PContinueObj> curObjs;
	map<long, PContinueObj> hisObjs;
	PContinueJudgeGroup pJudgeGroup;
};

typedef shared_ptr<CContinueFinder> PContinueFinder;
#define newContinueFinder(T) make_shared<CContinueFinder>(T)
#pragma once
#include "continueObj.h"
#include "continueFinder.h"
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
class CContinueKeeper
{
public:
	CContinueKeeper(PContinueJudgeGroup pJudgeGroup, int curDir);

	bool add(PRateValue curValue, PContinueValueStruct pTableStruct);
	
	void init();

	void setId(long finderId){this->finderId = finderId;}
	long getId(){ return finderId;}
protected:

	long finderId;

	void saveHisObj(PContinueValueStruct pTableStruct);

	//void addToObj(PRateValue curValue, PContinueValueStruct pTableStruct);

	long objIndex;

	int curDir;
	PContinueObj pCurObj;
	PContinueFinder pFinder;
	// ֻ����������������һ������һ��

	//map<int, PContinueObj> curObjs;
	//map<int, PContinueFinder> finders;
	list<PContinueObj> hisObjs;
	PContinueJudgeGroup pJudgeGroup;
	
};

typedef shared_ptr<CContinueKeeper> PContinueKeeper;
#define newContinueKeeper(T1,T2) make_shared<CContinueKeeper>(T1,T2)
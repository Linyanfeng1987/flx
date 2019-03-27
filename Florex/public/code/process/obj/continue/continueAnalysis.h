#pragma once
#include "continueKeeper.h"
#include "rate/rateInfo.h"
using namespace std;

// ������������ӵ�ж��finder
class CContinueAnalysis
{
public:
	CContinueAnalysis(PRateInfo _rateInfo);

	void add(PRateValue value);

protected:
	// ��ʼ��finder
	void init();
	map<long, PContinueKeeper> continueKeepers;
	long keeperIndex;
	PRateInfo rateInfo;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis(T) make_shared<CContinueAnalysis>(T)
#pragma once
#include "../baseAnalysis.h"
#include "continueKeeper.h"
#include "rate/rateInfo.h"
using namespace std;

// ������������ӵ�ж��finder
class CContinueAnalysis : public CBaseAnalysis
{
public:
	CContinueAnalysis(PRateInfo _rateInfo);

	virtual void add(PRateValue value);

protected:
	// ��ʼ��finder
	void init();
	map<long, PContinueKeeper> continueKeepers;
	long keeperIndex;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis(T) make_shared<CContinueAnalysis>(T)
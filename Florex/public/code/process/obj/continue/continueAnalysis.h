#pragma once
#include "../baseAnalysis.h"
#include "continueKeeper.h"
#include "rate/rateInfo.h"
using namespace std;

// ������������ӵ�ж��finder
class CContinueAnalysis : public CBaseAnalysis
{
public:
	using CBaseAnalysis::CBaseAnalysis;
	CContinueAnalysis(PAnalysisInfo _analysisInfo, PRateInfo _rateInfo) :CBaseAnalysis(_analysisInfo, _rateInfo) {}

	virtual void add(PRateValue value);

protected:
	// ��ʼ��finder
	virtual void init();
	map<long, PContinueKeeper> continueKeepers;
	long keeperIndex;

	// 	unsigned int maxMemberSize;
	// 	double minContinueStep;
	// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis(T1,T2) make_shared<CContinueAnalysis>(T1,T2)
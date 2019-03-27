#pragma once
#include "averageObj.h"
#include "rate/rateInfo.h"
using namespace std;

// ������������ӵ�ж��finder
class CAverageAnalysis
{
public:
	CAverageAnalysis(PRateInfo _rateInfo);

	void add(PRateValue value);

protected:
	// ��ʼ��finder
	void init();
	map<long, PAverageObj> averageObjs;
	PRateInfo rateInfo;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CAverageAnalysis> PAverageAnalysis;
#define newAverageAnalysis(T) make_shared<CAverageAnalysis>(T)
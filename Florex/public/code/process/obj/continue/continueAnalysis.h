#pragma once
#include "continueFinder.h"

using namespace std;

// ������������ӵ�ж��finder
class CContinueAnalysis
{
public:
	CContinueAnalysis();

	void add(PRateValue value);

protected:
	// ��ʼ��finder
	void init();
	map<long, PContinueFinder> continueFinders;
	long finderIndex;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis() make_shared<CContinueAnalysis>()
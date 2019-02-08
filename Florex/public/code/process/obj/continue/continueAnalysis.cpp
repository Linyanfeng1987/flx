#include "continueAnalysis.h"
#include "ConstDef.h"
#include "process/obj/function/fun1.h"

CContinueAnalysis::CContinueAnalysis()
{
	finderIndex = 0;
	init();
}

void CContinueAnalysis::add(PRateValue value, PContinueValueStruct pTableStruct)
{
	for (auto conPair : continueFinders)
	{
		conPair.second->add(value, pTableStruct);
	}

	// �������ҵ�������������û��Ԥ��ͼ��ʾ�û������
}

void CContinueAnalysis::init( )
{
	double testParam2 = 0.8;
	PBaseFun retrcementCalcFun = newCFun1(goldenSection, testParam2);
	PContinueJudgeGroup pGroup = newContinueJudgeGroup(15, goldenSection, retrcementCalcFun);
	pGroup->init(basePoint, goldenSection);
	PContinueFinder pFinder = newContinueFinder(pGroup);
	pFinder->setId(finderIndex++);
	continueFinders.insert(make_pair(pFinder->getId(), pFinder));

	double testPersent = 0.9;
	retrcementCalcFun = newCFun1(testPersent, testParam2);
	pGroup = newContinueJudgeGroup(70, testPersent, retrcementCalcFun);
	pGroup->init(basePoint, testPersent);
	pFinder = newContinueFinder(pGroup);
	pFinder->setId(finderIndex++);
	continueFinders.insert(make_pair(pFinder->getId(), pFinder));
}

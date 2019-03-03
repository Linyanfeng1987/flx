#include "continueAnalysis.h"
#include "ConstDef.h"
#include "process/obj/function/fun1.h"

CContinueAnalysis::CContinueAnalysis()
{
	keeperIndex = 0;
	init();
}

void CContinueAnalysis::add(PRateValue value, PContinueValueStruct pTableStruct)
{
	for (auto conPair : continueKeepers)
	{
		conPair.second->add(value, pTableStruct);
	}

	// �������ҵ�������������û��Ԥ��ͼ��ʾ�û������
}

void CContinueAnalysis::init()
{
	PContinueKeeper pKeeper = nullptr;
	PContinueJudgeGroup pGroup = nullptr;
	PBaseFun retrcementCalcFun = nullptr;

	double testParam2 = 0.8;
	retrcementCalcFun = newCFun1(goldenSection, testParam2);
	pGroup = newContinueJudgeGroup(15, goldenSection, retrcementCalcFun);
	pGroup->init(basePoint, goldenSection);
	pKeeper = newContinueKeeper(pGroup, direct_up);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
	pKeeper = newContinueKeeper(pGroup, direct_down);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));

	double testPersent = 0.9;
	retrcementCalcFun = newCFun1(testPersent, 0.95);
	pGroup = newContinueJudgeGroup(70, testPersent, retrcementCalcFun);
	pGroup->init(basePoint, testPersent);
	pKeeper = newContinueKeeper(pGroup, direct_up);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
	pKeeper = newContinueKeeper(pGroup, direct_down);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
}

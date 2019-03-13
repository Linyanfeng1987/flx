#include "continueAnalysis.h"
#include "ConstDef.h"
#include "process/obj/function/fun1.h"
#include "process/decision/continueDecision.h"
#include "PubFun.h"

CContinueAnalysis::CContinueAnalysis(string _rateName)
{
	rateName = _rateName;
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
	list<PContinueDecision> decisions;

	double testParam2 = 0.8;
	for (int i = 3; i <= 5; i++)
	{
		PContinueDecision decision = newContinueDecision(i, rateName, "goldenSection", PubFun::intToString(i));
		decisions.push_back(decision);
	}
	retrcementCalcFun = newCFun1(goldenSection, testParam2);
	pGroup = newContinueJudgeGroup(15, goldenSection, retrcementCalcFun);
	pGroup->init(basePoint, goldenSection);
	pKeeper = newContinueKeeper(pGroup, direct_up, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
	pKeeper = newContinueKeeper(pGroup, direct_down, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));

	double testPersent = 0.9;
	decisions.clear();
	for (int i = 9; i <= 15; i++)
	{
		decisions.push_back(newContinueDecision(i, rateName, "90persent", PubFun::intToString(i)));
	}
	decisions.push_back(newContinueDecision(20, rateName, "90persent", PubFun::intToString(20)));
	decisions.push_back(newContinueDecision(22, rateName, "90persent", PubFun::intToString(22)));
	retrcementCalcFun = newCFun1(testPersent, 0.95);
	pGroup = newContinueJudgeGroup(70, testPersent, retrcementCalcFun);
	pGroup->init(basePoint, testPersent);
	pKeeper = newContinueKeeper(pGroup, direct_up, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
	pKeeper = newContinueKeeper(pGroup, direct_down, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
}

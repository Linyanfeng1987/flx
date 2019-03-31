#include "averageAnalysis.h"
#include "ConstDef.h"
#include "process/obj/function/fun1.h"
#include "process/decision/continueDecision.h"
#include "PubFun.h"

CAverageAnalysis::CAverageAnalysis(PRateInfo _rateInfo):rateInfo(_rateInfo)
{
	init();
}

void CAverageAnalysis::add(PRateValue value)
{
	for (auto obj : averageObjs)
	{
		obj.second->add(value);
	}

	// �������ҵ�������������û��Ԥ��ͼ��ʾ�û������
}

void CAverageAnalysis::init()
{
	double stepTimes[] = {10, 60, 60*15, 60*60, 60*60*4, 60*60*24};

	list<PAverageDecisionTemplate> dTemplates;
	double decisionPersents[] = {0.2, 0.4, 0.6, 0.8, 1};
	for (double decisionPersent : decisionPersents)
	{
		PAverageDecisionTemplate dTemplate = newAverageDecisionTemplate(decisionPersent, decisionPersent*0.5);
		dTemplates.push_back(dTemplate);
	}

	for (double stepTime : stepTimes)
	{
		PAverageObj obj = newAverageObj(dTemplates, rateInfo, stepTime);
		averageObjs.insert(make_pair(obj->getTagId(), obj));
	}
}

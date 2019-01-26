#include "continueAnalysis.h"
#include "ConstDef.h"

CContinueAnalysis::CContinueAnalysis()
{
	finderIndex = 0;
	init();
}

void CContinueAnalysis::add(PRateValue value )
{
	for (auto conPair : continueFinders)
	{
		conPair.second->add(value);
	}

	// �������ҵ�������������û��Ԥ��ͼ��ʾ�û������
}

void CContinueAnalysis::init( )
{
	PContinueJudgeGroup pGroup = newContinueJudgeGroup(100, goldenSection);
	pGroup->init(basePoint, goldenSection, goldenSection);
	PContinueFinder pFinder = newContinueFinder(pGroup);
	pFinder->setId(finderIndex++);
	continueFinders.insert(make_pair(pFinder->getId(), pFinder));
}

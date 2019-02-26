#include "continueFinder.h"
#include <list>
#include "table/Table.h"

CContinueFinder::CContinueFinder( PContinueJudgeGroup pJudgeGroup)
{
	startValue = nullptr;
	this->pJudgeGroup = pJudgeGroup;
}

PContinueSubsection CContinueFinder::tryFindNew( PRateValue curValue )
{
	// ȷ������
	PContinueSubsection pSection = nullptr;
	double stepValue = startValue->value - curValue->value;
	int curDirect = stepValue > 0 ? direct_down : direct_up;
	if (curDirect  == expDir)
	{
		// ������ȷ�����Բ���
		// ��ǰ������û��ͬ��������������ʱ�򣬳����ж��Ƿ������µ�
		double stepPersent = abs(stepValue / curValue->value * basePersentStep);
		int continueLevel = pJudgeGroup->isContinueStart(stepPersent);
		if (-1 != continueLevel)
		{
			// �������
			pSection = newContinueSubsection(pJudgeGroup);
			pSection->init(startValue, curValue, curDirect, continueLevel);

			// �������
			startValue = nullptr;
		}
	}
	else
	{
		// �����෴�����²������
		startValue = curValue;
	}
	return pSection;
}

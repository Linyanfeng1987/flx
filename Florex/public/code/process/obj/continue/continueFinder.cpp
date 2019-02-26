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
	// 确定方向
	PContinueSubsection pSection = nullptr;
	double stepValue = startValue->value - curValue->value;
	int curDirect = stepValue > 0 ? direct_down : direct_up;
	if (curDirect  == expDir)
	{
		// 方向正确，尝试查找
		// 当前容器内没有同方向的连续对象的时候，尝试判断是否生成新的
		double stepPersent = abs(stepValue / curValue->value * basePersentStep);
		int continueLevel = pJudgeGroup->isContinueStart(stepPersent);
		if (-1 != continueLevel)
		{
			// 连续达成
			pSection = newContinueSubsection(pJudgeGroup);
			pSection->init(startValue, curValue, curDirect, continueLevel);

			// 重置起点
			startValue = nullptr;
		}
	}
	else
	{
		// 方向相反，更新查找起点
		startValue = curValue;
	}
	return pSection;
}

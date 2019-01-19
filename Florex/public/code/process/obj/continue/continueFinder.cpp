#include "continueFinder.h"
#include <list>


CContinueFinder::CContinueFinder( PContinueJudgeGroup pJudgeGroup )
{
	objIndex = 0;
	this->pJudgeGroup = pJudgeGroup;
}


// ֻ��¼������С��������ʼ��Ϣ����
bool CContinueFinder::add(CRateValue& curValue)
{
	bool bIsContinue = true;
	
	addToObj(curValue);
	tryFindNew(curValue);
	return bIsContinue;
}

void CContinueFinder::tryFindNew( CRateValue& curValue )
{
	if (!startValue.isValid())
	{
		startValue = curValue;
	}
	else
	{
		// ȷ������
		double stepValue = startValue.value - curValue.value;
		int curDirect = stepValue > 0 ? 1 : -1;
		auto curContinueObjIter = curObjs.find(curDirect);
		if (curObjs.end() == curContinueObjIter)
		{
			// ��ǰ������û��ͬ��������������ʱ�򣬳����ж��Ƿ������µ�
			double stepPersent = abs(stepValue / curValue.value * 1000);
			int continueLevel = pJudgeGroup->isContinueStart(stepPersent);
			if (-1 != continueLevel)
			{
				// �������
				PContinueObj pObj = newContinueObj(pJudgeGroup);
				pObj->init(startValue, curValue, curDirect, continueLevel);
				pObj->setId(++objIndex);
				curObjs.insert(make_pair(curDirect, pObj));

				// �������
				startValue = curValue;
			}
		}
	}
}

void CContinueFinder::addToObj( CRateValue& curValue )
{
	static list<int> rmObjs;
	for (auto objPair : curObjs)
	{
		if (!objPair.second->isContinueGoOn(curValue))
		{
			// �����ж�
			hisObjs.insert(make_pair(objPair.second->getId(), objPair.second));
			rmObjs.push_back(objPair.first);
		}
	}

	for (int rmId : rmObjs)
	{
		curObjs.erase(rmId);
	}

	if (!rmObjs.empty())
	{
		rmObjs.clear();
	}
}

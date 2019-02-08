#include "continueFinder.h"
#include <list>
#include "table/Table.h"

CContinueFinder::CContinueFinder( PContinueJudgeGroup pJudgeGroup)
{
	objIndex = 0;
	startValue = nullptr;
	this->pJudgeGroup = pJudgeGroup;
}


// ֻ��¼������С��������ʼ��Ϣ����
bool CContinueFinder::add(PRateValue curValue, PContinueValueStruct pTableStruct)
{
	addToObj(curValue,pTableStruct);
	tryFindNew(curValue);
	return true;
}

void CContinueFinder::tryFindNew( PRateValue curValue )
{
	if (nullptr == startValue)
	{
		startValue = curValue;
	}
	else
	{
		// ȷ������
		double stepValue = startValue->value - curValue->value;
		int curDirect = stepValue > 0 ? 1 : -1;
		auto curContinueObjIter = curObjs.find(curDirect);
		if (curObjs.end() == curContinueObjIter)
		{
			// ��ǰ������û��ͬ��������������ʱ�򣬳����ж��Ƿ������µ�
			double stepPersent = abs(stepValue / curValue->value * basePersentStep);
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

void CContinueFinder::addToObj( PRateValue curValue, PContinueValueStruct pTableStruct )
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

	if (1000 < hisObjs.size())
	{
		saveHisObj(pTableStruct);
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

void CContinueFinder::saveHisObj(PContinueValueStruct pTableStruct)
{
	PTable pTable = newTable(pTableStruct);
	for (auto hisObjPair : hisObjs)
	{
		PRow pRow = hisObjPair.second->getContinueValue()->buildDbRow(finderId, pTableStruct);
		pTable->addRow(pRow);
	}

	pTable->save();
	hisObjs.clear();
}

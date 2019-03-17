#include "continueKeeper.h"
#include <list>
#include "table/Table.h"

CContinueKeeper::CContinueKeeper(PRateInfo _rateInfo, PContinueJudgeGroup _pJudgeGroup, int _curDir, list<PContinueDecision> &_decisions)
{
	rateInfo = _rateInfo;
	objIndex = 0;
	pJudgeGroup = _pJudgeGroup;
	curDir = _curDir;
	decisions = _decisions;
	pFinder = newContinueFinder(rateInfo, pJudgeGroup, &decisions);
	//finders.insert(make_pair(direct_up, newContinueFinder(pJudgeGroup)));
	//finders.insert(make_pair(direct_down, newContinueFinder(pJudgeGroup)));
}


// ֻ��¼������С��������ʼ��Ϣ����.
bool CContinueKeeper::add(PRateValue curValue, PContinueValueStruct pTableStruct)
{
	if (nullptr == pCurObj)
	{
		// ����
		if(!pFinder->isStart())
		{
			pFinder->setStart(curValue, curDir);
		}
		else
		{
			 pCurObj = pFinder->tryFindNew(curValue);
		}
	}
	else
	{
		if ( continue_stop == pCurObj->isContinueGoOn(curValue))
		{
			// �����ж�
			hisObjs.push_back(pCurObj);
			pCurObj = nullptr;

			if (100 < hisObjs.size())
			{
				saveHisObj(pTableStruct);
			}
		}
	}

	return true;
}

void CContinueKeeper::saveHisObj(PContinueValueStruct pTableStruct)
{
	pTableStruct->ensureExist();
	PTable pTable = newTable(pTableStruct);
	for (auto pHisObj : hisObjs)
	{
		PRow pRow = pHisObj->getContinueValue()->buildDbRow(finderId, pTableStruct);
		pTable->addRow(pRow);
	}

	pTable->save();
	hisObjs.clear();
}

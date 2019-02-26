#include "continueObj.h"

CContinueObj::CContinueObj(PContinueSubsection pCurSubsection, int curDir)
{
	pReserveSubsecton = nullptr;
	curObjStatus = continue_keep;
	this->curDir = curDir;
	this->pCurSubsection = pCurSubsection;
	pFinder = newContinueFinder(pCurSubsection->getJudgeGroup());
}



// �����������ֵ�����Բ����µ�����
// ���µ��������˸��ߵ�ֵ
// �л�������
// ��ǰ�������ж����ж�

//�ƺ���Ҫһ�����󣬷�װһ����ת�������ҵģ���������У��������ظ������ã�С�������ϱ��жϣ�ֱ���滻�ɹ�

emumContinueStatus CContinueObj::isContinueGoOn(PRateValue curValue )
{
	emumContinueStatus curContinueStatus = pCurSubsection->isContinueGoOn(curValue);

	if (continue_stop != curContinueStatus)
	{
		if (continue_lowDown == curObjStatus)
		{
			curLowDown(curValue, curContinueStatus);
		}
		else if(continue_keep <= curObjStatus)
		{
			curKeep(curValue, curContinueStatus);
		}
	}
	else
	{
		subsections.push_back(pCurSubsection);
	}
	return curContinueStatus;
}



void CContinueObj::curLowDown(PRateValue curValue, emumContinueStatus curContinueStatus )
{
	emumContinueStatus resStatus = continue_stop;
	if (nullptr != pReserveSubsecton)
	{
		resStatus = pReserveSubsecton->isContinueGoOn(curValue);
		if (continue_keep <= resStatus 
			&& (pCurSubsection->getCurLevel() - lowDownLevel <= pReserveSubsecton->getCurLevel()
			|| continue_groupUp <= curContinueStatus))
		{
			pCurSubsection->stopContinue(curValue);
			subsections.push_back(pCurSubsection);
			pCurSubsection = pReserveSubsecton;
			pReserveSubsecton = nullptr;
			curObjStatus = continue_keep;
		}
	}
	else
	{
		if (!pFinder->isStart())
		{
			pFinder->setStart(curValue, curDir);
		}
		else
		{
			pReserveSubsecton = pFinder->tryFindNew(curValue);
		}
	}
}

void CContinueObj::curKeep( PRateValue curValue, emumContinueStatus curContinueStatus  )
{
	if (continue_lowDown == curContinueStatus)
	{
		curObjStatus = continue_lowDown;
		curLowDown(curValue, curContinueStatus);
	}
}


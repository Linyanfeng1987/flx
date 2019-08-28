#include "continueJudgeGroup.h"

CContinueJudgeGroup::CContinueJudgeGroup(int maxObjNumber, double stepLevelPersent, PBaseFun retrcementCalcFun)
{
	this->maxObjNumber = maxObjNumber;
	this->stepLevelPersent = stepLevelPersent;
	this->retrcementCalcFun = retrcementCalcFun;
}

/*
emumContinueStatus CContinueJudgeGroup::isContinueGoOn( int& level, PRateValue curValue, PRateValue startValue,
													   PRateValue& tryEndValue, int curDirect, PContinueValue& pContinueValue )
{
	//int correcteLevel=0;@@@@
	// ����򻯵Ŀ����ԣ���ʱ����Ϊ�жϼ����һ���֣�����ʱ����������жϱ���Խ�٣�ʱ������0�����ж�У��ϵ������1
	// levelԽ�ߣ�ʱЧ��Խ����˥��Խ������֮˥��Խ��
	// 0.618(1-0.4^x)^t
	auto pCurJudge = judgeGroup.find(level)->second;
	double curRetrcementSpead = 0;
	emumContinueStatus conStatus = pCurJudge->isContinueGoOn(curValue,startValue,tryEndValue,curDirect, curRetrcementSpead, pContinueValue);
	if (continue_groupUp == conStatus)
	{
		tryEndValue =  curValue;
		int nextLevel = level + 1;
		while (nextLevel <= maxObjNumber)
		{
			// ���Գɳ�
			// �ɳ���Ŀ���Ǳ����������ܵķ��գ���֮ͳ�Ʋ������ж�
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			double stepPersent = CContinueJudgeObj::getStepPersent(curValue, startValue);
			bool bIsGroupUp = pNextJudge->isContinueStart(stepPersent);
			if (bIsGroupUp)
			{
				level = nextLevel;
			}
			else
			{
				break;
			}
			++nextLevel;
		}
	}

	else if (continue_lowDown == conStatus)
	{
		int nextLevel = level - 1;
		while (nextLevel >= 0)
		{
			// ���Խ���
			// ���͵�Ŀ�ģ��������жϣ��ͳɳ���Ŀ�ĳ�ͻ����������ģ�����
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			@@@���ٵľ��������⣬��Ҫ����˼��, ������Ŀ���Ǹ�����С�Ķ���
			bool isLowDown = pNextJudge->isLowDown(curRetrcementSpead);
			if (isLowDown)
			{
				level = nextLevel;
			}
			else
			{
				break;
			}
			--nextLevel;
		}
	}
	else if (continue_stop == conStatus)
	{
		bIsContinue = false;
	}
	return conStatus;
}
*/

emumContinueStatus CContinueJudgeGroup::isContinueGoOn(PRateValue curValue, PContinueValue pContinueValue)
{
	//int correcteLevel=0;@@@@
	// ����򻯵Ŀ����ԣ���ʱ����Ϊ�жϼ����һ���֣�����ʱ����������жϱ���Խ�٣�ʱ������0�����ж�У��ϵ������1
	// levelԽ�ߣ�ʱЧ��Խ����˥��Խ������֮˥��Խ��
	// 0.618(1-0.4^x)^t
	int curLevel = pContinueValue->getCurLevel();
	auto pCurJudge = judgeGroup.find(curLevel)->second;
	double curRetrcementSpead = 0;
	emumContinueStatus conStatus = pCurJudge->isContinueGoOn(curValue, pContinueValue);
	if (continue_groupUp == conStatus)
	{
		pContinueValue->tryEndRateValue = curValue;
		int nextLevel = curLevel + 1;
		while (nextLevel <= maxObjNumber)
		{
			// ���Գɳ�
			// �ɳ���Ŀ���Ǳ����������ܵķ��գ���֮ͳ�Ʋ������ж�
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			double stepPersent = CContinueJudgeObj::getStepPersent(curValue, pContinueValue->startRateValue);
			bool bIsGroupUp = pNextJudge->isContinueStart(stepPersent);
			if (bIsGroupUp)
			{
				pContinueValue->setCurLevel(nextLevel);
			}
			else
			{
				break;
			}
			++nextLevel;
		}
	}
	/*
	else if (continue_lowDown == conStatus)
	{
		int nextLevel = level - 1;
		while (nextLevel >= 0)
		{
			// ���Խ���
			// ���͵�Ŀ�ģ��������жϣ��ͳɳ���Ŀ�ĳ�ͻ����������ģ�����
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			@@@���ٵľ��������⣬��Ҫ����˼��, ������Ŀ���Ǹ�����С�Ķ���
			bool isLowDown = pNextJudge->isLowDown(curRetrcementSpead);
			if (isLowDown)
			{
				level = nextLevel;
			}
			else
			{
				break;
			}
			--nextLevel;
		}
	}
	else if (continue_stop == conStatus)
	{
		bIsContinue = false;
	}*/
	return conStatus;
}

void CContinueJudgeGroup::init(double minStepValuePersent, double retrcementSpead)
{
	this->minStepValuePersent = minStepValuePersent;
	this->retrcementSpead = retrcementSpead;
	double retrcementValue = 0;
	for (int nLevelIndex = 0; nLevelIndex <= maxObjNumber; nLevelIndex++)
	{
		PContinueJudgeObj pObj = newContinueJudgeObj(nLevelIndex);
		// �س�ֵ��Ҫ��̬������ݶ����� 0.618*(1-0.4^x)
		retrcementValue = retrcementCalcFun->calc(nLevelIndex);
		pObj->init(minStepValuePersent, retrcementValue, retrcementSpead);

		minStepValuePersent /= stepLevelPersent;

		judgeGroup.insert(make_pair(nLevelIndex, pObj));
	}
}

int CContinueJudgeGroup::isContinueStart(double& stepPersent)
{
	int level = -1;

	for (auto objPair : judgeGroup)
	{
		if (objPair.second->isContinueStart(stepPersent))
		{
			level = objPair.second->getLevel();
		}
		else
		{
			break;
		}
	}
	return level;
}
#include "continueProcess.h"
#include "db/dataStruct/curRateAverageStruct.h"
#include "PubFun.h"

CContinueProcess::CContinueProcess( PRow pTaskInfo ):CBaseProcess(pTaskInfo)
{
	init(pTaskInfo);
}

CContinueProcess::~CContinueProcess()
{

}

void CContinueProcess::calc( PTable& table )
{
	string pureRateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	string timeName = PubFun::getStepNameByType(timeStepType);
	PCurRateAverageStruct curRateAverageStruct = newCurRateAverageStruct(pureRateName, timeName);
	curRateAverageStruct->ensureExist();
	
	PTable resTable = newTable(curRateAverageStruct);

	// @@@@@����Ӧ������ʷ��¼�����ֱ�
	for (auto rowIter : *table)
	{
		PRateValue pRateValue = CCurRateStruct::getRateValue(rowIter.second);
		pContinueAnalysis->add(pRateValue);
	}
	resTable->save();
}

void CContinueProcess::init( PRow pTaskInfo )
{
	//@@@ ������Ҫ��ȡʱ����ֵ
	string paramter = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);

	map<string, string> resMap;
	PubFun::splitParamStr(paramter, resMap);
	auto iter = resMap.find("timeStep");
	string strTimeStep = "";
	if (resMap.end() != iter )
	{
		strTimeStep = iter->second;
	}
	cycle =  PubFun::stringToInt(strTimeStep);
	timeStepType = PubFun::getStepType(cycle);

	pContinueAnalysis = newContinueAnalysis();
	lastPrice = 0;
}

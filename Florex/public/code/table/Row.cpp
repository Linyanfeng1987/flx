#include "Row.h"
#include "Exception.h"
#include "PubFun.h"

std::string trim(std::string s) 
{
	if (s.empty()) 
	{
		return s;
	}

	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

CRow::CRow(CTableStruct *pTableStruct)
{
	init(pTableStruct);
}

CRow::~CRow(void)
{
}

std::string CRow::getSql()
{
	string strSql = "";
	switch (m_dbType)
	{
	case DBTYPE_NEW:
		{
			strSql = getInsertSql();
		}
		
		break;
	case DBTYPE_SAME:
		{
			strSql = "";
		}
		break;
	case DBTYPE_CHANGE:
		{
			strSql = getUpdateSql();
		}
		break;
	case DETYPE_DELETE:
		{
			strSql = getDeleteSql();
		}
		break;
	default:
		{
			strSql = "";
		}
		break;
	}

	return strSql;
}

std::string CRow::getInsertSql()
{
	static string strBaseSqlFormat = "";
	if(strBaseSqlFormat.empty())
	{
		strBaseSqlFormat = getBaseInsertSqlFormat();
	}

	char chSql[2048] = {0};
	string strTmp = "";
	CRow::iterator rowIter;
	strTmp.clear();
	rowIter = this->begin();
	for (; rowIter != this->end(); rowIter++)
	{
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += rowIter->second;	
	}
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp.c_str());

	return string(chSql);
}

std::string CRow::getBaseInsertSqlFormat()
{
	string strBaseSqlFormat = "";
	strBaseSqlFormat += "insert into ";
	strBaseSqlFormat += m_pTableStruct->tableName;
	strBaseSqlFormat += " (";
	CTableStruct::iterator fieldIter = m_pTableStruct->begin();
	string strTmp = "";
	for(unsigned int i = 0;i < m_pTableStruct->size();i++, fieldIter++)
	{
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += fieldIter->first;
	}
	strBaseSqlFormat += strTmp;
	strBaseSqlFormat += ")";
	strBaseSqlFormat += " value";
	strBaseSqlFormat += " ( ";
	strBaseSqlFormat += "%s";
	strBaseSqlFormat += " )";
	strBaseSqlFormat += ";";

	return strBaseSqlFormat;
}

std::string CRow::getUpdateSql()
{
	static string strBaseSqlFormat = "";
	if(strBaseSqlFormat.empty())
	{
		strBaseSqlFormat = getBaseUpdateSqlFormat();
	}

	char chSql[2048] = {0};
	string strTmp = "";
	CRow::iterator rowIter;
	strTmp.clear();
	rowIter = this->begin();
	for (; rowIter != this->end(); rowIter++)
	{
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += rowIter->first;
		strTmp += "=";
		strTmp += rowIter->second;
	}
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp.c_str());

	return string(chSql);
}

//UPDATE tbl_name SET col_name1=value1, col_name2=value2, … WHERE conditions
std::string CRow::getBaseUpdateSqlFormat()
{
	string strBaseSqlFormat = "";
	strBaseSqlFormat += "update ";
	strBaseSqlFormat += m_pTableStruct->tableName;
	strBaseSqlFormat += " set ";
	strBaseSqlFormat += "%s";
	strBaseSqlFormat += getConditionFormat();
	strBaseSqlFormat += ";";

	return strBaseSqlFormat;
}

std::string CRow::getDeleteSql()
{
	string strSql = "delete from ";
	strSql += m_pTableStruct->tableName;
	string strCondition = getConditionFormat();
	if (trim(strCondition).empty())
	{
		//不允许不带条件删除，避免清空表
		throw Exception("error condition");
	}
	strSql += strCondition;
	strSql += ";";
	return strSql;
}

// where a = A and b = B
std::string CRow::getConditionFormat()
{
	string strSql = "";
	CTableStruct::iterator fieldIter;
	CRow::iterator iter = this->begin();
	for(;iter != this->end(); iter++)
	{
		fieldIter = m_pTableStruct->find(iter->first);
 		if (fieldIter->second.bIsPk)
 		{
			if (!strSql.empty())
			{
				strSql += " and ";
			}

			strSql += iter->first;
			strSql += "=";
			strSql += iter->second;
		}
	}
	
	if (!strSql.empty())
	{
		strSql = " where " + strSql;
	}

	return strSql;
}

void CRow::init( CTableStruct *pTableStruct )
{
	setTableStruct(pTableStruct);
}

void CRow::setAndaddValue( string strKey, string strValue )
{
	if (m_pTableStruct->find(strKey) != m_pTableStruct->end())
	{
		CRow::iterator iter = this->find(strKey);
		if (iter != this->end())
		{
			iter->second = strValue;
		}
		else
		{
			std::pair<CRow::iterator, bool> pr = this->insert(make_pair(strKey,strValue));
			if (!pr.second)
			{
				throw Exception("setAndaddValue error.");
			}
		}
	}
}

void CRow::addByList( list<string> valueList )
{
	if (valueList.size() != m_pTableStruct->size())
	{
		throw Exception("addByList error.");
	}
	list<string>::iterator valueIter= valueList.begin();
	CTableStruct::iterator fieldIter = m_pTableStruct->begin();
	for (; valueIter != valueList.end();valueIter++, fieldIter++)
	{
		setAndaddValue(fieldIter->first, *valueIter);
	}
}

std::string CRow::getValue( string strKey )
{
	string destValue = "";
	if (m_pTableStruct->find(strKey) != m_pTableStruct->end())
	{
		CRow::iterator iter = this->find(strKey);
		if (iter != this->end())
		{
			destValue = iter->second;
		}
		else
		{
			destValue = "";
		}
	}
	return destValue;
}

void CRow::setValue( string strKey, string strValue )
{
	auto iter = this->find(strKey);
	if(iter != this->end())
	{
		iter->second = strValue;
	}
	else
	{
		this->insert(make_pair(strKey, strValue));
	}
}


std::string CRow::getStringValue(string strKey)
{
	return this->getValue(strKey);
}

long CRow::getIntValue(string strKey)
{
	return PubFun::stringToInt(this->getValue(strKey));
}

time_t CRow::getTimeValue(string strKey)
{
	return PubFun::stringToInt(this->getValue(strKey));
}

double CRow::getDoubleValue(string strKey)
{
	return PubFun::stringToDouble(this->getValue(strKey));
}

void CRow::setStringValue(string strKey, string strValue )
{
	this->setValue(strKey, strValue);
}

void CRow::setIntValue(string strKey, long lValue )
{
	this->setValue(strKey, PubFun::intToString(lValue));
}

void CRow::setTimeValue(string strKey, time_t tValue )
{
	this->setValue(strKey, PubFun::intToString(tValue));
}

void CRow::setDoubleValue(string strKey, double dValue )
{
	this->setValue(strKey, PubFun::doubleToString(dValue));
}


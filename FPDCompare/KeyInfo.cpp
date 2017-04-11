#include "StdAfx.h"
#include "KeyInfo.h"
#include "MetaProperty.h"
#include "ConfigurationStorage.h"
#include "MetaPropertyValue.h"

CKeyInfo::CKeyInfo(void)
{
	m_KeyValue = NULL;
	m_bMatched = false;
	m_bIsInvalid = false;	
	m_HashValue = 0;
}


CKeyInfo::~CKeyInfo(void)
{
	delete m_KeyValue;
}

//************************************
// Method:    Compare
// FullName:  CKeyInfo::Compare
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: CKeyInfo * pKeyInfo
// Parameter: bool & out_return
//************************************
Status CKeyInfo::Compare(CKeyInfo *pKeyInfo,bool &out_return)
{
	out_return = false;

	if (NULL == pKeyInfo)
	{		
		return FAILURE;
	}

	List_Wstr KeyAttributes;
	Wstring szThisDifference;
	Wstring szOtherDifference;
	unsigned short usCompareCount = 0;

	List_Wstr::const_iterator AttributeListIterator;
	CConfigurationStorage::getInstance()->GetKeyAttributeList(KeyAttributes);	

	CKey *pKeyThis = this->m_KeyValue;
	CKey *pKeyOther = pKeyInfo->m_KeyValue;	

	if (pKeyThis->m_HashValue == pKeyOther->m_HashValue)
	{
		if ((pKeyThis->m_Properties.size() == pKeyOther->m_Properties.size()) && (pKeyThis->m_Properties.size() == KeyAttributes.size()))
		{
			Status retCompare = pKeyThis->Compare(pKeyOther,szThisDifference,szOtherDifference,out_return);
			if (FAILURE == retCompare)
			{
				// log error
				return FAILURE;
			}
		}
		
	}

	return SUCCESS;
}

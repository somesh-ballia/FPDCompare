#include "StdAfx.h"
#include "MetaPropertyValue.h"


CMetaPropertyValue::CMetaPropertyValue(void)
{
	m_Multiplicity = false;
	m_Matched = false;	
	m_uHashValue = 0;
	m_Datatype = DATATYPE_UNKNOWN;
}


//************************************
// Method:    ~CMetaPropertyValue
// FullName:  CMetaPropertyValue::~CMetaPropertyValue
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: void
//************************************
CMetaPropertyValue::~CMetaPropertyValue(void)
{
	std::list<CMetaPropertySubValue*>::iterator ListSubValuesIterator;
	for (ListSubValuesIterator = this->m_ListSubValues.begin();ListSubValuesIterator != this->m_ListSubValues.end();)
	{
		CMetaPropertySubValue *pMetaPropertySubValue = *ListSubValuesIterator;
		ListSubValuesIterator++;
		delete pMetaPropertySubValue;
	}
	this->m_ListSubValues.clear();
}

//************************************
// Method:    Compare
// FullName:  CMetaPropertyValue::Compare
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: CMetaPropertyValue * pMetaPropertyValue
// Parameter: bool & out_result
//************************************
Status CMetaPropertyValue::Compare(CMetaPropertyValue *pMetaPropertyValue,bool &out_result)
{
	out_result = false;

	if (NULL == pMetaPropertyValue)
	{
		return FAILURE;
	}

	if (this->m_uHashValue != pMetaPropertyValue->m_uHashValue)
	{
		return SUCCESS;
	}

	if (this->m_Datatype != pMetaPropertyValue->m_Datatype)
	{
		return SUCCESS;
	}

	if (this->m_Multiplicity != pMetaPropertyValue->m_Multiplicity)
	{
		return SUCCESS;
	}

	if (this->m_ListSubValues.size() != pMetaPropertyValue->m_ListSubValues.size())
	{
		return SUCCESS;
	}

	std::list<CMetaPropertySubValue*>::const_iterator ListIteratorThis;
	std::list<CMetaPropertySubValue*>::const_iterator ListIteratorOther;

	int iCount = 0;

	ListIteratorThis = this->m_ListSubValues.begin();
	ListIteratorOther = pMetaPropertyValue->m_ListSubValues.begin();
	
	while(ListIteratorThis != this->m_ListSubValues.end())
	{
		CMetaPropertySubValue *pMetaPropertySubValue = *ListIteratorThis;
		if (pMetaPropertySubValue->Compare(*ListIteratorOther))
		{
			iCount++;
			ListIteratorThis++;
			ListIteratorOther++;
		}
		else
		{
			break;
		}
	}	
	if (iCount == pMetaPropertyValue->m_ListSubValues.size())
	{
		out_result = true;
	}
	else
	{
		out_result = false;
	}
	
	return SUCCESS;
}

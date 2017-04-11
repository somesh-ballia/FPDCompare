#include "StdAfx.h"
#include "MetaProperty.h"
#include "MetaPropertySubValue.h"
#include "MetaPropertSubValue_String.h"
#include "LogManager.h"

CMetaPropertySet::CMetaPropertySet(void)
{
	m_HashValue = 0;
}

//************************************
// Method:    ~CMetaPropertySet
// FullName:  CMetaPropertySet::~CMetaPropertySet
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: void
//************************************
CMetaPropertySet::~CMetaPropertySet(void)
{
	std::map<std::wstring,CMetaPropertyValue*>::const_iterator Iterator;
	for(Iterator = this->m_Properties.begin();Iterator != this->m_Properties.end();)
	{
		CMetaPropertyValue *pMetaPropertyValue = (*Iterator).second;	
		Iterator++;
		delete pMetaPropertyValue;	
	}
	this->m_Properties.clear();	
}

//************************************
// Method:    Compare
// FullName:  CMetaPropertySet::Compare
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: CMetaPropertySet * pMetaPropertySet
// Parameter: Wstring & szThisDifferenceDetails
// Parameter: Wstring & szOtherDifferenceDetails
// Parameter: bool & out_result
//************************************
Status CMetaPropertySet::Compare(CMetaPropertySet *pMetaPropertySet,Wstring &szThisDifferenceDetails,Wstring &szOtherDifferenceDetails,bool &out_result)
{
	out_result = false;
	bool bIsMatching = false;

	unsigned short usCompareCount = 0;
	unsigned short usCompareTotal = 0;
	unsigned short usCountTotalThis = 0;
	unsigned short usCountTotalOther = 0;

	std::map<std::wstring,CMetaPropertyValue*>::const_iterator MapIteratorThis;
	std::map<std::wstring,CMetaPropertyValue*>::const_iterator MapIteratorOther;

	if (NULL == pMetaPropertySet)
	{
		return FAILURE;
	}

	usCountTotalThis = this->m_Properties.size();
	usCountTotalOther = pMetaPropertySet->m_Properties.size();	

	usCompareTotal =  ( usCountTotalThis>=usCountTotalOther) ?   usCountTotalThis : usCountTotalOther;				

	for(MapIteratorThis = this->m_Properties.begin();MapIteratorThis != this->m_Properties.end();MapIteratorThis++)
	{
		CMetaPropertyValue *pMetaPropertyValueThis = (*MapIteratorThis).second;
		CMetaPropertyValue *pMetaPropertyValueOther = (pMetaPropertySet->m_Properties[(*MapIteratorThis).first]); 
		bool out_return_temp = false;

		if(NULL == pMetaPropertyValueThis)
		{			
			szThisDifferenceDetails.append((*MapIteratorThis).first+L",");
			continue;
		}

		if (NULL == pMetaPropertyValueOther)
		{
			szOtherDifferenceDetails.append((*MapIteratorThis).first+L",");
			continue;
		}

		if (SUCCESS == pMetaPropertyValueThis->Compare(pMetaPropertyValueOther,out_return_temp))
		{
			if (out_return_temp)
			{
				usCompareCount++;
			}
			else
			{
				szThisDifferenceDetails.append((*MapIteratorThis).first+L","); 
			}
		}
		else
		{			
			String szMessage = "Error Compairing attributes CMetaPropertySet::Compare  ";				
			CLogManager::CreateLog(LOG_ERROR,szMessage);
		}	
	}	

	if (usCompareCount == usCompareTotal)
	{
		bIsMatching = true;
	}
	else
	{
		bIsMatching = false;
	}	

	usCompareCount = 0;

	for(MapIteratorOther = pMetaPropertySet->m_Properties.begin();MapIteratorOther != pMetaPropertySet->m_Properties.end();MapIteratorOther++)
	{
	
		CMetaPropertyValue *pMetaPropertyValueOther = (*MapIteratorOther).second;
		CMetaPropertyValue *pMetaPropertyValueThis = (pMetaPropertySet->m_Properties[(*MapIteratorOther).first]); 
		 
		bool out_return_temp = false;

		if(NULL == pMetaPropertyValueThis)
		{			
			szThisDifferenceDetails.append((*MapIteratorOther).first+L",");
			continue;
		}

		if (NULL == pMetaPropertyValueOther)
		{
			szOtherDifferenceDetails.append((*MapIteratorOther).first+L",");
			continue;
		}

		if (pMetaPropertyValueThis->m_uHashValue == pMetaPropertyValueOther->m_uHashValue)
		{
			if (SUCCESS == pMetaPropertyValueThis->Compare(pMetaPropertyValueOther,out_return_temp))
			{
				if (out_return_temp)
				{
					usCompareCount++;
				}
				else
				{
					szOtherDifferenceDetails.append((*MapIteratorOther).first+L","); 
				}
			}
			else
			{				
				String szMessage = "Error Compairing attributes CMetaPropertySet::Compare  ";				
				CLogManager::CreateLog(LOG_ERROR,szMessage);
			}
		}
		else
		{
			szOtherDifferenceDetails.append((*MapIteratorThis).first+L","); 
		}		
	}
	if ((usCompareCount == usCompareTotal) && (true == bIsMatching))
	{
		out_result = true;			
	}	
		
	return SUCCESS;
}

//************************************
// Method:    GetAttributeValue
// FullName:  CMetaPropertySet::GetAttributeValue
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const Wstring & in_szAttributeName
// Parameter: Wstring & out_szAttributeValue
//************************************
Status CMetaPropertySet::GetAttributeValue(const Wstring &in_szAttributeName,Wstring &out_szAttributeValue)
{
	CMetaPropertyValue *pMetaPropertyValue = m_Properties[in_szAttributeName];
	if(NULL == pMetaPropertyValue)
	{
		return FAILURE;
	}
	
	switch(pMetaPropertyValue->m_Datatype)
	{
	case DATATYPE_STRING:
		std::list<CMetaPropertySubValue*> MetaPropertySubValueList = pMetaPropertyValue->m_ListSubValues;
		if(0 == MetaPropertySubValueList.size())
		{
			return FAILURE;
		}
		std::list<CMetaPropertSubValue_String*> MetaPropertySubValue_StringList;
		if(SUCCESS == ConvertList(MetaPropertySubValueList,MetaPropertySubValue_StringList))
		{
			std::list<CMetaPropertSubValue_String*>::const_iterator ListIterator;
			if(0 == MetaPropertySubValue_StringList.size())
			{
				return FAILURE;
			}

			ListIterator = MetaPropertySubValue_StringList.begin();
			CMetaPropertSubValue_String *pMetaPropertySubValue_String = *ListIterator;
			if(NULL == pMetaPropertySubValue_String)
			{
				return FAILURE;
			}
			out_szAttributeValue = pMetaPropertySubValue_String->m_Value;
		}
	}
	return SUCCESS;
}

//************************************
// Method:    ConvertList
// FullName:  CMetaPropertySet::ConvertList
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const std::list<CMetaPropertySubValue * > & ListMetaPropertySubValue
// Parameter: std::list<CMetaPropertSubValue_String * > & ListMetaPropertySubValue_String
//************************************
Status CMetaPropertySet::ConvertList(const std::list<CMetaPropertySubValue*> &ListMetaPropertySubValue,
	std::list<CMetaPropertSubValue_String*> &ListMetaPropertySubValue_String)
{
	std::list<CMetaPropertySubValue*>::const_iterator ListIterator;
	for(ListIterator = ListMetaPropertySubValue.begin();ListIterator != ListMetaPropertySubValue.end();ListIterator++)
	{
		CMetaPropertSubValue_String *pValue = static_cast<CMetaPropertSubValue_String*> (*ListIterator);
		ListMetaPropertySubValue_String.push_back(pValue);
	}
	return SUCCESS;
}
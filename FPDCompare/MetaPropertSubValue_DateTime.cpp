#include "StdAfx.h"
#include "MetaPropertSubValue_DateTime.h"


CMetaPropertSubValue_DateTime::CMetaPropertSubValue_DateTime(void)
{
	m_Value = 0;
}


CMetaPropertSubValue_DateTime::~CMetaPropertSubValue_DateTime(void)
{
}

//************************************
// Method:    Compare
// FullName:  CMetaPropertSubValue_DateTime::Compare
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
//************************************
bool CMetaPropertSubValue_DateTime::Compare(CMetaPropertySubValue *pMetaPropertySubValue)
{
	CMetaPropertSubValue_DateTime *pMetaPropertySubValue_DateTime = static_cast<CMetaPropertSubValue_DateTime*>(pMetaPropertySubValue);
	if(this->m_Value == pMetaPropertySubValue_DateTime->m_Value)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

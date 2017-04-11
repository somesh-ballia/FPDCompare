#include "StdAfx.h"
#include "MetaPropertSubValue_Integer.h"


CMetaPropertSubValue_Integer::CMetaPropertSubValue_Integer(void)
{
	m_Value = 0;
}

CMetaPropertSubValue_Integer::~CMetaPropertSubValue_Integer(void)
{
}

//************************************
// Method:    Compare
// FullName:  CMetaPropertSubValue_Integer::Compare
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
//************************************
bool CMetaPropertSubValue_Integer::Compare(CMetaPropertySubValue *pMetaPropertySubValue)
{
	CMetaPropertSubValue_Integer *pMetaPropertySubValue_Integer = static_cast<CMetaPropertSubValue_Integer*>(pMetaPropertySubValue);
	if (this->m_Value == pMetaPropertySubValue_Integer->m_Value)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

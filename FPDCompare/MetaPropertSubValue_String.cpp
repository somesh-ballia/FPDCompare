#include "StdAfx.h"
#include "MetaPropertSubValue_String.h"


CMetaPropertSubValue_String::CMetaPropertSubValue_String(void)
{
}


CMetaPropertSubValue_String::~CMetaPropertSubValue_String(void)
{	
}

//************************************
// Method:    Compare
// FullName:  CMetaPropertSubValue_String::Compare
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
//************************************
bool CMetaPropertSubValue_String::Compare(CMetaPropertySubValue *pMetaPropertySubValue)
{
	CMetaPropertSubValue_String *pMetaPropertSubValue_String = static_cast<CMetaPropertSubValue_String*>(pMetaPropertySubValue);
	if (!(this->m_Value.compare(pMetaPropertSubValue_String->m_Value)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

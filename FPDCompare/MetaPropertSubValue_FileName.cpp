#include "StdAfx.h"
#include "MetaPropertSubValue_FileName.h"


CMetaPropertSubValue_FileName::CMetaPropertSubValue_FileName(void)
{
}


CMetaPropertSubValue_FileName::~CMetaPropertSubValue_FileName(void)
{
}

//************************************
// Method:    Compare
// FullName:  CMetaPropertSubValue_FileName::Compare
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
//************************************
bool CMetaPropertSubValue_FileName::Compare(CMetaPropertySubValue *pMetaPropertySubValue)
{
	CMetaPropertSubValue_FileName *pMetaPropertySubValue_FileName = static_cast<CMetaPropertSubValue_FileName*>(pMetaPropertySubValue);
	if(!(this->m_Value.compare(pMetaPropertySubValue_FileName->m_Value)))
	{
		return true;
	}
	else
	{
		return false;
	}	
}

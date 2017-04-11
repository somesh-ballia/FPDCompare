#pragma once


 /***************************************************************************
 *																			*
 *																			*
 * Copyright 2001-02 by Cleartrail Technologies, Inc. All rights reserved.	*
 *																			*
 * Warning:  This program is the unpublished, proprietary property of		*
 * 'Cleartrail Technologies, Inc.' and is to be maintained in strict		*
 * confidence. Unauthorized reproduction, distribution or disclosure of		*
 * this program, or any program derived from it is prohibited by State		*
 * and Federal law.															*
 ****************************************************************************/

#include "MetaPropertySubValue.h"

class CMetaPropertyValue
{
public:
	CMetaPropertyValue(void);
   ~CMetaPropertyValue(void);

	std::list<CMetaPropertySubValue*> m_ListSubValues;
	UINT32							  m_uHashValue;
	unsigned short					  m_Datatype;
	bool							  m_Multiplicity;	
	bool							  m_Matched;	

	//************************************
	// Method:    Compare
	// FullName:  CMetaPropertyValue::Compare
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: CMetaPropertyValue * pMetaPropertyValue
	// Parameter: bool & out_result
	//************************************
	Status Compare(CMetaPropertyValue *pMetaPropertyValue,bool &out_result);
};


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
class CMetaPropertSubValue_String : public CMetaPropertySubValue
{
public:
	CMetaPropertSubValue_String(void);
	~CMetaPropertSubValue_String(void);
	Wstring m_Value;

	//************************************
	// Method:    Compare
	// FullName:  CMetaPropertSubValue_String::Compare
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
	//************************************
	bool Compare (CMetaPropertySubValue *pMetaPropertySubValue);
};


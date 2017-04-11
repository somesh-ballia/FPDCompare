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
class CMetaPropertSubValue_DateTime : public CMetaPropertySubValue
{
public:
	CMetaPropertSubValue_DateTime(void);
	~CMetaPropertSubValue_DateTime(void);
	unsigned int m_Value;

	//************************************
	// Method:    Compare
	// FullName:  CMetaPropertSubValue_DateTime::Compare
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
	//************************************
	bool Compare (CMetaPropertySubValue *pMetaPropertySubValue);

};


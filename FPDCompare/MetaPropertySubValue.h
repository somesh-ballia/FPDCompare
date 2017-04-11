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

class CMetaPropertSubValue_String;
class CMetaPropertSubValue_Integer;
class CMetaPropertSubValue_DateTime;
class CMetaPropertSubValue_FileName;

class CMetaPropertySubValue
{
public:
	CMetaPropertySubValue(void);
	virtual ~CMetaPropertySubValue(void);
	//************************************
	// Method:    Compare
	// FullName:  CMetaPropertySubValue::Compare
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier:
	// Parameter: CMetaPropertySubValue * pMetaPropertySubValue
	//************************************
	virtual bool Compare (CMetaPropertySubValue *pMetaPropertySubValue) = 0;
};


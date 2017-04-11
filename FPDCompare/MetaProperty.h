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

#include "MetaPropertyValue.h"

class CMetaPropertySet
{

public:
	CMetaPropertySet(void);
	~CMetaPropertySet(void);
	std::map<Wstring,CMetaPropertyValue*>									m_Properties;
	UINT32																	m_HashValue;

	//************************************
	// Method:    GetAttributeValue
	// FullName:  CMetaPropertySet::GetAttributeValue
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Wstring & in_szAttributeName
	// Parameter: Wstring & out_szAttributeValue
	//************************************
	Status GetAttributeValue(const Wstring									&in_szAttributeName,
							 Wstring										&out_szAttributeValue
							 );

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
	Status Compare(CMetaPropertySet											*pMetaPropertySet,
					Wstring													&szThisDifferenceDetails,
					Wstring													&szOtherDifferenceDetails,
					bool													&out_result
					);

private:
	//************************************
	// Method:    ConvertList
	// FullName:  CMetaPropertySet::ConvertList
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const std::list<CMetaPropertySubValue * > & ListMetaPropertySubValue
	// Parameter: std::list<CMetaPropertSubValue_String * > & ListMetaPropertySubValue_String
	//************************************
	Status ConvertList(const std::list<CMetaPropertySubValue*>				&ListMetaPropertySubValue,
							  std::list<CMetaPropertSubValue_String*>		&ListMetaPropertySubValue_String
							  );

};


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

class CMetaPropertySet;
class CMetaReader
{
public:
	CMetaReader(void);
	~CMetaReader(void);

	//************************************
	// Method:    ReadMetaFile
	// FullName:  CMetaReader::ReadMetaFile
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szMetaFilePath
	// Parameter: CMetaPropertySet * pMetaProperty
	// Parameter: const bool bCalculateHash
	//************************************
	Status ReadMetaFile	(
		const String						&szMetaFilePath,						
		CMetaPropertySet					*pMetaProperty,
		const bool							bCalculateHash
		); 
private:
	//************************************
	// Method:    ParseBuffer
	// FullName:  CMetaReader::ParseBuffer
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Wstring & szBuffer
	// Parameter: CMetaPropertySet * pMetaProperty
	// Parameter: const bool bCalculateHash
	//************************************
	Status ParseBuffer(
		const Wstring						&szBuffer,
		CMetaPropertySet					*pMetaProperty,
		const bool							bCalculateHash
		);

	//************************************
	// Method:    GetDatatype
	// FullName:  CMetaReader::GetDatatype
	// Access:    private 
	// Returns:   Datatype
	// Qualifier:
	// Parameter: const Wstring & szBuffer
	// Parameter: unsigned short & sEndOffset
	//************************************
	Datatype GetDatatype(
		const Wstring						&szBuffer,
		unsigned short						&sEndOffset
		);

	//************************************
	// Method:    GetMultiplicity
	// FullName:  CMetaReader::GetMultiplicity
	// Access:    private 
	// Returns:   Multiplicity
	// Qualifier:
	// Parameter: const Wstring & szBuffer
	// Parameter: unsigned short & sOffset
	//************************************
	Multiplicity GetMultiplicity(
		const Wstring						&szBuffer,
		unsigned short						&sOffset
		);

	//************************************
	// Method:    GetAttributeName
	// FullName:  CMetaReader::GetAttributeName
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Wstring & szBuffer
	// Parameter: unsigned short & sOffset
	// Parameter: Wstring & szAttributeName
	//************************************
	Status GetAttributeName(
		const Wstring						&szBuffer,
		unsigned short						&sOffset,
		Wstring								&szAttributeName
		);

	//************************************
	// Method:    GetAttributeValue
	// FullName:  CMetaReader::GetAttributeValue
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Wstring & szBuffer
	// Parameter: unsigned short & sOffset
	// Parameter: Wstring & szAttributeValue
	//************************************
	Status GetAttributeValue(
		const Wstring						&szBuffer,
		unsigned short						&sOffset,
		Wstring								&szAttributeValue
		);

	//************************************
	// Method:    GetMultipleValue
	// FullName:  CMetaReader::GetMultipleValue
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Wstring & szAttributeValue
	// Parameter: List_Wstr & ListMultipleValues
	//************************************
	Status GetMultipleValue(
		const Wstring						&szAttributeValue,
		List_Wstr							&ListMultipleValues
		);

	//************************************
	// Method:    IgnoreAttribute
	// FullName:  CMetaReader::IgnoreAttribute
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Wstring & szAttributeName
	// Parameter: const List_Wstr & IgnoreList
	//************************************
	Status IgnoreAttribute(
		const Wstring						&szAttributeName,
		const List_Wstr						&IgnoreList
		);

	//************************************
	// Method:    GetNewOffset
	// FullName:  CMetaReader::GetNewOffset
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: const Wstring & szBuffer
	// Parameter: WCHAR wchDelimeter
	// Parameter: unsigned short & sOffset
	//************************************
	void GetNewOffset(
		const Wstring						&szBuffer,
		WCHAR								wchDelimeter,
		unsigned short						&sOffset
		);

	//************************************
	// Method:    FillMetaPropertyValue
	// FullName:  CMetaReader::FillMetaPropertyValue
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const Datatype & dtDatatype
	// Parameter: const Multiplicity & mMultiplicity
	// Parameter: const Wstring & szAttributeName
	// Parameter: const List_Wstr & ListValue
	// Parameter: CMetaPropertySet * pMetaProperty
	// Parameter: const bool bCalculateHash
	//************************************
	Status FillMetaPropertyValue(
		const Datatype						&dtDatatype,
		const Multiplicity					&mMultiplicity,
		const Wstring						&szAttributeName,
		const List_Wstr						&ListValue,
		CMetaPropertySet					*pMetaProperty,
		const bool							bCalculateHash
		);

};


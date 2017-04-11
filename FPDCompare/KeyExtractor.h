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
class CKeyExtractor
{
public:
	CKeyExtractor(void);
	~CKeyExtractor(void);

	//************************************
	// Method:    ExtractKey
	// FullName:  CKeyExtractor::ExtractKey
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szMetaFilePath
	// Parameter: CKey * pKeyValue
	// Parameter: UINT32 & uiHashValue
	//************************************
	Status ExtractKey(
		const String					&szMetaFilePath,
		CKey							*pKeyValue, 
		UINT32							&uiHashValue
		);
private:	

	//************************************
	// Method:    FetchMetaFileInfo
	// FullName:  CKeyExtractor::FetchMetaFileInfo
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const std::string szMetaFilePath
	// Parameter: CMetaPropertySet * * pMetaProperty
	//************************************
	Status FetchMetaFileInfo(
		const std::string				szMetaFilePath,
		CMetaPropertySet				**pMetaProperty		
		);
};


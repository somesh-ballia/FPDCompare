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
#include "CommonAll.h"

using namespace std;

class CKeyInfo;
class CFPDReader
{
public:
	CFPDReader(void);
	~CFPDReader(void);

	//************************************
	// Method:    ProcessDirectory
	// FullName:  CFPDReader::ProcessDirectory
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szDirectoryPath
	// Parameter: List_Str & InvalidPathList
	// Parameter: list<CKeyInfo * > & KeyInfoList
	// Parameter: std::list<CKeyInfo * > * HashMapBase
	//************************************
	Status ProcessDirectory(
		const String											&szDirectoryPath, 
		List_Str												&InvalidPathList,
		list<CKeyInfo*>											&KeyInfoList,
		std::list<CKeyInfo*>									*HashMapBase
		);
private:

	//************************************
	// Method:    HashMapInsert
	// FullName:  CFPDReader::HashMapInsert
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: std::list<CKeyInfo * > * HashMap
	// Parameter: CKeyInfo * pKeyInfo
	// Parameter: const UINT32 & uiHashValue
	//************************************
	Status HashMapInsert(
		std::list<CKeyInfo*>									*HashMap,
		CKeyInfo												*pKeyInfo,
		const UINT32											&uiHashValue
		);
};


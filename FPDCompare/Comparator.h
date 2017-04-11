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
class CKeyInfo;
class COutputCollector;
class CMetaPropertySubValue;
class CMetaPropertSubValue_String;
class CMetaPropertSubValue_Integer;
class CMetaPropertSubValue_FileName;
class CMetaPropertSubValue_DateTime;
class CDataFileInfo;

class CComparator
{
public:
	CComparator(void);
	~CComparator(void);

	//************************************
	// Method:    PerformKeyComparision
	// FullName:  CComparator::PerformKeyComparision
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const std::list<CKeyInfo * > & KeyInfoBase
	// Parameter: const std::list<CKeyInfo * > & KeyInfoModified
	// Parameter: COutputCollector & OutputCollector
	// Parameter: std::list<CKeyInfo * > * HashMapBase
	// Parameter: std::list<CKeyInfo * > * HashMapModified
	//************************************
	Status PerformKeyComparision(
		const std::list<CKeyInfo*>									&KeyInfoBase,
		const std::list<CKeyInfo*>									&KeyInfoModified,
		COutputCollector											&OutputCollector,
		std::list<CKeyInfo*>										*HashMapBase,
		std::list<CKeyInfo*>										*HashMapModified
		);

private:

	//************************************
	// Method:    MatchMetaFile
	// FullName:  CComparator::MatchMetaFile
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szMetaFilePathBase
	// Parameter: const String & szMetaFilePathModified
	// Parameter: Wstring & szMismatchDetailsBase
	// Parameter: Wstring & szMismatchDetailsModified
	//************************************
	Status MatchMetaFile(	
		const String												&szMetaFilePathBase,
		const String												&szMetaFilePathModified, 
		Wstring														&szMismatchDetailsBase,
		Wstring														&szMismatchDetailsModified
		);

	//************************************
	// Method:    MatchDataProperty
	// FullName:  CComparator::MatchDataProperty
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const CDataFileInfo * pDataFileInfoBase
	// Parameter: const CDataFileInfo * pDataFileInfoModified
	//************************************
	Status MatchDataProperty(
		const CDataFileInfo											*pDataFileInfoBase, 
		const CDataFileInfo											*pDataFileInfoModified 
		);

	//************************************
	// Method:    ProcessMatchCondition
	// FullName:  CComparator::ProcessMatchCondition
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: CKeyInfo * pKeyInfoBase
	// Parameter: CKeyInfo * pKeyInfoModified
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status ProcessMatchCondition(
		CKeyInfo													*pKeyInfoBase, 
		CKeyInfo													*pKeyInfoModified, 
		COutputCollector											&OutputCollector
		);

	//************************************
	// Method:    ProcessMismatchCondition
	// FullName:  CComparator::ProcessMismatchCondition
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: CKeyInfo * pKeyInfoBase
	// Parameter: CKeyInfo * pKeyInfoModified
	// Parameter: Status IsDataMatchSuccessful
	// Parameter: Status IsMetaMatchSuccessful
	// Parameter: const Wstring & szDetailsBase
	// Parameter: const Wstring & szDetailsModified
	// Parameter: CDataFileInfo * pDataFileInfoBase
	// Parameter: CDataFileInfo * pDataFileInfoModified
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status ProcessMismatchCondition(
		CKeyInfo													*pKeyInfoBase, 
		CKeyInfo													*pKeyInfoModified,
		Status														IsDataMatchSuccessful,
		Status														IsMetaMatchSuccessful,
		const Wstring												&szDetailsBase, 
		const Wstring												&szDetailsModified,
		CDataFileInfo												*pDataFileInfoBase,
		CDataFileInfo												*pDataFileInfoModified,
		COutputCollector											&OutputCollector
		);

	//************************************
	// Method:    ProcessMissingCondition
	// FullName:  CComparator::ProcessMissingCondition
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const std::list<CKeyInfo * > & KeyInfoBase
	// Parameter: const std::list<CKeyInfo * > & KeyInfoModified
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status ProcessMissingCondition(
		const std::list<CKeyInfo*>									&KeyInfoBase,
		const std::list<CKeyInfo*>									&KeyInfoModified,
		COutputCollector											&OutputCollector
		);


	//************************************
	// Method:    CheckKeyReplication
	// FullName:  CComparator::CheckKeyReplication
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: const std::list<CKeyInfo * > & KeyInfoListBase
	// Parameter: const std::list<CKeyInfo * > & KeyInfoListModified
	// Parameter: std::list<CKeyInfo * > * HashMapBase
	// Parameter: std::list<CKeyInfo * > * HashMapModified
	//************************************
	Status CheckKeyReplication(
		const std::list<CKeyInfo*>									&KeyInfoListBase, 
		const std::list<CKeyInfo*>									&KeyInfoListModified,
		std::list<CKeyInfo*>										*HashMapBase,
		std::list<CKeyInfo*>										*HashMapModified
		);		
};

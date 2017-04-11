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
class CResourceCrawler
{
public:
	CResourceCrawler(void);
	~CResourceCrawler(void);
	
	//************************************
	// Method:    CrawlDirectory
	// FullName:  CResourceCrawler::CrawlDirectory
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szDirectoryPath
	// Parameter: List_Str & ValidPathList
	// Parameter: List_Str & InvalidPathList
	//************************************
	Status CrawlDirectory(
		const String				&szDirectoryPath,
		List_Str					&ValidPathList,
		List_Str					&InvalidPathList
		);

	//************************************
	// Method:    FindFile
	// FullName:  CResourceCrawler::FindFile
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szMetaDirectoryPath
	// Parameter: List_Str & MetaPathList
	//************************************
	Status FindFile(
		const String				&szMetaDirectoryPath, 
		List_Str					&MetaPathList
		);


	//************************************
	// Method:    FindMetaPath
	// FullName:  CResourceCrawler::FindMetaPath
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szDirectoryPath
	// Parameter: String & szMetaDirectoryPath
	//************************************
	Status FindMetaPath(
		const String				&szDirectoryPath, 
		String						&szMetaDirectoryPath
		);
};


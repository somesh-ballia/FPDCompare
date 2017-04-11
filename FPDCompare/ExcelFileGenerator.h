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

#include "libxl.h"
using namespace libxl;

class COutputCollector;
class CSummary;

class CExcelFileGenerator
{
public:
	CExcelFileGenerator(void);
	~CExcelFileGenerator(void);

	//************************************
	// Method:    GenerateFile
	// FullName:  CExcelFileGenerator::GenerateFile
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: COutputCollector & OutputCollector
	// Parameter: const List_Str & InvalidPathListBase
	// Parameter: const List_Str & InvalidPathListModified
	//************************************
	Status GenerateFile	(
		COutputCollector				&OutputCollector,		
		const List_Str					&InvalidPathListBase,
		const List_Str					&InvalidPathListModified
		);
private:

	//************************************
	// Method:    CreateSheatSummary
	// FullName:  CExcelFileGenerator::CreateSheatSummary
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: Book * & book
	//************************************
	Status CreateSheatSummary(
		Book							*&book
		);

	//************************************
	// Method:    CreateSheatMatchFile
	// FullName:  CExcelFileGenerator::CreateSheatMatchFile
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: Book * & book
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status CreateSheatMatchFile	(
		Book							*&book,
		COutputCollector				&OutputCollector
		);

	//************************************
	// Method:    CreateSheatMissingFile
	// FullName:  CExcelFileGenerator::CreateSheatMissingFile
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: Book * & book
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status CreateSheatMissingFile(
		Book							*&book,
		COutputCollector				&OutputCollector
		);

	//************************************
	// Method:    CreateSheatMismatchFile
	// FullName:  CExcelFileGenerator::CreateSheatMismatchFile
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: Book * & book
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status CreateSheatMismatchFile(
		Book							*&book,
		COutputCollector				&OutputCollector
		);	

	//************************************
	// Method:    CreateSheatInvalidFiles
	// FullName:  CExcelFileGenerator::CreateSheatInvalidFiles
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: Book * & book
	// Parameter: const List_Str & InvalidPathListBase
	// Parameter: const List_Str & InvalidPathListModified
	//************************************
	Status CreateSheatInvalidFiles(
		Book							*&book, 
		const List_Str					&InvalidPathListBase,
		const List_Str					&InvalidPathListModified
		);

	//************************************
	// Method:    CreateSheatKeyReplicationFile
	// FullName:  CExcelFileGenerator::CreateSheatKeyReplicationFile
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: Book * & book
	// Parameter: COutputCollector & OutputCollector
	//************************************
	Status CreateSheatKeyReplicationFile(
		Book							*&book,
		COutputCollector				&OutputCollector);

};


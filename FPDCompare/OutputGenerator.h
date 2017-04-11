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

class COutputCollector;
class COutputGenerator
{
public:
	COutputGenerator(void);
	~COutputGenerator(void);

	//************************************
	// Method:    GenerateOutput
	// FullName:  COutputGenerator::GenerateOutput
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: COutputCollector & OutputCollector
	// Parameter: const List_Str & InvalidPathListBase
	// Parameter: const List_Str & InvalidPathListModified
	//************************************
	Status GenerateOutput(
		COutputCollector			&OutputCollector,
		const List_Str				&InvalidPathListBase,
		const List_Str				&InvalidPathListModified
		);
};

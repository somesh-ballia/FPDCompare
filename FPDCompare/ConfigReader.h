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
class CConfigReader
{
public:
	CConfigReader(void);
	~CConfigReader(void);

	//************************************
	// Method:    ParseConfigFile
	// FullName:  CConfigReader::ParseConfigFile
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: const String & szConfigFilePath
	//************************************
	Status ParseConfigFile(
		const String							&szConfigFilePath
		);

private:

	//************************************
	// Method:    BufferParser
	// FullName:  CConfigReader::BufferParser
	// Access:    private 
	// Returns:   Status
	// Qualifier:
	// Parameter: char * pszBuffer
	// Parameter: List_Wstr & ItemList
	//************************************
	Status	BufferParser(
		char									*pszBuffer,
		List_Wstr								&ItemList
		);
};


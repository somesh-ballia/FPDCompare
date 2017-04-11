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

class CLogManager
{
public:
	CLogManager(void);
	~CLogManager(void);		

	//************************************
	// Method:    CreateLog
	// FullName:  CLogManager::CreateLog
	// Access:    public static 
	// Returns:   Status
	// Qualifier:
	// Parameter: LogType ltLogType
	// Parameter: int iMessage
	//************************************
	static	Status CreateLog(
		LogType					ltLogType,
		int						iMessage
		);

	//************************************
	// Method:    CreateLog
	// FullName:  CLogManager::CreateLog
	// Access:    public static 
	// Returns:   Status
	// Qualifier:
	// Parameter: LogType ltLogType
	// Parameter: String & szMessage
	//************************************
	static	Status CreateLog(
		LogType					ltLogType,
		String					&szMessage
		);

	//************************************
	// Method:    CreateLog
	// FullName:  CLogManager::CreateLog
	// Access:    public static 
	// Returns:   Status
	// Qualifier:
	// Parameter: LogType ltLogType
	// Parameter: String & szMessage
	// Parameter: int iMessage
	//************************************
	static	Status CreateLog(
		LogType					ltLogType,
		String					&szMessage,
		int						iMessage
		);

	//************************************
	// Method:    CreateLog
	// FullName:  CLogManager::CreateLog
	// Access:    public static 
	// Returns:   Status
	// Qualifier:
	// Parameter: LogType ltLogType
	// Parameter: char * pszMessage
	// Parameter: int iMessage
	//************************************
	static	Status CreateLog(
		LogType					ltLogType,
		char					*pszMessage,
		int						iMessage
		);

	//************************************
	// Method:    CreateLog
	// FullName:  CLogManager::CreateLog
	// Access:    public static 
	// Returns:   Status
	// Qualifier:
	// Parameter: LogType ltLogType
	// Parameter: char * pszMessage
	//************************************
	static  Status CreateLog(
		LogType					ltLogType,
		char					*pszMessage
		);
};


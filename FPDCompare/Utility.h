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

#include<stdio.h>
class CDataFileInfo;
typedef __int64 QWORD, *LPQWORD;

#define MAKEQWORD(a, b)	\
	((QWORD)( ((QWORD) ((DWORD) (a))) << 32 | ((DWORD) (b))))

#define LODWORD(l) \
	((DWORD)(l))
#define HIDWORD(l) \
	((DWORD)(((QWORD)(l) >> 32) & 0xFFFFFFFF))

// Read 4K of data at a time (used in the C++ streams, Win32 I/O, and assembly functions)
#define MAX_BUFFER_SIZE	4096

// Map a "view" size of 10MB (used in the filemap function)
#define MAX_VIEW_SIZE	10485760

extern bool g_bIsUnicodeEnabled;
extern bool g_bIsGenerateCheckOP;

static DWORD *m_pdwCrc32Table;

//************************************
// Method:    Init
// FullName:  Init
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void			Init();		

//************************************
// Method:    Free
// FullName:  Free
// Access:    public 
// Returns:   Status
// Qualifier:
//************************************
Status			Free();															

//************************************
// Method:    FileCrc32Filemap
// FullName:  FileCrc32Filemap
// Access:    public 
// Returns:   extern DWORD
// Qualifier:
// Parameter: const String & pszFilename
// Parameter: DWORD & dwCrc32
//************************************
extern DWORD FileCrc32Filemap(
	const String						&pszFilename, 
	DWORD								&dwCrc32
	);				


//************************************
// Method:    GetFileSizeQW
// FullName:  GetFileSizeQW
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const HANDLE hFile
// Parameter: QWORD & qwSize
//************************************
Status GetFileSizeQW(
	const HANDLE						hFile, 
	QWORD								&qwSize
	);					

//************************************
// Method:    CalcCrc32
// FullName:  CalcCrc32
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const BYTE byte
// Parameter: DWORD & dwCrc32
//************************************
void CalcCrc32(
	const BYTE							byte, 
	DWORD								&dwCrc32
	);						

//************************************
// Method:    GetCurrentTimeString
// FullName:  GetCurrentTimeString
// Access:    public 
// Returns:   std::string
// Qualifier:
//************************************
std::string GetCurrentTimeString();	

//************************************
// Method:    TrimDataFileName
// FullName:  TrimDataFileName
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szDataFileName
// Parameter: const String & szStringToFind
// Parameter: String & szShortDataFileName
//************************************
Status TrimDataFileName(
	const String						&szDataFileName,
	const String						&szStringToFind, 
	String								&szShortDataFileName
	);

//************************************
// Method:    LogError
// FullName:  LogError
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String szErrorMessage
//************************************
Status LogError(
	const String						szErrorMessage);

//************************************
// Method:    GetDataFileName
// FullName:  GetDataFileName
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaFilePath
// Parameter: std::string & szDataFilePath
//************************************
Status GetDataFileName(
	const String						&szMetaFilePath,
	std::string							&szDataFilePath
	);

//************************************
// Method:    IsFilePresent
// FullName:  IsFilePresent
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szFilePath
//************************************
Status IsFilePresent(
	const String						&szFilePath);

//************************************
// Method:    CalculateDataFileInfo
// FullName:  CalculateDataFileInfo
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaFilePath
// Parameter: CDataFileInfo * pDataFileInfo
//************************************
Status CalculateDataFileInfo(
	const String						&szMetaFilePath,
	CDataFileInfo						*pDataFileInfo											
	);

//************************************
// Method:    ConvertToWString
// FullName:  ConvertToWString
// Access:    public 
// Returns:   Wstring
// Qualifier:
// Parameter: const String & szInputString
//************************************
Wstring	ConvertToWString(
	const String						&szInputString
	);

//************************************
// Method:    ConvertToHyperlink
// FullName:  ConvertToHyperlink
// Access:    public 
// Returns:   Wstring
// Qualifier:
// Parameter: const String & szFilePath
//************************************
Wstring	ConvertToHyperlink(
	const String						&szFilePath
	);

//************************************
// Method:    GetNewPath
// FullName:  GetNewPath
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szOldPath
// Parameter: String & szNewPath
// Parameter: const ListType ltType
// Parameter: const DirectoryType dtType
//************************************
Status GetNewPath(
	const String						&szOldPath, 
	String								&szNewPath,
	const ListType						ltType , 
	const DirectoryType					dtType 
	);

//************************************
// Method:    CopyFile
// FullName:  CopyFile
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szOldPath
// Parameter: const String & szNewPath
//************************************
Status CopyFile(
	const String						&szOldPath,
	const String						&szNewPath
	);
//************************************
// Method:    CompareNocase
// FullName:  CompareNocase
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const Wstring & szFirst
// Parameter: const Wstring & szSecond
//************************************
bool CompareNocase(
	const Wstring						&szFirst,
	const Wstring						&szSecond
	);

//************************************
// Method:    CalculateHash
// FullName:  CalculateHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const Wstring & szData
//************************************
UINT32 CalculateHash(
	const Wstring						&szData);

//************************************
// Method:    CalculateHash
// FullName:  CalculateHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const unsigned int & uiData
//************************************
UINT32 CalculateHash(
	const unsigned int					&uiData);

//************************************
// Method:    CalculateHash
// FullName:  CalculateHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const int & uiData
//************************************
UINT32 CalculateHash(
	const int							&uiData);

//************************************
// Method:    CalculateCombinedHash
// FullName:  CalculateCombinedHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const std::list<UINT32> & ListHashValues
//************************************
UINT32 CalculateCombinedHash(
	const std::list<UINT32>				&ListHashValues);

//************************************
// Method:    GetSmallHashValue
// FullName:  GetSmallHashValue
// Access:    public 
// Returns:   UINT16
// Qualifier:
// Parameter: const UINT32 & uiHashValue
//************************************
UINT16 GetSmallHashValue(					
	const UINT32						&uiHashValue
	);

//************************************
// Method:    RemoveBrackets
// FullName:  RemoveBrackets
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Wstring & szData
//************************************
void RemoveBrackets(
	Wstring								&szData
	);
//************************************
// Method:    Tokenize
// FullName:  Tokenize
// Access:    public 
// Returns:   List_Wstr
// Qualifier:
// Parameter: const Wstring & szData
// Parameter: const Wstring & szDelimeters
//************************************
List_Wstr Tokenize(
	const Wstring						&szData,
	const Wstring						&szDelimeters
	);

//************************************
// Method:    CreateDirectoryStructure
// FullName:  CreateDirectoryStructure
// Access:    public 
// Returns:   Status
// Qualifier:
//************************************
Status CreateDirectoryStructure();
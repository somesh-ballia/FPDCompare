#include "StdAfx.h"
#include <Shlobj.h>
#include <algorithm>
#include "Utility.h"
#include "CommonAll.h"
#include "ConfigurationStorage.h"
#include "DataFileInfo.h"
#include "LogManager.h"


#define META "\\Meta\\"
#define DATA "\\Data\\"
#define MISMATCH "\\MISMATCH"
#define MISSING "\\MISSING"
#define MATCH "\\MATCH"
#define KEYREPLICATION "\\KEYREPLICATION"
#define HYPERLINK L"=HYPERLINK("

//************************************
// Method:    Init
// FullName:  Init
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Init()
{
	// This is the official polynomial used by CRC32 in PKZip.
	// Often times the polynomial shown reversed as 0x04C11DB7.
	DWORD dwPolynomial = 0xEDB88320;
	int i, j;
	
	Free();
	m_pdwCrc32Table = new DWORD[256];
	
	DWORD dwCrc;
	for(i = 0; i < 256; i++)
	{
		dwCrc = i;
		for(j = 8; j > 0; j--)
		{
			if(dwCrc & 1)
				dwCrc = (dwCrc >> 1) ^ dwPolynomial;
			else
				dwCrc >>= 1;
		}
		m_pdwCrc32Table[i] = dwCrc;
	}
}

//************************************
// Method:    Free
// FullName:  Free
// Access:    public 
// Returns:   Status
// Qualifier:
//************************************
Status Free()
{
	///*!
	//	Clears CRC table
	//*/
	delete m_pdwCrc32Table;
	m_pdwCrc32Table = NULL;
	return SUCCESS;
}

//************************************
// Method:    FileCrc32Filemap
// FullName:  FileCrc32Filemap
// Access:    public 
// Returns:   DWORD
// Qualifier:
// Parameter: const std::string & szDataFileName
// Parameter: DWORD & dwCrc32
//************************************
DWORD FileCrc32Filemap(const std::string &szDataFileName, DWORD &dwCrc32)
{
	/*!
		Performs CRC Check on the files
	*/
	DWORD dwErrorCode = NO_ERROR;
	HANDLE hFile = NULL, hFilemap = NULL;	
	
	dwCrc32 = 0xFFFFFFFF;	
	std::wstring szFileNameW;
	szFileNameW.assign(szDataFileName.begin(),szDataFileName.end());

	LPCWSTR lpFileName = const_cast<wchar_t *>(szFileNameW.c_str());
	try
	{
		// Is the table initialized?
		if(m_pdwCrc32Table == NULL)
			throw 0;
		
		// Open the file
			hFile = CreateFileW(lpFileName,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_SEQUENTIAL_SCAN,
			NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			dwErrorCode = GetLastError();
		else
		{
			QWORD qwFileSize = 0, qwFileOffset = 0;
			DWORD dwByteCount, dwViewSize;
			DWORD dwBaseAddress;
			
			// Get the file size
			if(GetFileSizeQW(hFile, qwFileSize))
				dwErrorCode = ERROR_BAD_LENGTH;
			else if(qwFileSize != 0)	// We cannot CRC zero byte files
			{
				// Create the file mapping
				hFilemap = CreateFileMapping(hFile,
					NULL,
					PAGE_READONLY,
					0,
					0,
					NULL);
				if(hFilemap == NULL)
					dwErrorCode = GetLastError();
				else
				{
					LPBYTE pByte;
					
					// Loop while we map a section of the file and CRC it
					while(qwFileSize > 0)
					{
						if(qwFileSize < MAX_VIEW_SIZE)
							dwViewSize = LODWORD(qwFileSize);
						else
							dwViewSize = MAX_VIEW_SIZE;
						
						dwBaseAddress = (DWORD)MapViewOfFile(hFilemap,
							FILE_MAP_READ,
							HIDWORD(qwFileOffset),
							LODWORD(qwFileOffset),
							dwViewSize);
						
						dwByteCount = dwViewSize;
						pByte = (LPBYTE)dwBaseAddress;
						while(dwByteCount-- > 0)
						{
							CalcCrc32(*pByte, dwCrc32);
							pByte++;
						}
						
						UnmapViewOfFile((LPVOID)dwBaseAddress);
						qwFileOffset += dwViewSize;
						qwFileSize -= dwViewSize;
					}
				}
			}
		}
	}
	catch(...)
	{
		// An unknown exception happened, or the table isn't initialized
		dwErrorCode = ERROR_CRC;
	}
	
	if(hFile != NULL) CloseHandle(hFile);
	if(hFilemap != NULL) CloseHandle(hFilemap);
	
	dwCrc32 = ~dwCrc32;
	
	return dwErrorCode;	
}

//************************************
// Method:    GetFileSizeQW
// FullName:  GetFileSizeQW
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const HANDLE hFile
// Parameter: QWORD & qwSize
//************************************
Status GetFileSizeQW(const HANDLE hFile, QWORD &qwSize)
{	
	//Get file size of data file		
		
	bool bSuccess = true;
	try
	{
		DWORD dwLo = 0, dwHi = 0;
		dwLo = GetFileSize(hFile, &dwHi);

		if(dwLo == INVALID_FILE_SIZE && GetLastError() != NO_ERROR)
		{
			bSuccess = false;
			qwSize = 0;
		}
		else
		{
			qwSize = MAKEQWORD(dwHi, dwLo);
		}
	}
	catch(...)
	{
		bSuccess = false;
	}

	if(bSuccess)	
		return SUCCESS;
	else
		return FAILURE;
}

//************************************
// Method:    CalcCrc32
// FullName:  CalcCrc32
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const BYTE byte
// Parameter: DWORD & dwCrc32
//************************************
void CalcCrc32(const BYTE byte, DWORD &dwCrc32)
{	
		dwCrc32 = ((dwCrc32) >> 8) ^ m_pdwCrc32Table[(byte) ^ ((dwCrc32) & 0x000000FF)];	
}

//************************************
// Method:    GetCurrentTimeString
// FullName:  GetCurrentTimeString
// Access:    public 
// Returns:   std::string
// Qualifier:
//************************************
std::string GetCurrentTimeString()
{
	static time_t tCurrentTime;
	static char	szTimeString[100];

	tCurrentTime = time(NULL);
	strftime(szTimeString, sizeof(szTimeString), "%d/%b/%Y %H:%M:%S ", localtime(&tCurrentTime));
	std::string szTime = szTimeString;
	return szTime;
}

//************************************
// Method:    GetDataFileName
// FullName:  GetDataFileName
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const std::string & szMetaFilePath
// Parameter: std::string & szDataFilePath
//************************************
Status GetDataFileName(const std::string &szMetaFilePath, std::string &szDataFilePath)
{
	const std::string szStringToFind = "\\Meta\\";
	const std::string szReplacement = "\\Da";	
	int iPosition = szMetaFilePath.find(szStringToFind);
	szDataFilePath = szMetaFilePath;
	szDataFilePath.replace(iPosition,3,szReplacement);
	int iLength = szDataFilePath.length();
	szDataFilePath.resize(iLength-8);
	return SUCCESS;
}

//************************************
// Method:    IsFilePresent
// FullName:  IsFilePresent
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const std::string & szFilePath
//************************************
Status IsFilePresent(const std::string &szFilePath)
{
	if (szFilePath.empty())
	{
		return FAILURE;
	}	

	struct stat stTempBuffer;
	if(stat(szFilePath.c_str(), &stTempBuffer))
	{
		return FAILURE;		
	}
	else
	{
		return SUCCESS;
	}	
}

//************************************
// Method:    CalculateDataFileInfo
// FullName:  CalculateDataFileInfo
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaFilePath
// Parameter: CDataFileInfo * pDataFileInfo
//************************************
Status CalculateDataFileInfo( const String &szMetaFilePath, CDataFileInfo *pDataFileInfo)
{	
	String szDataFilePath ;
	WIN32_FIND_DATAW stDataFileInfo;
	HANDLE hFindHandle = NULL;	
	std::wstring szDataFileNameW;
	DWORD dwCrc32 = 0, dwErrorCode = 0;

	if (0 == szMetaFilePath.length() || NULL == pDataFileInfo)
	{
		return FAILURE;
	}

	Status retGetDataFileName = GetDataFileName(szMetaFilePath,szDataFilePath);
	pDataFileInfo->m_szDataFilePath = szDataFilePath;

	if (FAILURE == retGetDataFileName)
	{
		return FAILURE;
	}

	if(0 == szDataFilePath.length())
	{
		return FAILURE;
	}

	pDataFileInfo->m_szDataFilePath = szDataFilePath;	
	dwErrorCode = FileCrc32Filemap(szDataFilePath, dwCrc32);
	pDataFileInfo->m_lCRCValue = dwCrc32;
	
	FILE *read_fp = NULL;
	read_fp = fopen(szDataFilePath.c_str(),"r");
	if (NULL != read_fp)
	{
		fseek(read_fp,0,SEEK_END);
		pDataFileInfo->m_lSize = ftell(read_fp);
		fclose(read_fp);
	}
	else
	{
		return FAILURE;
	}

	
	return SUCCESS;
}

//************************************
// Method:    ConvertToWString
// FullName:  ConvertToWString
// Access:    public 
// Returns:   Wstring
// Qualifier:
// Parameter: const String & szInputString
//************************************
Wstring ConvertToWString( const String &szInputString )
{
	std::wstring szOutputString;
	szOutputString.assign(szInputString.begin(),szInputString.end());
	return szOutputString;
}

//************************************
// Method:    ConvertToHyperlink
// FullName:  ConvertToHyperlink
// Access:    public 
// Returns:   Wstring
// Qualifier:
// Parameter: const String & szFilePath
//************************************
Wstring ConvertToHyperlink( const String &szFilePath )
{
	std::wstring szTemp;
	szTemp.assign(szFilePath.begin(),szFilePath.end());
	std::wstring szHyperlink;
	szHyperlink.append(L"=HYPERLINK(");
	szHyperlink.append(L"\"");
	szHyperlink.append(szTemp);
	szHyperlink.append(L"\",\"File\")");
	return szHyperlink;
}

//************************************
// Method:    GetNewPath
// FullName:  GetNewPath
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const std::string & szOldPath
// Parameter: std::string & szNewPath
// Parameter: const ListType ltType
// Parameter: const DirectoryType dtType
//************************************
Status GetNewPath( const std::string &szOldPath, std::string &szNewPath,const ListType ltType , const DirectoryType dtType )
{
	std::string szDumpPath;
	CConfigurationStorage::getInstance()->GetDumpFolderPath(szDumpPath);

	std::string szMeta = META;
	std::string szData = DATA;
	size_t sFound = szOldPath.find(szMeta);
	std::string szType;
	std::string szDirType;
	if (std::string::npos == sFound)
	{
		sFound = szOldPath.find(szData);
	}

	if(std::string::npos == sFound)
	{
		return FAILURE;
	}

	switch(ltType)
	{
	case LIST_MISMATCH:
		szType = "\\MISMATCH";
		break;
	case LIST_MISSING:
		szType = "\\MISSING";
		break;
	case LIST_KEY_REPLICATION:
		szType = "\\KEYREPLICATION";
		break;
	case LIST_MATCH :
		szType = "\\MATCH";
		break;
	}

	switch(dtType)
	{
	case BASE:
		szDirType = "\\Base";
		break;
	case MODIFIED:
		szDirType = "\\Modified";
		break;
	}

	szNewPath = szDumpPath;
	szNewPath.append(szType);
	szNewPath.append(szDirType);
	szNewPath.append(szOldPath.substr(sFound,szOldPath.length()));
	return SUCCESS;
}

//************************************
// Method:    CopyFile
// FullName:  CopyFile
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szOldPath
// Parameter: const String & szNewPath
//************************************
Status CopyFile(const String &szOldPath,const String &szNewPath)
{	
	String szDirPath;
	String szMessage;
	size_t sLocation = szNewPath.find_last_of('\\');
	szDirPath = szNewPath.substr(0,sLocation);

	SHCreateDirectoryExA(NULL,(LPCSTR)szDirPath.c_str(),NULL);
	DWORD errCreateDir  = GetLastError();
	BOOL retCopyStatus = CopyFile((LPCSTR)szOldPath.c_str(),(LPCSTR)szNewPath.c_str(),FALSE);	
	DWORD errCopyFile = GetLastError();
	if (TRUE == retCopyStatus)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

//************************************
// Method:    CompareNocase
// FullName:  CompareNocase
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const Wstring & szFirst
// Parameter: const Wstring & szSecond
//************************************
bool CompareNocase(const Wstring &szFirst,const Wstring &szSecond)
{
	unsigned int i=0;
	while ( (i<szFirst.length()) && (i<szSecond.length()) )
	{
		if (tolower(szFirst[i])<tolower(szSecond[i])) return true;
		else if (tolower(szFirst[i])>tolower(szSecond[i])) return false;
		++i;
	}
	if (szFirst.length()<szSecond.length()) return true;
	else return false;
}

//************************************
// Method:    CalculateHash
// FullName:  CalculateHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const Wstring & szData
//************************************
UINT32  CalculateHash(const Wstring &szData)
{
	UINT32 uiHashValue = 1;		
	const wchar_t *pszData = szData.c_str();
	while(*pszData)
	{
		uiHashValue = uiHashValue * 31 +*pszData++;		
	}
	return uiHashValue;
}

//************************************
// Method:    CalculateHash
// FullName:  CalculateHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const unsigned int & uiData
//************************************
UINT32	CalculateHash(const unsigned int &uiData)
{
	UINT32 uiHashValue = (UINT32)uiData;	
	return  uiHashValue;
}

//************************************
// Method:    CalculateHash
// FullName:  CalculateHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const int & uiData
//************************************
UINT32	CalculateHash(const int &uiData)
{
	UINT32 uiHashValue = (UINT32)uiData;
	return  uiHashValue;
}

//************************************
// Method:    CalculateCombinedHash
// FullName:  CalculateCombinedHash
// Access:    public 
// Returns:   UINT32
// Qualifier:
// Parameter: const std::list<UINT32> & ListHashValues
//************************************
UINT32 CalculateCombinedHash(const std::list<UINT32> &ListHashValues)
{
	std::list<UINT32>::const_iterator ListIterator;
	UINT32 uiHashValue = 0;
	for (ListIterator = ListHashValues.begin();ListIterator != ListHashValues.end();ListIterator++)
	{
		uiHashValue = uiHashValue ^ *ListIterator;		
	}	
	return uiHashValue;
}

//************************************
// Method:    GetSmallHashValue
// FullName:  GetSmallHashValue
// Access:    public 
// Returns:   UINT16
// Qualifier:
// Parameter: const UINT32 & uiHashValue
//************************************
UINT16 GetSmallHashValue( const UINT32 &uiHashValue )
{
	UINT32 check = 65535;
	UINT16 SmallHash = uiHashValue & check;	
	return SmallHash;
}

//************************************
// Method:    RemoveBrackets
// FullName:  RemoveBrackets
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Wstring & szData
//************************************
void RemoveBrackets( Wstring &szData )
{
	WCHAR chars[] = L"{},";
	for (unsigned int iCount = 0; iCount < wcslen(chars); ++iCount)
	{		
		szData.erase (std::remove(szData.begin(), szData.end(), chars[iCount]), szData.end());
	}
}

//************************************
// Method:    Tokenize
// FullName:  Tokenize
// Access:    public 
// Returns:   List_Wstr
// Qualifier:
// Parameter: const Wstring & szData
// Parameter: const Wstring & szDelimeters
//************************************
List_Wstr Tokenize(const Wstring &szData,const Wstring &szDelimeters)
{
	std::list<std::wstring> tokens;
	std::wstring::size_type delimPos = 0, tokenPos = 0, pos = 0;

	if(szData.length()<1)  return tokens;
	while(1){
		delimPos = szData.find_first_of(szDelimeters, pos);
		tokenPos = szData.find_first_not_of(szDelimeters, pos);

		if(std::wstring::npos != delimPos){
			if(std::wstring::npos != tokenPos){
				if(tokenPos<delimPos){
					tokens.push_back(szData.substr(pos,delimPos-pos));
				}
			}
			pos = delimPos+1;
		} else {
			if(std::wstring::npos != tokenPos){
				tokens.push_back(szData.substr(pos));
			}
			break;
		}
	}
	tokens.sort(CompareNocase);
	return tokens;
}

#include "StdAfx.h"
#include "ConfigReader.h"
#include "ConfigurationStorage.h"
#include "Summary.h"

#define BUFFER_SIZE 32768
#define  COMA L','

CConfigReader::CConfigReader(void)
{
}


CConfigReader::~CConfigReader(void)
{
}

//************************************
// Method:    BufferParser
// FullName:  CConfigReader::BufferParser
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: char * pszBuffer
// Parameter: List_Wstr & ItemList
//************************************
Status CConfigReader::BufferParser( char *pszBuffer,List_Wstr &ItemList )
{	
	std::string szBuffer;
	std::wstring szBufferW;
	int iCounter = 0;
	int usStart = 0;
	int usEnd = 0;
	int usLength = 0;

	if(NULL == pszBuffer)
	{
		return FAILURE;
	}

	// convert to std::wstring
	szBuffer = pszBuffer;
	szBufferW.assign(szBuffer.begin(),szBuffer.end());

	if(0 == szBufferW.length())
	{
		return FAILURE;
	}

	usLength = szBufferW.length();

	// extract words separated by coma and insert it into the list

	for(iCounter = usStart; iCounter < usLength; iCounter++)
	{
		usEnd = szBufferW.find(COMA,iCounter);
		if(std::wstring::npos == usEnd)
		{
			std::wstring szTempW = szBufferW.substr(iCounter,(usLength-iCounter));
			ItemList.push_back(szTempW);
			break;
		}
		std::wstring szTempW = szBufferW.substr(iCounter,(usEnd-iCounter));
		ItemList.push_back(szTempW);
		iCounter = usEnd;
	}

	return SUCCESS;
}

//************************************
// Method:    ParseConfigFile
// FullName:  CConfigReader::ParseConfigFile
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szConfigFilePath
//************************************
Status CConfigReader::ParseConfigFile(const String &szConfigFilePath)
{
	char pszBuffer[BUFFER_SIZE] = {0};
	memset(pszBuffer,0,BUFFER_SIZE);

	// Base path
	GetPrivateProfileStringA((LPSTR)"Settings",
							(LPSTR)"Base_Path",
							(LPSTR)"",
							(LPSTR)pszBuffer,
							BUFFER_SIZE,
							(LPSTR)szConfigFilePath.c_str()
							);

	String szBuffer = pszBuffer;
	CConfigurationStorage::getInstance()->SetBasePath(szBuffer);
	if (0 == strlen(pszBuffer))
	{
		return FAILURE;
	}
	memset(pszBuffer,0,BUFFER_SIZE);

	// modified path
	GetPrivateProfileStringA((LPSTR)"Settings",
							(LPSTR)"Modified_Path",
							(LPSTR)"",
							(LPSTR)pszBuffer,
							BUFFER_SIZE,
							(LPSTR)szConfigFilePath.c_str()
							);

	szBuffer = pszBuffer;
	CConfigurationStorage::getInstance()->SetModifiedPath(szBuffer);
	if (0 == strlen(pszBuffer))
	{
		return FAILURE;
	}
	memset(pszBuffer,0,BUFFER_SIZE);

	// output path
	GetPrivateProfileStringA((LPSTR)"Settings",
							 (LPSTR)"Output_Path",
							 (LPSTR)"",
							 (LPSTR)pszBuffer,
							 BUFFER_SIZE,
							 (LPSTR)szConfigFilePath.c_str()
							 );
	szBuffer = pszBuffer;
	CConfigurationStorage::getInstance()->SetOutputPath(szBuffer);
	if (0 == strlen(pszBuffer))
	{
		return FAILURE;
	}
	memset(pszBuffer,0,BUFFER_SIZE);

	// Log path
	GetPrivateProfileStringA((LPSTR)"Settings",
							 (LPSTR)"Log_Path",
							 (LPSTR)"",
							 (LPSTR)pszBuffer,
							 BUFFER_SIZE,
							 (LPSTR)szConfigFilePath.c_str()
							 );

	szBuffer = pszBuffer;
	CConfigurationStorage::getInstance()->SetLogFilePath(szBuffer);
	if(0 == strlen(pszBuffer))
	{
		return FAILURE;
	}
	memset(pszBuffer,0,BUFFER_SIZE);

	// key attributes
	GetPrivateProfileStringA((LPSTR)"Settings",
							 (LPSTR)"Key_Attributes",
							 (LPSTR)"",
							 (LPSTR)pszBuffer,
							 BUFFER_SIZE,
							 (LPSTR)szConfigFilePath.c_str()
							 );

	List_Wstr TempListKeyAttrib;
	Status retParseKeyAttrib = BufferParser(pszBuffer,TempListKeyAttrib);
	CSummary::getInstance()->m_szKeyList = pszBuffer;
	if ((SUCCESS == retParseKeyAttrib) && (0 != strlen(pszBuffer)))
	{
		CConfigurationStorage::getInstance()->SetKeyAttributeList(TempListKeyAttrib);
	}
	else
	{
		return FAILURE;
	}	
	memset(pszBuffer,0,BUFFER_SIZE);


	GetPrivateProfileStringA((LPSTR)"Settings",
							(LPSTR)"Ignore_List",
							(LPSTR)"",
							(LPSTR)pszBuffer,
							BUFFER_SIZE,
							(LPSTR)szConfigFilePath.c_str()
							);	

	List_Wstr TempListIgnore;
	Status retParseIgnore = BufferParser(pszBuffer,TempListIgnore);
	CSummary::getInstance()->m_szIgnoreList = pszBuffer;
	if ((SUCCESS == retParseIgnore) && (0 != strlen(pszBuffer)))
	{
		CConfigurationStorage::getInstance()->SetIgnoreList(TempListIgnore);
	}
	else
	{
		return FAILURE;
	}	
	memset(pszBuffer,0,BUFFER_SIZE);


	GetPrivateProfileStringA((LPSTR)"Settings",
							 (LPSTR)"Dump_Folder_Path",
							 (LPSTR)"",
							 (LPSTR)pszBuffer,
							 BUFFER_SIZE,
							 (LPSTR)szConfigFilePath.c_str()
							 );

	szBuffer = pszBuffer;
	CConfigurationStorage::getInstance()->SetDumpFolderPath(szBuffer);
	if (0 == strlen(pszBuffer))
	{
		return FAILURE;
	}
	memset(pszBuffer,0,BUFFER_SIZE);

	
	int iIsUnicode = GetPrivateProfileIntA((LPSTR)"Settings",
											(LPSTR)"IS_Unicode",
											1,
											(LPSTR)szConfigFilePath.c_str()
											);
	if (1 == iIsUnicode)
	{
		CConfigurationStorage::getInstance()->SetUnicodeEnableStatus(true);
		CSummary::getInstance()->m_uiIsUnicode = 1;
	}
	else
	{
		CConfigurationStorage::getInstance()->SetUnicodeEnableStatus(false);
		CSummary::getInstance()->m_uiIsUnicode = 0;
	}

	int iEnableMetaMatch = GetPrivateProfileIntA((LPSTR)"Settings",
												(LPSTR)"Enable_Meta_Comparision",
												0,
												(LPSTR)szConfigFilePath.c_str()
												);
	if (1 == iEnableMetaMatch)
	{
		CConfigurationStorage::getInstance()->SetEnableMatchMeta(true);
		CSummary::getInstance()->m_uiIsMetaComparisionEnabled = 1;
	}
	else
	{
		CConfigurationStorage::getInstance()->SetEnableMatchMeta(false);
		CSummary::getInstance()->m_uiIsMetaComparisionEnabled = 0;
	}

	int iDumpFolderHierarchy = GetPrivateProfileIntA((LPSTR)"Settings",
													(LPSTR)"Dump_Folder_Hierarchy",
													0,
													(LPSTR)szConfigFilePath.c_str()
													);
	if (1 == iDumpFolderHierarchy)
	{
		CConfigurationStorage::getInstance()->SetEnableDumpFolderHierarchy(true);
	}
	else
	{
		CConfigurationStorage::getInstance()->SetEnableDumpFolderHierarchy(false);
	}

	int iEnableLogging = GetPrivateProfileIntA((LPSTR)"Settings",
											   (LPSTR)"Enable_Logging",
											   0,
											   (LPSTR)szConfigFilePath.c_str()
											   );
	if (1 == iEnableLogging)
	{
		CConfigurationStorage::getInstance()->SetLoggingStatus(true);
	}
	else
	{
		CConfigurationStorage::getInstance()->SetLoggingStatus(false);
	}

	return SUCCESS;
}
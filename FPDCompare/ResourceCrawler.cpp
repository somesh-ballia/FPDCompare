#include "StdAfx.h"
#include "ResourceCrawler.h"
#include "CommonAll.h"
#include "Utility.h"
#include "LogManager.h"

#define DATA "Data"
#define META "Meta"

CResourceCrawler::CResourceCrawler(void)
{
}


CResourceCrawler::~CResourceCrawler(void)
{
}

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
Status CResourceCrawler::CrawlDirectory(const String &szDirectoryPath,
											  List_Str &ValidPathList,
											  List_Str &InvalidPathList
											  )
{
	std::string szMetaFilePath;

	Status retFindMetaPath = FindMetaPath(szDirectoryPath, szMetaFilePath);
	if (SUCCESS == retFindMetaPath)
	{
		List_Str MetaPathList;
		Status retFindFile = FindFile(szMetaFilePath,MetaPathList);
		if (SUCCESS == retFindFile)
		{
			List_Str::iterator listIterator;
			for(listIterator = MetaPathList.begin(); listIterator != MetaPathList.end(); listIterator++)
			{
				std::string szDataFilePath;
				const std::string &szItem = (std::string) *listIterator;
				Status retGetDataFileName = GetDataFileName(szItem,szDataFilePath);
				if(SUCCESS == retGetDataFileName)
				{
					Status retIsFilePresent = IsFilePresent(szDataFilePath);
					if(SUCCESS == retIsFilePresent)
					{					
						ValidPathList.push_back(szItem);
					}
					else
					{					
						InvalidPathList.push_back(szItem);
						String szMessage = "Data File Not Found : "; 
						szMessage.append(szItem);
						CLogManager::CreateLog(LOG_ERROR,szMessage);
					}
				}
				else
				{
					String szMessage = "Error Computing data file name : "; 
					szMessage.append(szItem);
					CLogManager::CreateLog(LOG_ERROR,szMessage);
					return FAILURE;
				}
			}
		}
		else
		{
			String szMessage = "Error Populating meta file list : "; 
			szMessage.append(szMetaFilePath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;			
		}
	}
	else
	{
		String szMessage = "Error Computing meta file path : "; 
		szMessage.append(szDirectoryPath);
		CLogManager::CreateLog(LOG_ERROR,szMessage);
		return FAILURE;
	} 

	return SUCCESS;
}

//************************************
// Method:    FindMetaPath
// FullName:  CResourceCrawler::FindMetaPath
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szDirectoryPath
// Parameter: String & szMetaDirectoryPath
//************************************
Status CResourceCrawler::FindMetaPath( const String &szDirectoryPath, String &szMetaDirectoryPath )
{
	const char* filePath = szDirectoryPath.c_str();	

	char fileName[MAX_PATH] = {NULL};
	const char *temp = NULL;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	temp = strrchr(filePath, '\\');
	strcat_s(fileName, temp+1);

	if(strcmp(fileName, 	("*.*")) == 0)
	{
		char path[MAX_PATH] = {NULL};
		size_t len = 0;
		strcat_s/*_tcscpy*/(path, filePath);
		len = strlen/*_tcslen*/(path);
		path[len - strlen/*_tcslen*/("*.*")] = '\0';

		HRESULT hr = S_OK;

		hFind = FindFirstFileA(filePath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{	
			String szMessage = "Error Opening file : "; 
			szMessage.append(filePath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;
		}
		else 
		{
			if((strcmp(FindFileData.cFileName, (".")) != 0) && (strcmp(FindFileData.cFileName, ("..")) != 0))
			{
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if(0 == strcmp(FindFileData.cFileName, "Meta") )
					{
						char path[MAX_PATH] = {NULL};
						size_t len = 0;  
						strcat_s(path, filePath);
						len = strlen(path);
						path[len - strlen("*.*")] = '\0';
						strcat_s(path, FindFileData.cFileName);
						strcat_s(path, "\\");
						strcat_s(path, 	"*.*");
						szMetaDirectoryPath = path;
						return SUCCESS;						
					}
					else if(0 == strcmp(FindFileData.cFileName, DATA) )
					{
						//Do Nothing
					}
					else
					{
						char path[MAX_PATH] = {NULL};
						size_t len = 0;  
						strcat_s(path, filePath);
						len = strlen(path);
						path[len - strlen("*.*")] = '\0';
						strcat_s(path, FindFileData.cFileName);
						strcat_s(path, "\\");
						strcat_s(path, 	"*.*");
						Status retFindMetaPath = FindMetaPath(path,szMetaDirectoryPath);
						if (SUCCESS == retFindMetaPath)
						{
							return SUCCESS;
						}
					}
				}				
			}
			while (FindNextFileA(hFind, &FindFileData) != 0) 
			{
				if((strcmp(FindFileData.cFileName, (".")) != 0) && (strcmp(FindFileData.cFileName,("..")) != 0))
				{
					if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if(0 == strcmp(FindFileData.cFileName, META) )
						{
							char path[MAX_PATH] = {NULL};
							size_t len = 0;  
							strcat_s(path, filePath);
							len = strlen(path);
							path[len - strlen("*.*")] = '\0';
							strcat_s(path, FindFileData.cFileName);
							strcat_s(path, "\\");
							strcat_s(path, 	"*.*");
							szMetaDirectoryPath = path;
							return SUCCESS;							
						}
						else if(0 == strcmp(FindFileData.cFileName, DATA) )
						{
							//Do Nothing
						}
						else
						{
							char path[MAX_PATH] = {NULL};
							size_t len = 0;  
							strcat_s(path, filePath);
							len = strlen(path);
							path[len - strlen("*.*")] = '\0';
							strcat_s(path, FindFileData.cFileName);
							strcat_s(path, "\\");
							strcat_s(path, 	"*.*");
							Status retFindMetaPath = FindMetaPath(path,szMetaDirectoryPath);
							if (SUCCESS == retFindMetaPath)
							{
								return SUCCESS;
							}
						}
					}
				}				
			}
		}

		if(hFind)
		{
			FindClose(hFind);
		}
		else
		{
			String szMessage = "Error closing handle of  : "; 
			szMessage.append(szDirectoryPath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);			
		}		
	}

	CLogManager::CreateLog(LOG_ERROR,"Error in Finding meta file path");
	return FAILURE;

}

//************************************
// Method:    FindFile
// FullName:  CResourceCrawler::FindFile
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaDirectoryPath
// Parameter: List_Str & MetaPathList
//************************************
Status CResourceCrawler::FindFile( const String &szMetaDirectoryPath, List_Str &MetaPathList )
{
	const char* szFilePath = szMetaDirectoryPath.c_str();
	char szFileName[MAX_PATH] = {NULL};
	const char *szTemp = NULL;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	szTemp = strrchr(szFilePath, '\\');
	strcat_s(szFileName, szTemp+1);

	if(strcmp(szFileName,("*.*")) == 0)
	{
		char szPath[MAX_PATH] = {NULL};
		size_t iLength = 0;
		strcat_s(szPath, szFilePath);
		iLength = strlen(szPath);
		szPath[iLength - strlen("*.*")] = '\0';

		HRESULT hr = S_OK;

		hFind = FindFirstFileA(szFilePath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			String szMessage = "Error Opening file : "; 
			szMessage.append(szFilePath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;
		}
		else 
		{
			if((0 != strcmp(FindFileData.cFileName,("."))) && (0 != strcmp(FindFileData.cFileName,(".."))))
			{
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					char szPath[MAX_PATH] = {NULL};
					size_t iLength = 0;  
					strcat_s(szPath, szFilePath);
					iLength = strlen(szPath);
					szPath[iLength - strlen("*.*")] = '\0';
					strcat_s(szPath, FindFileData.cFileName);
					strcat_s(szPath, "\\");
					strcat_s(szPath, 	"*.*");
					FindFile(szPath,MetaPathList);
				}
				else
				{
					char szPath[MAX_PATH] = {NULL};
					size_t iLength = 0;
					strcat_s(szPath, szFilePath);
					iLength = strlen(szPath);
					szPath[iLength - strlen(("*.*"))] = '\0';
					strcat_s(szPath, FindFileData.cFileName);

					char *pszTempString = NULL;					
					pszTempString = strrchr(szPath, '.');

					if(NULL != pszTempString)
					{
						// Process the File that has been found, if it is a Meta File
						if( 0 == strcmp(pszTempString, IMPMETA))
						{					
							MetaPathList.push_back(szPath);							
						}
					}
				}
			}
			while (FindNextFileA(hFind, &FindFileData) != 0) 
			{
				if((0 != strcmp(FindFileData.cFileName, ".")) && (0 != strcmp(FindFileData.cFileName, "..")))
				{
					if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						char szPath[MAX_PATH] = {NULL};
						size_t iLength = 0;
						strcat_s(szPath, szFilePath);
						iLength = strlen(szPath);
						szPath[iLength - strlen("*.*")] = '\0';
						strcat_s(szPath, FindFileData.cFileName);
						strcat_s(szPath, "\\");
						strcat_s(szPath, 	"*.*");
						FindFile(szPath,MetaPathList);
					}
					else
					{
						char szPath[MAX_PATH] = {NULL};
						size_t iLength = 0;
						strcat_s(szPath, szFilePath);
						iLength = strlen(szPath);
						szPath[iLength - strlen("*.*")] = '\0';
						strcat_s(szPath, FindFileData.cFileName);

						char *pszTempString = NULL;
						pszTempString = strrchr(szPath, '.');

						if(NULL != pszTempString)
						{
							// Process the File that has been found, if it is a Meta File
							if( 0 == strcmp(pszTempString,IMPMETA) )
							{
								MetaPathList.push_back(szPath);	
							}
						}
					}
				}
			}
		}

		if(hFind)
		{
			FindClose(hFind);
		}
		else
		{

			String szMessage = "Error closing handle of  : "; 			
			CLogManager::CreateLog(LOG_ERROR,szMessage);
		}
	}

	int iListSize = MetaPathList.size();

	if (0 == iListSize)
	{
		return FAILURE;
	}
	return SUCCESS;
}
#include "StdAfx.h"
#include "FPDReader.h"
#include "KeyInfo.h"
#include "KeyExtractor.h"
#include "ResourceCrawler.h"
#include "MetaProperty.h"
#include "ConfigurationStorage.h"
#include "LogManager.h"
#include "Utility.h"

CFPDReader::CFPDReader(void)
{
}


CFPDReader::~CFPDReader(void)
{
}

//************************************
// Method:    ProcessDirectory
// FullName:  CFPDReader::ProcessDirectory
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szDirectoryPath
// Parameter: List_Str & InvalidPathList
// Parameter: list<CKeyInfo * > & KeyInfoList
// Parameter: std::list<CKeyInfo * > * HashMap
//************************************
Status CFPDReader::ProcessDirectory( const String &szDirectoryPath,
											List_Str &InvalidPathList,
											list<CKeyInfo*> &KeyInfoList,
											std::list<CKeyInfo*> *HashMap
											)
{
	CLogManager LogManager;
	List_Str ValidPathList;
	List_Str::iterator ListIterator;
	CResourceCrawler ResourceCrawler;
	CKeyExtractor KeyExtractor;
	
	if(0 == szDirectoryPath.length())
	{
		return FAILURE;
	}
	
	Status retCrawlDirectory = ResourceCrawler.CrawlDirectory(szDirectoryPath,ValidPathList,InvalidPathList);
	if (SUCCESS == retCrawlDirectory)
	{
		int iDisplayCount = 0;
		for(ListIterator = ValidPathList.begin(); ListIterator != ValidPathList.end();ListIterator++)
		{
			CKey *pKeyValue = new CKey();
			UINT32 uiHashValue = 0;
			Status retKeyExtractor = KeyExtractor.ExtractKey(*ListIterator,pKeyValue,uiHashValue);
			if (SUCCESS == retKeyExtractor)
			{
				CKeyInfo *pKeyInfo = new CKeyInfo();
				pKeyInfo->m_MetaFilePath = *ListIterator;
				pKeyInfo->m_KeyValue = pKeyValue;			
				pKeyInfo->m_HashValue = uiHashValue;
				Status retHashMapInsert = HashMapInsert(HashMap,pKeyInfo,uiHashValue);
				std::list<CKeyInfo*> &tees = HashMap[GetSmallHashValue(uiHashValue)];
				if (SUCCESS == retHashMapInsert)
				{
					KeyInfoList.push_back(pKeyInfo);
					iDisplayCount++;				
					String szDisplay = "";
					LogManager.CreateLog(LOG_UI,"Parsing",iDisplayCount);
				}
				else
				{
					String szMessage = "Error Inserting in Hash Map :";
					szMessage.append(*ListIterator);
					CLogManager::CreateLog(LOG_ERROR,szMessage);
					return FAILURE;
				}
			}
			else
			{
				String szMessage = "Error Extracting Key :";
				szMessage.append(*ListIterator);
				CLogManager::CreateLog(LOG_ERROR,szMessage);
			}
		}
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	ValidPathList.clear();
}

//************************************
// Method:    HashMapInsert
// FullName:  CFPDReader::HashMapInsert
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: std::list<CKeyInfo * > * HashMap
// Parameter: CKeyInfo * pKeyInfo
// Parameter: const UINT32 & uiHashValue
//************************************
Status CFPDReader::HashMapInsert(std::list<CKeyInfo*> *HashMap,CKeyInfo *pKeyInfo,const UINT32 &uiHashValue)
{
	if (NULL == pKeyInfo)
	{
		return FAILURE;
	}	
	std::list<CKeyInfo*> &ListKey = HashMap[GetSmallHashValue(uiHashValue)];	
	ListKey.push_back(pKeyInfo);	
	return SUCCESS;
}



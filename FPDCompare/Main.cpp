#include "stdafx.h"
#include "ConfigurationStorage.h"
#include "ConfigReader.h"
#include "FPDReader.h"
#include "Comparator.h"
#include "Utility.h"
#include "Summary.h"
#include "OutputCollector.h"
#include "OutputGenerator.h"
#include "LogManager.h"
#include "FileDumpCreator.h"
#include "MatchResource.h"
#include "MismatchResource.h"
#include "CopyFileStorage.h"
#include "MetaPropertyValue.h"
#include "MetaProperty.h"
#include "KeyInfo.h"

#define CONFIG_PATH "..\\Configuration\\FPDCompare.ini"

// cleaning up memory
//************************************
// Method:    CleanMemory
// FullName:  CleanMemory
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: COutputCollector & OutputCollector
// Parameter: list<CKeyInfo * > & KeyInfoListBase
// Parameter: list<CKeyInfo * > & KeyInfoListModified
//************************************
void CleanMemory(COutputCollector &OutputCollector,list<CKeyInfo*> &KeyInfoListBase,list<CKeyInfo*> &KeyInfoListModified)
{
	// for match list
	std::list<CMatchResource*>::iterator MatchListIterator;
	for (MatchListIterator = OutputCollector.m_MatchList.begin();MatchListIterator != OutputCollector.m_MatchList.end();)
	{
		CMatchResource *pMatchResource = *MatchListIterator;
		MatchListIterator++;
		delete pMatchResource;
	}
	OutputCollector.m_MatchList.clear();

	// for mismatch list
	std::list<CMismatchResource*>::iterator	MismatchListIterator;
	for(MismatchListIterator = OutputCollector.m_MismatchList.begin();MismatchListIterator != OutputCollector.m_MismatchList.end();)
	{
		CMismatchResource *pMismatchResource = *MismatchListIterator;
		MismatchListIterator++;
		delete pMismatchResource;
	}
	OutputCollector.m_MismatchList.clear();

	// for missing list base
	std::list<CMetaFileInfo*>::iterator MissingListBaseIterator;
	for(MissingListBaseIterator = OutputCollector.m_MissingListBase.begin();MissingListBaseIterator != OutputCollector.m_MissingListBase.end();)
	{
		CMetaFileInfo *pMetaFileInfo = *MissingListBaseIterator;
		MissingListBaseIterator++;
		delete pMetaFileInfo;
	}
	OutputCollector.m_MissingListBase.clear();

	// for missing list modified
	std::list<CMetaFileInfo*>::iterator MissingListModifiedIterator;
	for(MissingListModifiedIterator = OutputCollector.m_MissingListModified.begin();MissingListModifiedIterator != OutputCollector.m_MissingListModified.end();)
	{
		CMetaFileInfo *pMetaFileInfo = *MissingListModifiedIterator;
		MissingListModifiedIterator++;
		delete pMetaFileInfo;
	}
	OutputCollector.m_MissingListModified.clear();

	// for key replication base 
	std::list<CMetaFileInfo*>::iterator KeyReplicationListBaseIterator;
	for(KeyReplicationListBaseIterator = OutputCollector.m_KeyReplicationListBase.begin();KeyReplicationListBaseIterator != OutputCollector.m_KeyReplicationListBase.end();)
	{
		CMetaFileInfo *pMetaFileInfo = *KeyReplicationListBaseIterator;
		KeyReplicationListBaseIterator++;
		delete pMetaFileInfo;
	}
	OutputCollector.m_KeyReplicationListBase.clear();

	// for key replication modified
	std::list<CMetaFileInfo*>::iterator		KeyReplicationListModifiedIterator;
	for(KeyReplicationListModifiedIterator = OutputCollector.m_KeyReplicationListModified.begin();KeyReplicationListModifiedIterator != OutputCollector.m_KeyReplicationListModified.end();)
	{
		CMetaFileInfo *pMetaFileInfo = *KeyReplicationListModifiedIterator;
		KeyReplicationListModifiedIterator++;
		delete pMetaFileInfo;
	}
	OutputCollector.m_KeyReplicationListModified.clear();

	// for file copy list
	std::list<CCopyFileStorage*>::iterator	FileCopyListIterator;
	for(FileCopyListIterator = OutputCollector.m_FileCopyList.begin();FileCopyListIterator != OutputCollector.m_FileCopyList.end();)
	{
		CCopyFileStorage *pCopyFileStorage = *FileCopyListIterator;
		FileCopyListIterator++;
		delete pCopyFileStorage;
	}
	OutputCollector.m_FileCopyList.clear();

	// for cleaning meta key list base
	list<CKeyInfo*>::iterator KeyInfoListBaseIterator;
	for(KeyInfoListBaseIterator = KeyInfoListBase.begin();KeyInfoListBaseIterator != KeyInfoListBase.end();)
	{
		CKeyInfo *pKeyInfo = *KeyInfoListBaseIterator;
		KeyInfoListBaseIterator++;
		delete pKeyInfo;
	}
	KeyInfoListBase.clear();

	// for cleaning meta key list modified
	list<CKeyInfo*>::iterator KeyInfoListModifiedIterator;
	for(KeyInfoListModifiedIterator = KeyInfoListModified.begin();KeyInfoListModifiedIterator != KeyInfoListModified.end();)
	{
		CKeyInfo *pKeyInfo = *KeyInfoListModifiedIterator;
		KeyInfoListModifiedIterator++;
		delete pKeyInfo;
	}
	KeyInfoListModified.clear();
}

//************************************
// Method:    main
// FullName:  main
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int main()
{
	std::list<CKeyInfo*> *HashMapBase = new std::list<CKeyInfo*>[65536];
	std::list<CKeyInfo*> *HashMapModified = new std::list<CKeyInfo*>[65536];

	list<CKeyInfo*> KeyInfoListBase;
	list<CKeyInfo*> KeyInfoListModified;  	
	
	String szDirectoryPathBase;
	String szDirectoryPathModified;
	List_Str InvalidPathListBase;
	List_Str InvalidPathListModified;

	COutputGenerator OutputGenerator;
	COutputCollector OutputCollector;
	CComparator Comparator;
	CConfigReader ConfigReader;
	CFPDReader FPDReader;	

	String szMessage = "Start Processing";						
	CLogManager::CreateLog(LOG_UI,szMessage);
	CLogManager::CreateLog(LOG_ERROR,szMessage);

	CSummary::getInstance()->m_szStartTime = GetCurrentTimeString();
	Init();	

	if(SUCCESS == ConfigReader.ParseConfigFile(CONFIG_PATH))
	{
		CConfigurationStorage::getInstance()->GetBasePath(szDirectoryPathBase);
		CConfigurationStorage::getInstance()->GetModifiedPath(szDirectoryPathModified);	

		String szMessage = "Start Processing Base Directory ";		
		szMessage.append(szDirectoryPathBase);
		CLogManager::CreateLog(LOG_UI,szMessage);
		CLogManager::CreateLog(LOG_ERROR,szMessage);
		Status retDirectoryPathBase = FPDReader.ProcessDirectory(szDirectoryPathBase,
																InvalidPathListBase,
																KeyInfoListBase,
																HashMapBase
																);
		if (SUCCESS == retDirectoryPathBase)
		{
			CSummary::getInstance()->m_uiValidFilesBase = KeyInfoListBase.size();
			CSummary::getInstance()->m_uiInvalidFilesBase = InvalidPathListBase.size();
			CSummary::getInstance()->m_uiTotalFilesBase = CSummary::getInstance()->m_uiValidFilesBase + 
														  CSummary::getInstance()->m_uiInvalidFilesBase;

			String szMessage = "Start Processing Modified Directory ";		
			szMessage.append(szDirectoryPathModified);
			CLogManager::CreateLog(LOG_UI,szMessage);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			Status retDirectoryPathModified = FPDReader.ProcessDirectory(szDirectoryPathModified,
																		 InvalidPathListModified,
																		 KeyInfoListModified,
																		 HashMapModified
																		);
			if(SUCCESS == retDirectoryPathModified)
			{
				CSummary::getInstance()->m_uiValidFilesModified = KeyInfoListModified.size();
				CSummary::getInstance()->m_uiInvalidFilesModified = InvalidPathListModified.size();
				CSummary::getInstance()->m_uiTotalFilesModified = CSummary::getInstance()->m_uiInvalidFilesModified + 
																  CSummary::getInstance()->m_uiValidFilesModified;
				CSummary::getInstance()->m_uiTotalFiles = 	CSummary::getInstance()->m_uiTotalFilesModified + 
														    CSummary::getInstance()->m_uiTotalFilesBase;

				CSummary::getInstance()->m_uiInvalidFilesBase = InvalidPathListBase.size();
				CSummary::getInstance()->m_uiInvalidFilesModified = InvalidPathListModified.size();

				String szMessage = "Start Key Comparisons ";				
				CLogManager::CreateLog(LOG_UI,szMessage);
				CLogManager::CreateLog(LOG_ERROR,szMessage);
				
				// to enable hash map preview
#pragma region HashMapPreview
				if (false)
				{
					for (UINT16 i = 0;i<65535;i++)
					{
						std::list<CKeyInfo*> baseL = HashMapBase[i];
						std::list<CKeyInfo*> ModiL = HashMapModified[i];
						int sizeB = baseL.size();
						int sizeM = ModiL.size();

						if (0 != sizeB || 0 != sizeM)
						{
							printf("\n %d %d %d",i,sizeB,sizeM);
						}
					}
					_getch();
				}	
#pragma endregion HashMapPreview
		
				Status retComparator = Comparator.PerformKeyComparision(KeyInfoListBase,
																		KeyInfoListModified,
																		OutputCollector,
																		HashMapBase,
																		HashMapModified
																		);
				if (SUCCESS == retComparator)
				{
					CSummary::getInstance()->m_uiMatchFiles = OutputCollector.m_MatchList.size();
					CSummary::getInstance()->m_uiMismatchFiles = OutputCollector.m_MismatchList.size();
					CSummary::getInstance()->m_uiMissingFilesBase = OutputCollector.m_MissingListBase.size();
					CSummary::getInstance()->m_uiMissingFilesModified = OutputCollector.m_MissingListModified.size();
					CSummary::getInstance()->m_uiKeyReplicationBase = OutputCollector.m_KeyReplicationListBase.size();
					CSummary::getInstance()->m_uiKeyReplicationModified = OutputCollector.m_KeyReplicationListModified.size();
					CSummary::getInstance()->m_szEndTime = GetCurrentTimeString();

					String szMessage = "Start Output Generation ";				
					CLogManager::CreateLog(LOG_UI,szMessage);
					CLogManager::CreateLog(LOG_ERROR,szMessage);
					Status retOutputGenerator = OutputGenerator.GenerateOutput(OutputCollector,
																				InvalidPathListBase,
																				InvalidPathListModified
																				);
					if (SUCCESS == retOutputGenerator)
					{	
						CLogManager::CreateLog(LOG_UI,"Output Generation Complete");

						CFileDumpCreator FileDumpCreator;
						Status retFileDump = FileDumpCreator.DumpFiles(OutputCollector);
						if (SUCCESS == retFileDump)
						{
							printf("\nStart Time :- %s",CSummary::getInstance()->m_szStartTime.c_str());
							printf("\nEnd Time :- %s",CSummary::getInstance()->m_szEndTime.c_str());	
							printf("\nProcess Successful");
						}
						else
						{
							String szMessage = "Error Generating File Dump";						
							CLogManager::CreateLog(LOG_UI,szMessage);
							CLogManager::CreateLog(LOG_ERROR,szMessage);
						}
					}
					else
					{
						String szMessage = "Error Generating Output";						
						CLogManager::CreateLog(LOG_UI,szMessage);
						CLogManager::CreateLog(LOG_ERROR,szMessage);
					}
				}
				else
				{
					String szMessage = "Error Performing Key Comparisons";					
					CLogManager::CreateLog(LOG_UI,szMessage);
					CLogManager::CreateLog(LOG_ERROR,szMessage);
				}
			}
			else
			{
				String szMessage = "Error Processing ";
				szMessage.append(szDirectoryPathModified);
				CLogManager::CreateLog(LOG_UI,szMessage);
				CLogManager::CreateLog(LOG_ERROR,szMessage);
			}
		}
		else
		{
			String szMessage = "Error Processing ";
			szMessage.append(szDirectoryPathBase);
			CLogManager::CreateLog(LOG_UI,szMessage);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
		}		
	}
	else
	{
		String szMessage = "Error Reading Configuration File";
		CLogManager::CreateLog(LOG_UI,szMessage);
	}

	printf("\nDone");
	Free();
	InvalidPathListBase.clear();
	InvalidPathListModified.clear();
	CleanMemory(OutputCollector,KeyInfoListBase,KeyInfoListModified);	
	_getch();
	return 0;
}


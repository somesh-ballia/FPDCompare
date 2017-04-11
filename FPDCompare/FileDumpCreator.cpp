#include "StdAfx.h"
#include "FileDumpCreator.h"
#include "OutputCollector.h"
#include "ConfigurationStorage.h"
#include "Utility.h"
#include "CopyFileStorage.h"
#include "LogManager.h"

CFileDumpCreator::CFileDumpCreator(void)
{
}


CFileDumpCreator::~CFileDumpCreator(void)
{
}

//************************************
// Method:    DumpFiles
// FullName:  CFileDumpCreator::DumpFiles
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const COutputCollector & OutputCollector
//************************************
Status CFileDumpCreator::DumpFiles(const COutputCollector &OutputCollector)
{
	int iCounterSuccess = 1;
	int iCounterFailure = 1;
	if (CConfigurationStorage::getInstance()->GetEnableDumpFolderHierarchy())
	{
		CLogManager::CreateLog(LOG_UI,"Starting File Dump Process");
		CLogManager::CreateLog(LOG_UI,"Number of Files to dump ",OutputCollector.m_FileCopyList.size());
		std::list<CCopyFileStorage*>::const_iterator ListIterator;
		for(ListIterator = OutputCollector.m_FileCopyList.begin();ListIterator != OutputCollector.m_FileCopyList.end();ListIterator++)
		{
			CCopyFileStorage *pCopyFileStorage = *ListIterator;
			Status retCopy = CopyFile(pCopyFileStorage->m_szOldPath,pCopyFileStorage->m_szNewPath);
			if (SUCCESS == retCopy)
			{				
				CLogManager::CreateLog(LOG_UI,"Dumping File",iCounterSuccess);
				iCounterSuccess++;
			}
			else
			{
				CLogManager::CreateLog(LOG_UI,"Dumping File",iCounterFailure);
				iCounterFailure++;
				String szMessage = "Error Writing file : ";
				szMessage.append(pCopyFileStorage->m_szNewPath);
				CLogManager::CreateLog(LOG_ERROR,szMessage);
			}
		}
	}
	return SUCCESS;
}


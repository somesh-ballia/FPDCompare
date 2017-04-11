#include "StdAfx.h"
#include "ExcelFileGenerator.h"
#include "OutputCollector.h"
#include "Summary.h"
#include "MatchResource.h"
#include "MismatchResource.h"
#include "Utility.h"
#include "ConfigurationStorage.h"
#include "LogManager.h"
#include "CopyFileStorage.h"

#define BASE_DIRECTORY L"BASE DIRECTORY"
#define MODIFIED_DIRECTORY L"MODIFIED DIRECTORY"
#define META_FILE_PATH L"META FILE PATH"
#define DATA_FILE_PATH L"DATA FILE PATH"
#define PROTOCOL L"PROTOCOL"

CExcelFileGenerator::CExcelFileGenerator(void)
{
}


CExcelFileGenerator::~CExcelFileGenerator(void)
{
}

//************************************
// Method:    CreateSheatKeyReplicationFile
// FullName:  CExcelFileGenerator::CreateSheatKeyReplicationFile
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: Book * & book
// Parameter: COutputCollector & OutputCollector
//************************************
Status CExcelFileGenerator::CreateSheatKeyReplicationFile(Book *&book, COutputCollector &OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;
	int iTempRowCount = 0;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"KeyReplication");
		if (NULL == sheet)
		{
			CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in CreateSheatKeyReplicationFile");
			return FAILURE;
		}

		if(sheet)
		{
			int iCount = 1;
			std::list<CMetaFileInfo*>::const_iterator BaseListIterator;
			std::list<CMetaFileInfo*>::const_iterator ModifiedListIterator;
			sheet->writeStr(iRowCount, iColumnCount+1,BASE_DIRECTORY);			
			sheet->writeStr(iRowCount, iColumnCount+5,MODIFIED_DIRECTORY);
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,PROTOCOL);

			sheet->writeStr(iRowCount, iColumnCount+4,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+6,PROTOCOL);
			iRowCount++;
			iTempRowCount = iRowCount;

			for(BaseListIterator = OutputCollector.m_KeyReplicationListBase.begin();BaseListIterator != OutputCollector.m_KeyReplicationListBase.end();BaseListIterator++)
			{			
				CMetaFileInfo *pMetaFileInfo = (*BaseListIterator);				
				std::wstring szProtocal = pMetaFileInfo->m_szProtocal;

				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount,ConvertToHyperlink(pMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink(pMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+2,szProtocal.c_str());
				
				if (CConfigurationStorage::getInstance()->GetEnableDumpFolderHierarchy())
				{
					CCopyFileStorage *pCopyFileStorage = new CCopyFileStorage();
					String szNewPath;
					GetNewPath(pMetaFileInfo->m_szMetaFilePath,szNewPath,LIST_KEY_REPLICATION,BASE);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szMetaFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;					
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);
					
					pCopyFileStorage = new CCopyFileStorage();
					GetNewPath(pMetaFileInfo->m_szDataFilePath,szNewPath,LIST_KEY_REPLICATION,BASE);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szDataFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);					
				}

				iRowCount++;
				iCount++;
			}

			iRowCount = iTempRowCount;

			for(ModifiedListIterator = OutputCollector.m_KeyReplicationListModified.begin();ModifiedListIterator != OutputCollector.m_KeyReplicationListModified.end();ModifiedListIterator++)
			{			
				CMetaFileInfo *pMetaFileInfo = (*ModifiedListIterator);				
				std::wstring szProtocal = pMetaFileInfo->m_szProtocal;

				sheet->writeStr(iRowCount, iColumnCount+4,ConvertToHyperlink(pMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+5,ConvertToHyperlink(pMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+6,szProtocal.c_str());

				if (CConfigurationStorage::getInstance()->GetEnableDumpFolderHierarchy())
				{

					CCopyFileStorage *pCopyFileStorage = new CCopyFileStorage();
					String szNewPath;
					GetNewPath(pMetaFileInfo->m_szMetaFilePath,szNewPath,LIST_KEY_REPLICATION,MODIFIED);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szMetaFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;					
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);

					pCopyFileStorage = new CCopyFileStorage();
					GetNewPath(pMetaFileInfo->m_szDataFilePath,szNewPath,LIST_KEY_REPLICATION,MODIFIED);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szDataFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);
				}
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}

//************************************
// Method:    CreateSheatInvalidFiles
// FullName:  CExcelFileGenerator::CreateSheatInvalidFiles
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: Book * & book
// Parameter: const List_Str & InvalidPathListBase
// Parameter: const List_Str & InvalidPathListModified
//************************************
Status CExcelFileGenerator::CreateSheatInvalidFiles(Book *&book, const List_Str &InvalidPathListBase,const List_Str &InvalidPathListModified)
{
	int iRowCount = 2;
	int iColumnCount = 2;
	int iTempRowCount = 0;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"InvalidFiles");
		if (NULL == sheet)
		{
			CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in CreateSheatInvalidFiles");
			return FAILURE;
		}
		if(sheet)
		{
			int iCount = 1;
			std::list<std::string>::const_iterator BaseListIterator;
			std::list<std::string>::const_iterator ModifiedListIterator;

			sheet->writeStr(iRowCount, iColumnCount+1,BASE_DIRECTORY);			
			sheet->writeStr(iRowCount, iColumnCount+2,MODIFIED_DIRECTORY);
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount+1,L"META FILE PATH");	
			sheet->writeStr(iRowCount, iColumnCount+2,L"META FILE PATH");		
			iRowCount++;
			iTempRowCount = iRowCount;

			for(BaseListIterator = InvalidPathListBase.begin();BaseListIterator != InvalidPathListBase.end();BaseListIterator++)
			{			
				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink((*BaseListIterator)).c_str());
				iRowCount++;
				iCount++;
			}

			iRowCount = iTempRowCount;

			for(ModifiedListIterator = InvalidPathListModified.begin();ModifiedListIterator != InvalidPathListModified.end();ModifiedListIterator++)
			{			
				sheet->writeStr(iRowCount, iColumnCount+2,ConvertToHyperlink((*ModifiedListIterator)).c_str());				
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}

//************************************
// Method:    CreateSheatSummary
// FullName:  CExcelFileGenerator::CreateSheatSummary
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: Book * & book
//************************************
Status CExcelFileGenerator::CreateSheatSummary(Book *&book)
{
	int iRowCount = 2;
	int iColumnCount = 2;
	
	if(book)
	{
		Sheet* sheet = book->addSheet(L"Summary");
		if (NULL == sheet)
		{
			CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in CreateSheatSummary");
			return FAILURE;
		}
		if(sheet)
		{
			sheet->writeStr(iRowCount,iColumnCount,L"SUMMARY");

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Key");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(CSummary::getInstance()->m_szKeyList).c_str());

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"IgnoreList");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(CSummary::getInstance()->m_szIgnoreList).c_str());

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Is Unicode Enabled");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiIsUnicode);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"IsMeta Comparison Enabled");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiIsMetaComparisionEnabled);
			
			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Total Files Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiTotalFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Total Files Base Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiTotalFilesBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Total Files Modified Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiTotalFilesModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Match Files Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiMatchFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Mismatch Files Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiMismatchFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Missing Files base Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiMissingFilesBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Missing Files Modified Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiMissingFilesModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Key Replication Base Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiKeyReplicationBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Key Replication Modified Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiKeyReplicationModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Invalid Meta Files Base Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiInvalidFilesBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Invalid Meta Files Modified Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiInvalidFilesModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Ambiguous Files Count");
			sheet->writeNum(iRowCount,iColumnCount+1,CSummary::getInstance()->m_uiAmbiguousFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Start Time");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(CSummary::getInstance()->m_szStartTime).c_str());

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"EndTime");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(CSummary::getInstance()->m_szEndTime).c_str());
		}
	}
	return SUCCESS;
}

//************************************
// Method:    CreateSheatMismatchFile
// FullName:  CExcelFileGenerator::CreateSheatMismatchFile
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: Book * & book
// Parameter: COutputCollector & OutputCollector
//************************************
Status CExcelFileGenerator::CreateSheatMismatchFile(Book *&book,COutputCollector &OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"MismatchFiles");
		if (NULL == sheet)
		{
			CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in CreateSheatMismatchFile");
			return FAILURE;
		}
		if(sheet)
		{
			int iCount = 1;
			std::list<CMismatchResource*>::const_iterator ListIterator;
			sheet->writeStr(iRowCount, iColumnCount+3,BASE_DIRECTORY);			
			sheet->writeStr(iRowCount, iColumnCount+9,MODIFIED_DIRECTORY);
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,PROTOCOL);
			sheet->writeStr(iRowCount, iColumnCount+3,L"MODIFICATION");
			sheet->writeStr(iRowCount, iColumnCount+4,L"DATA CRC");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA SIZE");
			sheet->writeStr(iRowCount, iColumnCount+6,L"DETAILS");

			sheet->writeStr(iRowCount, iColumnCount+8,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+9,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+10,PROTOCOL);
			sheet->writeStr(iRowCount, iColumnCount+11,L"MODIFICATION");
			sheet->writeStr(iRowCount, iColumnCount+12,L"DATA CRC");
			sheet->writeStr(iRowCount, iColumnCount+13,L"DATA SIZE");
			sheet->writeStr(iRowCount, iColumnCount+14,L"DETAILS");

			iRowCount++;
			for(ListIterator = OutputCollector.m_MismatchList.begin();ListIterator != OutputCollector.m_MismatchList.end();ListIterator++)
			{
				CMismatchResource *pMismatchFiles = (*ListIterator);
				CResourceModificationInfo  *pBaseMetaFileModificationInfo = pMismatchFiles->m_pResourceModificationInfoBase;
				CResourceModificationInfo  *pModifiedMetaFileModificationInfo = pMismatchFiles->m_pResourceModificationInfoModified;

				CMetaFileInfo *pBaseMetaFileInfo = pBaseMetaFileModificationInfo->m_pMetaFileInfo;
				CMetaFileInfo *pModifiedFileInfo = pModifiedMetaFileModificationInfo->m_pMetaFileInfo;

				CDataFileInfo *pBaseDataFileInfo = pBaseMetaFileModificationInfo->m_pDataFileInfo;
				CDataFileInfo *pModifiedDataFileInfo = pModifiedMetaFileModificationInfo->m_pDataFileInfo;
				
				std::wstring szBaseProtocal = pBaseMetaFileInfo->m_szProtocal;
				std::wstring szModifiedProtocal = pModifiedFileInfo->m_szProtocal;

				std::string szBaseMismatchType = pBaseMetaFileModificationInfo->m_szMismatchType;
				std::string szModifiedMismatchType  = pModifiedMetaFileModificationInfo->m_szMismatchType;

				std::wstring szBaseDetails = pBaseMetaFileModificationInfo->m_szMetaDetails;
				std::wstring szModifiedDetails = pModifiedMetaFileModificationInfo->m_szMetaDetails;

				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount,ConvertToHyperlink(pBaseMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink(pBaseMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+2,szBaseProtocal.c_str());
				sheet->writeStr(iRowCount, iColumnCount+3,ConvertToWString(szBaseMismatchType).c_str());
				sheet->writeNum(iRowCount, iColumnCount+4,pBaseDataFileInfo->m_lCRCValue);
				sheet->writeNum(iRowCount, iColumnCount+5,pBaseDataFileInfo->m_lSize);
				sheet->writeStr(iRowCount, iColumnCount+6,szBaseDetails.c_str());

				sheet->writeStr(iRowCount, iColumnCount+8,ConvertToHyperlink(pModifiedFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+9,ConvertToHyperlink(pModifiedFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+10,szModifiedProtocal.c_str());
				sheet->writeStr(iRowCount, iColumnCount+11,ConvertToWString(szModifiedMismatchType).c_str());
				sheet->writeNum(iRowCount, iColumnCount+12,pModifiedDataFileInfo->m_lCRCValue);
				sheet->writeNum(iRowCount, iColumnCount+13,pModifiedDataFileInfo->m_lSize);
				sheet->writeStr(iRowCount, iColumnCount+14,szModifiedDetails.c_str());

				if (CConfigurationStorage::getInstance()->GetEnableDumpFolderHierarchy())
				{
					CCopyFileStorage *pCopyFileStorage = new CCopyFileStorage();
					String szNewPath;
					GetNewPath(pBaseMetaFileInfo->m_szMetaFilePath,szNewPath,LIST_MISMATCH,BASE);
					pCopyFileStorage->m_szOldPath = pBaseMetaFileInfo->m_szMetaFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;					
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);

					pCopyFileStorage = new CCopyFileStorage();
					GetNewPath(pBaseMetaFileInfo->m_szDataFilePath,szNewPath,LIST_MISMATCH,BASE);
					pCopyFileStorage->m_szOldPath = pBaseMetaFileInfo->m_szDataFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);

					pCopyFileStorage = new CCopyFileStorage();					
					GetNewPath(pModifiedFileInfo->m_szMetaFilePath,szNewPath,LIST_MISMATCH,MODIFIED);
					pCopyFileStorage->m_szOldPath = pModifiedFileInfo->m_szMetaFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;					
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);

					pCopyFileStorage = new CCopyFileStorage();
					GetNewPath(pModifiedFileInfo->m_szDataFilePath,szNewPath,LIST_MISMATCH,MODIFIED);
					pCopyFileStorage->m_szOldPath = pModifiedFileInfo->m_szDataFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);					
				}				

				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;	
}

//************************************
// Method:    CreateSheatMissingFile
// FullName:  CExcelFileGenerator::CreateSheatMissingFile
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: Book * & book
// Parameter: COutputCollector & OutputCollector
//************************************
Status CExcelFileGenerator::CreateSheatMissingFile(Book *&book,COutputCollector &OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;
	int iTempRowCount = 0;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"MissingFile");
		if (NULL == sheet)
		{
			CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in CreateSheatMissingFile");
			return FAILURE;
		}
		if(sheet)
		{
			int iCount = 1;
			std::list<CMetaFileInfo*>::const_iterator BaseListIterator;
			std::list<CMetaFileInfo*>::const_iterator ModifiedListIterator;
			sheet->writeStr(iRowCount, iColumnCount+1,BASE_DIRECTORY);			
			sheet->writeStr(iRowCount, iColumnCount+5,MODIFIED_DIRECTORY);
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,PROTOCOL);

			sheet->writeStr(iRowCount, iColumnCount+4,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+6,PROTOCOL);
			iRowCount++;
			iTempRowCount = iRowCount;


			for(BaseListIterator = OutputCollector.m_MissingListBase.begin();BaseListIterator != OutputCollector.m_MissingListBase.end();BaseListIterator++)
			{			
				CMetaFileInfo *pMetaFileInfo = (*BaseListIterator);				
				std::wstring szProtocal = pMetaFileInfo->m_szProtocal;

				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount,ConvertToHyperlink(pMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink(pMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+2,szProtocal.c_str());

				if (CConfigurationStorage::getInstance()->GetEnableDumpFolderHierarchy())
				{
					CCopyFileStorage *pCopyFileStorage = new CCopyFileStorage();
					String szNewPath;
					GetNewPath(pMetaFileInfo->m_szMetaFilePath,szNewPath,LIST_MISSING,BASE);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szMetaFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;					
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);

					pCopyFileStorage = new CCopyFileStorage();
					GetNewPath(pMetaFileInfo->m_szDataFilePath,szNewPath,LIST_MISSING,BASE);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szDataFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);					
				}

				iRowCount++;
				iCount++;
			}

			iRowCount = iTempRowCount;

			for(ModifiedListIterator = OutputCollector.m_MissingListModified.begin();ModifiedListIterator != OutputCollector.m_MissingListModified.end();ModifiedListIterator++)
			{			
				CMetaFileInfo *pMetaFileInfo = (*ModifiedListIterator);				
				std::wstring szProtocal = pMetaFileInfo->m_szProtocal;

				sheet->writeStr(iRowCount, iColumnCount+4,ConvertToHyperlink(pMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+5,ConvertToHyperlink(pMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+6,szProtocal.c_str());

				if (CConfigurationStorage::getInstance()->GetEnableDumpFolderHierarchy())
				{
					CCopyFileStorage *pCopyFileStorage = new CCopyFileStorage();
					String szNewPath;
					GetNewPath(pMetaFileInfo->m_szMetaFilePath,szNewPath,LIST_MISSING,MODIFIED);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szMetaFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;					
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);

					pCopyFileStorage = new CCopyFileStorage();
					GetNewPath(pMetaFileInfo->m_szDataFilePath,szNewPath,LIST_MISSING,MODIFIED);
					pCopyFileStorage->m_szOldPath = pMetaFileInfo->m_szDataFilePath;
					pCopyFileStorage->m_szNewPath = szNewPath;
					OutputCollector.m_FileCopyList.push_back(pCopyFileStorage);					
				}
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}

//************************************
// Method:    CreateSheatMatchFile
// FullName:  CExcelFileGenerator::CreateSheatMatchFile
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: Book * & book
// Parameter: COutputCollector & OutputCollector
//************************************
Status CExcelFileGenerator::CreateSheatMatchFile(Book *&book,COutputCollector &OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"MatchFile");
		if (NULL == sheet)
		{
			CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in CreateSheatMatchFile");
			return FAILURE;
		}

		if(sheet)
		{
			int iCount = 1;
			std::list<CMatchResource*>::const_iterator ListIterator;
			sheet->writeStr(iRowCount, iColumnCount+1,BASE_DIRECTORY);			
			sheet->writeStr(iRowCount, iColumnCount+5,MODIFIED_DIRECTORY);
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,PROTOCOL);

			sheet->writeStr(iRowCount, iColumnCount+4,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+6,PROTOCOL);
			iRowCount++;
			for(ListIterator = OutputCollector.m_MatchList.begin();ListIterator != OutputCollector.m_MatchList.end();ListIterator++)
			{
				CMatchResource *pMatchFiles = (*ListIterator);
				CMetaFileInfo  *pBaseMetaFileInfo = pMatchFiles->m_pBaseFileInfo;
				CMetaFileInfo *pModifiedFileInfo = pMatchFiles->m_pModifiedFileInfo;

				std::wstring szBaseProtocal = pBaseMetaFileInfo->m_szProtocal;
				std::wstring szModifiedProtocal = pModifiedFileInfo->m_szProtocal;
				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount,ConvertToHyperlink(pBaseMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink(pBaseMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+2,szBaseProtocal.c_str());

				sheet->writeStr(iRowCount, iColumnCount+4,ConvertToHyperlink(pModifiedFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+5,ConvertToHyperlink(pModifiedFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+6,szModifiedProtocal.c_str());
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}


//************************************
// Method:    GenerateFile
// FullName:  CExcelFileGenerator::GenerateFile
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: COutputCollector & OutputCollector
// Parameter: const List_Str & InvalidPathListBase
// Parameter: const List_Str & InvalidPathListModified
//************************************
Status CExcelFileGenerator::GenerateFile(COutputCollector &OutputCollector, const List_Str &InvalidPathListBase, const List_Str &InvalidPathListModified)
{
	Book* book = xlCreateBook();
	if (NULL == book)
	{
		CLogManager::CreateLog(LOG_ERROR,"Invalid excel Sheet in GenerateFile");
		return FAILURE;
	}
	Status retSummary = CreateSheatSummary(book);
	Status retMatchFile = CreateSheatMatchFile(book,OutputCollector);
	Status retMismatchFile = CreateSheatMismatchFile(book,OutputCollector);
	Status retMissingFile = CreateSheatMissingFile(book,OutputCollector);
	Status retKeyReplication = CreateSheatKeyReplicationFile(book,OutputCollector);
	Status retInvalidFiles = CreateSheatInvalidFiles(book,InvalidPathListBase,InvalidPathListModified);

	if (SUCCESS == retMatchFile && SUCCESS == retMismatchFile && SUCCESS == retMissingFile && SUCCESS == retSummary && SUCCESS == retInvalidFiles && SUCCESS == retKeyReplication)
	{
		String szSaveFilePath;
		CConfigurationStorage::getInstance()->GetOutputPath(szSaveFilePath);
		if(book->save(ConvertToWString(szSaveFilePath).c_str())) 
		{
			::ShellExecuteW(NULL,(LPCWSTR) "open",(LPCWSTR) ConvertToWString(szSaveFilePath).c_str(), NULL, NULL, SW_SHOW);        
			book->release();		
			return SUCCESS;
		}
		else
		{
			std::cout << book->errorMessage() << std::endl;
			book->release();		
			String szMessage = "Error Saving Output File :";
			szMessage.append(szSaveFilePath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;
		}		
	}
	else
	{
		CLogManager::CreateLog(LOG_ERROR,"Error in Creating excel sheets");
		return FAILURE;
	}	
}
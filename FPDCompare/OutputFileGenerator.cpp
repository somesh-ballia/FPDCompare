#include "StdAfx.h"
#include "OutputFileGenerator.h"


COutputFileGenerator::COutputFileGenerator(void)
{
}


COutputFileGenerator::~COutputFileGenerator(void)
{
}

Status COutputFileGenerator::GetNewPath( const std::string szOldPath, std::string &szNewPath,const ListType ltType , const DirectoryType dtType )
{
	std::string szDumpPath = "D:\\xxx";

	std::string szMeta = "\\Meta\\";
	std::string szData = "\\Data\\";
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
	case MISMATCH_LIST:
		szType = "\\MISMATCH";
		break;
	case MISSING_LIST:
		szType = "\\MISSING";
		break;
	case KEY_REPLICATION_LIST:
		szType = "\\KEYREPLICATION";
		break;
	case MATCH_LIST :
		szType = "\\MATCH";
		break;;
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

Status Copy(std::string szFrom,std::string szTo)
{
	std::ifstream in (szFrom.c_str());
	std::ofstream out (szTo.c_str());
	out << in.rdbuf();
	out.close();
	in.close();
	return SUCCESS;
}

Status COutputFileGenerator::CopyFiles(const std::string szOldPath,ListType ltType,DirectoryType dtType )
{
	std::string szNewPath;
	Status retGetNewPath = GetNewPath(szOldPath,szNewPath,ltType,dtType);

	if (SUCCESS == retGetNewPath)
	{
		//BOOL retStatus = Copy(szOldPath,szNewPath);
		BOOL retStatus = CopyFile((LPCSTR)szOldPath.c_str(),(LPCSTR)szNewPath.c_str(),FALSE);
		DWORD err = GetLastError();
		if (SUCCESS == retStatus)
		{
			return SUCCESS;
		}
		else
		{
			return FAILURE;
		}	
	}
	else
	{
		return FAILURE;
	}
}


std::wstring COutputFileGenerator::ConvertToWString(const std::string szInputString)
{
	std::wstring szOutputString;
	szOutputString.assign(szInputString.begin(),szInputString.end());
	return szOutputString;
}

std::wstring COutputFileGenerator::ConvertToHyperlink(const std::string szFilePath)
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

Status COutputFileGenerator::MatchFile(Book *&book,const COutputCollector OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"MatchFile");
		if (NULL == sheet)
		{
			return FAILURE;
		}

		if(sheet)
		{
			int iCount = 1;
			std::list<CMatchFiles*>::const_iterator ListIterator;
			sheet->writeStr(iRowCount, iColumnCount+1,L"BASE DIRECTORY");			
			sheet->writeStr(iRowCount, iColumnCount+5,L"MODIFIED DIRECTORY");
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,L"PROTOCAL");

			sheet->writeStr(iRowCount, iColumnCount+4,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+6,L"PROTOCAL");
			iRowCount++;
			for(ListIterator = OutputCollector.m_MatchList.begin();ListIterator != OutputCollector.m_MatchList.end();ListIterator++)
			{
				CMatchFiles *pMatchFiles = (*ListIterator);
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

Status COutputFileGenerator::MismatchFile(Book *&book,COutputCollector OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"MismatchFiles");
		if (NULL == sheet)
		{
			return FAILURE;
		}
		if(sheet)
		{
			int iCount = 1;
			std::list<CMisMatchFiles*>::const_iterator ListIterator;
			sheet->writeStr(iRowCount, iColumnCount+3,L"BASE DIRECTORY");			
			sheet->writeStr(iRowCount, iColumnCount+9,L"MODIFIED DIRECTORY");
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,L"PROTOCAL");
			sheet->writeStr(iRowCount, iColumnCount+3,L"MODIFICATION");
			sheet->writeStr(iRowCount, iColumnCount+4,L"DATA CRC");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA SIZE");
			sheet->writeStr(iRowCount, iColumnCount+6,L"DETAILS");

			sheet->writeStr(iRowCount, iColumnCount+8,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+9,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+10,L"PROTOCAL");
			sheet->writeStr(iRowCount, iColumnCount+11,L"MODIFICATION");
			sheet->writeStr(iRowCount, iColumnCount+12,L"DATA CRC");
			sheet->writeStr(iRowCount, iColumnCount+13,L"DATA SIZE");
			sheet->writeStr(iRowCount, iColumnCount+14,L"DETAILS");

			iRowCount++;
			for(ListIterator = OutputCollector.m_MissMatchList.begin();ListIterator != OutputCollector.m_MissMatchList.end();ListIterator++)
			{
				CMisMatchFiles *pMismatchFiles = (*ListIterator);
				CMetaFileModificationInfo  *pBaseMetaFileModificationInfo = pMismatchFiles->m_pBaseFileModificationInfo;
				CMetaFileModificationInfo  *pModifiedMetaFileModificationInfo = pMismatchFiles->m_pModifiedFileModificationInfo;

				CMetaFileInfo *pBaseMetaFileInfo = pBaseMetaFileModificationInfo->m_pMetaFileInfo;
				CMetaFileInfo *pModifiedFileInfo = pModifiedMetaFileModificationInfo->m_pMetaFileInfo;

				std::wstring szBaseProtocal = pBaseMetaFileInfo->m_szProtocal;
				std::wstring szModifiedProtocal = pModifiedFileInfo->m_szProtocal;

				std::string szBaseMismatchType = pBaseMetaFileModificationInfo->m_szMissmatchType;
				std::string szModifiedMismatchType  = pModifiedMetaFileModificationInfo->m_szMissmatchType;

				std::wstring szBaseDetails = pBaseMetaFileModificationInfo->m_szMetaDetails;
				std::wstring szModifiedDetails = pModifiedMetaFileModificationInfo->m_szMetaDetails;

				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount,ConvertToHyperlink(pBaseMetaFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink(pBaseMetaFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+2,szBaseProtocal.c_str());
				sheet->writeStr(iRowCount, iColumnCount+3,ConvertToWString(szBaseMismatchType).c_str());
				sheet->writeNum(iRowCount, iColumnCount+4,pBaseMetaFileModificationInfo->m_ulCRCValue);
				sheet->writeNum(iRowCount, iColumnCount+5,pBaseMetaFileModificationInfo->m_ulFileSize);
				sheet->writeStr(iRowCount, iColumnCount+6,szBaseDetails.c_str());

				sheet->writeStr(iRowCount, iColumnCount+8,ConvertToHyperlink(pModifiedFileInfo->m_szMetaFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+9,ConvertToHyperlink(pModifiedFileInfo->m_szDataFilePath).c_str());
				sheet->writeStr(iRowCount, iColumnCount+10,szModifiedProtocal.c_str());
				sheet->writeStr(iRowCount, iColumnCount+11,ConvertToWString(szModifiedMismatchType).c_str());
				sheet->writeNum(iRowCount, iColumnCount+12,pModifiedMetaFileModificationInfo->m_ulCRCValue);
				sheet->writeNum(iRowCount, iColumnCount+13,pModifiedMetaFileModificationInfo->m_ulFileSize);
				sheet->writeStr(iRowCount, iColumnCount+14,szModifiedDetails.c_str());
				
				CopyFiles(pBaseMetaFileInfo->m_szMetaFilePath,MISMATCH_LIST,BASE);
				CopyFiles(pBaseMetaFileInfo->m_szDataFilePath,MISMATCH_LIST,BASE);

				CopyFiles(pModifiedFileInfo->m_szMetaFilePath,MISMATCH_LIST,MODIFIED);
				CopyFiles(pModifiedFileInfo->m_szDataFilePath,MISMATCH_LIST,MODIFIED);
								
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;	
}
Status COutputFileGenerator::KeyReplication( Book *&book, COutputCollector OutputCollector )
{
	int iRowCount = 2;
	int iColumnCount = 2;
	int iTempRowCount = 0;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"KeyReplication");
		if (NULL == sheet)
		{
			return FAILURE;
		}

		if(sheet)
		{
			int iCount = 1;
			std::list<CMetaFileInfo*>::const_iterator BaseListIterator;
			std::list<CMetaFileInfo*>::const_iterator ModifiedListIterator;
			sheet->writeStr(iRowCount, iColumnCount+1,L"BASE DIRECTORY");			
			sheet->writeStr(iRowCount, iColumnCount+5,L"MODIFIED DIRECTORY");
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,L"PROTOCAL");

			sheet->writeStr(iRowCount, iColumnCount+4,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+6,L"PROTOCAL");
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
				
				CopyFiles(pMetaFileInfo->m_szMetaFilePath,KEY_REPLICATION_LIST,BASE);
				CopyFiles(pMetaFileInfo->m_szDataFilePath,KEY_REPLICATION_LIST,BASE);

				
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
				
				CopyFiles(pMetaFileInfo->m_szMetaFilePath,KEY_REPLICATION_LIST,MODIFIED);
				CopyFiles(pMetaFileInfo->m_szDataFilePath,KEY_REPLICATION_LIST,MODIFIED);
								
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}


Status COutputFileGenerator::MissingFile(Book *&book,COutputCollector OutputCollector)
{
	int iRowCount = 2;
	int iColumnCount = 2;
	int iTempRowCount = 0;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"MissingFile");
		if (NULL == sheet)
		{
			return FAILURE;
		}
		if(sheet)
		{
			int iCount = 1;
			std::list<CMetaFileInfo*>::const_iterator BaseListIterator;
			std::list<CMetaFileInfo*>::const_iterator ModifiedListIterator;
			sheet->writeStr(iRowCount, iColumnCount+1,L"BASE DIRECTORY");			
			sheet->writeStr(iRowCount, iColumnCount+5,L"MODIFIED DIRECTORY");
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+1,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+2,L"PROTOCAL");

			sheet->writeStr(iRowCount, iColumnCount+4,L"META FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+5,L"DATA FILE PATH");
			sheet->writeStr(iRowCount, iColumnCount+6,L"PROTOCAL");
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
			
				CopyFiles(pMetaFileInfo->m_szMetaFilePath,MISSING_LIST,BASE);
				CopyFiles(pMetaFileInfo->m_szDataFilePath,MISSING_LIST,BASE);

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
				
				CopyFiles(pMetaFileInfo->m_szMetaFilePath,MISSING_LIST,MODIFIED);
				CopyFiles(pMetaFileInfo->m_szDataFilePath,MISSING_LIST,MODIFIED);

				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}

Status COutputFileGenerator::Summary(Book *&book,CSummary sSummary)
{
	int iRowCount = 2;
	int iColumnCount = 2;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"Summary");
		if (NULL == sheet)
		{
			return FAILURE;
		}
		if(sheet)
		{
			sheet->writeStr(iRowCount,iColumnCount,L"SUMMARY");

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Key");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(sSummary.m_szKeyList).c_str());

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"IgnoreList");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(sSummary.m_szIgnoreList).c_str());

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Total Files");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_TotalFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Total Files Base");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_TotalFilesBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Total Files Modified");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_TotalFilesModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Match Files");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_MatchFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Mismatch Files");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_MismatchFiles);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Missing Files base");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_MissingFilesBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Missing Files Modified");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_MissingFilesModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Key Replication Base");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_KeyReplicationBase);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Key Replication Modified");
			sheet->writeNum(iRowCount,iColumnCount+1,sSummary.m_KeyReplicationModified);

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"Start Time");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(sSummary.m_szStartTime).c_str());

			iRowCount++;
			sheet->writeStr(iRowCount,iColumnCount,L"EndTime");
			sheet->writeStr(iRowCount,iColumnCount+1,ConvertToWString(sSummary.m_szEndTime).c_str());
		}
	}
	return SUCCESS;
}

Status COutputFileGenerator::InvalidFiles(Book *&book,std::list<std::string> InvalidPathListBase,std::list<std::string> InvalidPathListModified)
{
	int iRowCount = 2;
	int iColumnCount = 2;
	int iTempRowCount = 0;

	if(book)
	{
		Sheet* sheet = book->addSheet(L"InvalidFiles");
		if (NULL == sheet)
		{
			return FAILURE;
		}
		if(sheet)
		{
			int iCount = 1;
			std::list<std::string>::const_iterator BaseListIterator;
			std::list<std::string>::const_iterator ModifiedListIterator;

			sheet->writeStr(iRowCount, iColumnCount+1,L"BASE DIRECTORY");			
			sheet->writeStr(iRowCount, iColumnCount+2,L"MODIFIED DIRECTORY");
			iRowCount++;
			sheet->writeStr(iRowCount, iColumnCount+1,L"META FILE PATH");	
			sheet->writeStr(iRowCount, iColumnCount+2,L"META FILE PATH");		
			iRowCount++;
			iTempRowCount = iRowCount;

			for(BaseListIterator = InvalidPathListBase.begin();BaseListIterator != InvalidPathListBase.end();BaseListIterator++)
			{			
				sheet->writeNum(iRowCount, iColumnCount-1, iCount);
				sheet->writeStr(iRowCount, iColumnCount,ConvertToHyperlink((*BaseListIterator)).c_str());
				iRowCount++;
				iCount++;
			}

			iRowCount = iTempRowCount;

			for(ModifiedListIterator = InvalidPathListModified.begin();ModifiedListIterator != InvalidPathListModified.end();ModifiedListIterator++)
			{			
				sheet->writeStr(iRowCount, iColumnCount+1,ConvertToHyperlink((*ModifiedListIterator)).c_str());				
				iRowCount++;
				iCount++;
			}
		}		
	}
	return SUCCESS;
}

Status COutputFileGenerator::GenerateFile(std::string szFilePath,const COutputCollector OutputCollector,CSummary sSummary,std::list<std::string> InvalidPathListBase,std::list<std::string> InvalidPathListModified)
{
	Book* book = xlCreateBook();
	if (NULL == book)
	{
		return FAILURE;
	}
	Status retSummary = Summary(book,sSummary);
	Status retMatchFile = MatchFile(book,OutputCollector);
	Status retMismatchFile = MismatchFile(book,OutputCollector);
	Status retMissingFile = MissingFile(book,OutputCollector);
	Status retKeyReplication = KeyReplication(book,OutputCollector);
	Status retInvalidFiles = InvalidFiles(book,InvalidPathListBase,InvalidPathListModified);

	if (SUCCESS == retMatchFile && SUCCESS == retMismatchFile && SUCCESS == retMissingFile && SUCCESS == retSummary && SUCCESS == retInvalidFiles && SUCCESS == retKeyReplication)
	{
		if(book->save(ConvertToWString(szFilePath).c_str())) 
		{
			::ShellExecuteW(NULL,(LPCWSTR) "open",(LPCWSTR) ConvertToWString(szFilePath).c_str(), NULL, NULL, SW_SHOW);        
			book->release();		
			return SUCCESS;
		}
		else
		{
			std::cout << book->errorMessage() << std::endl;
			book->release();		
			return FAILURE;
		}		
	}
	else
	{
		return FAILURE;
	}	
}

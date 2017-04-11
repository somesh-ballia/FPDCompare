#include "StdAfx.h"
#include "Comparator.h"
#include "KeyInfo.h"
#include "OutputCollector.h"
#include "MetaPropertSubValue_DateTime.h"
#include "MetaPropertSubValue_FileName.h"
#include "MetaPropertSubValue_Integer.h"
#include "MetaPropertSubValue_String.h"
#include "MetaPropertyValue.h"
#include "MetaProperty.h"
#include "MetaPropertySubValue.h"
#include "DataFileInfo.h"
#include "Utility.h"
#include "MetaReader.h"
#include "CommonAll.h"
#include "OutputCollector.h"
#include "ConfigurationStorage.h"
#include "MatchResource.h"
#include "MismatchResource.h"
#include "LogManager.h"

#define PROTOCAL L"ISProtocolName"
#define MISMATCH_TYPE_DATA "D"
#define MISMATCH_TYPE_META "M"

CComparator::CComparator(void)
{
}

CComparator::~CComparator(void)
{
}

//************************************
// Method:    CheckKeyReplication
// FullName:  CComparator::CheckKeyReplication
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const std::list<CKeyInfo * > & KeyInfoListBase
// Parameter: const std::list<CKeyInfo * > & KeyInfoListModified
// Parameter: std::list<CKeyInfo * > * HashMapBase
// Parameter: std::list<CKeyInfo * > * HashMapModified
//************************************
Status CComparator::CheckKeyReplication(const std::list<CKeyInfo*> &KeyInfoListBase,
										const std::list<CKeyInfo*> &KeyInfoListModified, 
											  std::list<CKeyInfo*> *HashMapBase, 
											  std::list<CKeyInfo*> *HashMapModified 
											  )
{
	std::list<CKeyInfo*>::const_iterator ListIteratorBase;
	std::list<CKeyInfo*>::const_iterator ListIteratorModified;
	unsigned short usCounter = 0;		
	int iTotalCounter = 0;
	CKeyInfo *pKeyInfoBase = NULL;
	CKeyInfo *pKeyInfoModified = NULL;
	CKeyInfo *pKeyInfoTemp = NULL;

	for(ListIteratorBase = KeyInfoListBase.begin();ListIteratorBase != KeyInfoListBase.end();ListIteratorBase++)
	{		
		pKeyInfoBase = *ListIteratorBase;
		std::list<CKeyInfo*> &HashMapList = HashMapModified[GetSmallHashValue(pKeyInfoBase->m_HashValue)];
		if (0 != HashMapList.size())
		{
			usCounter = 0;
			for(ListIteratorModified = HashMapList.begin();ListIteratorModified != HashMapList.end();ListIteratorModified++)
			{			
				pKeyInfoModified = *ListIteratorModified;
				bool bIsSuccessful = false;
				CLogManager::CreateLog(LOG_UI,"Processing Key Replication ",iTotalCounter);				
				iTotalCounter++;					

				Status retCompare = pKeyInfoBase->Compare(pKeyInfoModified,bIsSuccessful);
				if (SUCCESS == retCompare)
				{
					if (bIsSuccessful)
					{
						usCounter++;

						if(1 == usCounter)
						{
							pKeyInfoTemp = pKeyInfoModified;
						}				

						if (1 < usCounter)
						{
							if (2 == usCounter)
							{
								pKeyInfoTemp->m_bIsInvalid = true;
							}

							pKeyInfoModified->m_bIsInvalid = true;
							pKeyInfoBase->m_bIsInvalid = true;
						}
					}					
				}
				else
				{						
					CLogManager::CreateLog(LOG_ERROR,"CComparator::CheckKeyReplication Error comparing key info");
				}							
			}
		}		
	}	
	return SUCCESS;
}


//************************************
// Method:    PerformKeyComparision
// FullName:  CComparator::PerformKeyComparision
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const std::list<CKeyInfo * > & KeyInfoBase
// Parameter: const std::list<CKeyInfo * > & KeyInfoModified
// Parameter: COutputCollector & OutputCollector
// Parameter: std::list<CKeyInfo * > * HashMapBase
// Parameter: std::list<CKeyInfo * > * HashMapModified
//************************************
Status CComparator::PerformKeyComparision(const std::list<CKeyInfo*> &KeyInfoBase,
										  const std::list<CKeyInfo*> &KeyInfoModified, 
										  COutputCollector &OutputCollector, 
										  std::list<CKeyInfo*> *HashMapBase, 
										  std::list<CKeyInfo*> *HashMapModified 
										  )
{
	std::list<CKeyInfo*>::const_iterator ListIteratorBase;
	std::list<CKeyInfo*>::const_iterator ListIteratorModified;

	int iCount = 0;

	if (NULL == HashMapBase || NULL == HashMapModified)
	{
		CLogManager::CreateLog(LOG_ERROR,"CComparator::PerformKeyComparision NULL Hash Map");
		return FAILURE;
	}

	if (0 == KeyInfoBase.size() || 0 == KeyInfoModified.size())
	{
		CLogManager::CreateLog(LOG_ERROR,"CComparator::PerformKeyComparision Empty Lists");
		return FAILURE;
	}
	Status retKeyReplication = CheckKeyReplication(KeyInfoBase,KeyInfoModified,HashMapBase,HashMapModified);

	if (SUCCESS == retKeyReplication)
	{
		for (ListIteratorBase = KeyInfoBase.begin();ListIteratorBase != KeyInfoBase.end();ListIteratorBase++)
		{
			CKeyInfo *pKeyInfoBase = *ListIteratorBase;

			if (!pKeyInfoBase->m_bMatched && !pKeyInfoBase->m_bIsInvalid)
			{
				std::list<CKeyInfo*> &HashMapList = HashMapModified[GetSmallHashValue(pKeyInfoBase->m_HashValue)];

				if (0 != HashMapList.size())
				{
					for (ListIteratorModified = HashMapList.begin();ListIteratorModified != HashMapList.end();ListIteratorModified++)
					{
						CKeyInfo *pKeyInfoModified = *ListIteratorModified;

						if (!pKeyInfoModified->m_bMatched && !pKeyInfoModified->m_bIsInvalid)
						{
							bool bIsSuccessful = false;
							Status retCompare = pKeyInfoBase->Compare(pKeyInfoModified,bIsSuccessful);
							if (SUCCESS == retCompare)
							{
								// if match is successful
								if (bIsSuccessful)
								{
									CDataFileInfo *pDataFileInfoBase = new CDataFileInfo();
									CDataFileInfo *pDataFileInfoModified = new CDataFileInfo();

									Wstring szDetailsBase;
									Wstring szDetailsModified;

									String szDataFileInfoBase;
									String szDataFileInfoModified;

									Status retCalcDataFileInfoBase = CalculateDataFileInfo(pKeyInfoBase->m_MetaFilePath,
																						   pDataFileInfoBase
																						   );
									if (SUCCESS == retCalcDataFileInfoBase)
									{
										Status retCalcDataFileInfoModified = CalculateDataFileInfo(pKeyInfoModified->m_MetaFilePath,
																								  pDataFileInfoModified
																								  );
										if (SUCCESS == retCalcDataFileInfoModified)
										{
											Status retDataMatch = MatchDataProperty(pDataFileInfoBase,
																					pDataFileInfoModified
																					);

											Status retMetaMatch = MatchMetaFile(pKeyInfoBase->m_MetaFilePath,
																				pKeyInfoModified->m_MetaFilePath,
																				szDetailsBase,
																				szDetailsModified
																				);
											
											CLogManager::CreateLog(LOG_UI,"Processing ",iCount);				
											iCount++;
											
											if (SUCCESS == retDataMatch && SUCCESS == retMetaMatch)
											{
												// match condition
												Status retProcessMatchCondition = ProcessMatchCondition(pKeyInfoBase,
																										pKeyInfoModified,
																										OutputCollector
																										);
												if (SUCCESS == retProcessMatchCondition)
												{
													break;
												}
												else
												{
													String szMessage = "CComparator::PerformKeyComparision Error processing Matchch Condition ";													
													CLogManager::CreateLog(LOG_ERROR,szMessage);
												}

											}
											else
											{
												// mismatch condition
												Status retMismatchCondition = ProcessMismatchCondition(pKeyInfoBase,
																										pKeyInfoModified,
																										retDataMatch,
																									    retMetaMatch,
																										szDetailsBase,
																										szDetailsModified,
																										pDataFileInfoBase,
																										pDataFileInfoModified,
																										OutputCollector
																										);
												if (SUCCESS == retMismatchCondition)
												{
													break;
												}
												else
												{
													String szMessage = "CComparator::PerformKeyComparision Error Processing mismatch condition ";													
													CLogManager::CreateLog(LOG_ERROR,szMessage);
												}												
											}

										}
										else
										{
											String szMessage = "CComparator::PerformKeyComparision Error Fetching Data file info ";
											szMessage.append(szDataFileInfoModified);
											CLogManager::CreateLog(LOG_ERROR,szMessage);
										}
									}
									else
									{
										String szMessage = "CComparator::PerformKeyComparision Error Fetching Data file info ";
										szMessage.append(szDataFileInfoBase);
										CLogManager::CreateLog(LOG_ERROR,szMessage);
									}
								}								
							}
							else
							{
								String szMessage = "CComparator::PerformKeyComparision Error Performing comparision ";								
								CLogManager::CreateLog(LOG_ERROR,szMessage);
							}
						}
					}
				}
			}			
		}

		Status retMissingCondition = ProcessMissingCondition(KeyInfoBase,
																KeyInfoModified,
																OutputCollector
																);
		if (FAILURE == retMissingCondition)
		{
			String szMessage = "CComparator::PerformKeyComparision Error Processing Missing Condition ";		
			CLogManager::CreateLog(LOG_ERROR,szMessage);
		}
	}
	return SUCCESS;
}


//************************************
// Method:    MatchMetaFile
// FullName:  CComparator::MatchMetaFile
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaFilePathBase
// Parameter: const String & szMetaFilePathModified
// Parameter: Wstring & szMismatchDetailsBase
// Parameter: Wstring & szMismatchDetailsModified
//************************************
Status CComparator::MatchMetaFile( const String &szMetaFilePathBase, 
								   const String &szMetaFilePathModified,  
								   Wstring &szMismatchDetailsBase, 
								   Wstring &szMismatchDetailsModified 
								   )
{
	Status retStatus = FAILURE;
	if(CConfigurationStorage::getInstance()->GetEnableMatchMetaStatus())
	{
		CMetaReader MetaReader;
		CMetaPropertySet *pMetaPropertyBase = new CMetaPropertySet();
		CMetaPropertySet *pMetaPropertyModified = new CMetaPropertySet();

		Status retReadMetaFileBase = MetaReader.ReadMetaFile(szMetaFilePathBase,
															 pMetaPropertyBase,
															 false
															 );

		Status retReadMetaFileModified = MetaReader.ReadMetaFile(szMetaFilePathModified,
																 pMetaPropertyModified,
																 false
																 );

		if (SUCCESS == retReadMetaFileBase)
		{
			if (SUCCESS == retReadMetaFileModified)
			{
				bool bIsMatch = false;
				Status retCompare = pMetaPropertyBase->Compare(pMetaPropertyModified,
																szMismatchDetailsBase,
																szMismatchDetailsModified,
																bIsMatch
																);
				if (SUCCESS == retCompare)
				{
					if (bIsMatch)
					{
						delete pMetaPropertyBase;
						delete pMetaPropertyModified;						
						return SUCCESS;
					}
					else
					{
						delete pMetaPropertyBase;
						delete pMetaPropertyModified;						
						return FAILURE;
					}
				}
				else
				{
					String szMessage = "CComparator::MatchMetaFile Error Performing comparision  ";
					szMessage.append(szMetaFilePathBase);
					szMessage.append("  ");
					szMessage.append(szMetaFilePathModified);
					CLogManager::CreateLog(LOG_ERROR,szMessage);
					delete pMetaPropertyBase;
					delete pMetaPropertyModified;					
					return FAILURE;
				}
			}
			else
			{
				delete pMetaPropertyModified;
				String szMessage = "CComparator::MatchMetaFile Error Reading Meta Files  ";				
				szMessage.append(szMetaFilePathModified);
				CLogManager::CreateLog(LOG_ERROR,szMessage);
				return FAILURE;
			}			
		}
		else
		{
			delete pMetaPropertyBase;
			String szMessage = "CComparator::MatchMetaFile Error Reading Meta Files  ";
			szMessage.append(szMetaFilePathBase);			
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;
		}
	}
	else
	{
		return SUCCESS;
	}
	
}

//************************************
// Method:    MatchDataProperty
// FullName:  CComparator::MatchDataProperty
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const CDataFileInfo * pDataFileInfoBase
// Parameter: const CDataFileInfo * pDataFileInfoModified
//************************************
Status CComparator::MatchDataProperty( const CDataFileInfo *pDataFileInfoBase,
									   const CDataFileInfo *pDataFileInfoModified 
									   )
{
	if (NULL == pDataFileInfoBase || NULL == pDataFileInfoModified)
	{
		String szMessage = "CComparator::MatchDataProperty Null Inputs  ";
		CLogManager::CreateLog(LOG_ERROR,szMessage);
		return FAILURE;		
	}

	if ((pDataFileInfoBase->m_lSize == pDataFileInfoModified->m_lSize) && 
		(pDataFileInfoBase->m_lCRCValue == pDataFileInfoModified->m_lCRCValue))
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

//************************************
// Method:    ProcessMatchCondition
// FullName:  CComparator::ProcessMatchCondition
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: CKeyInfo * pKeyInfoBase
// Parameter: CKeyInfo * pKeyInfoModified
// Parameter: COutputCollector & OutputCollector
//************************************
Status CComparator::ProcessMatchCondition(CKeyInfo			*pKeyInfoBase, 
										  CKeyInfo			*pKeyInfoModified, 
										  COutputCollector	&OutputCollector
	)
{

	if (NULL == pKeyInfoBase || NULL == pKeyInfoModified)
	{
		return FAILURE;
	}

	String szDataFilePathBase;
	String szDataFilePathModified;

	CMatchResource *pMatchFiles = new CMatchResource();
	CMetaFileInfo *pMetaFileInfoBase = new CMetaFileInfo();
	CMetaFileInfo *pMetaFileInfoModified = new CMetaFileInfo();

	pMetaFileInfoBase->m_szMetaFilePath = pKeyInfoBase->m_MetaFilePath;
	pMetaFileInfoBase->m_szDataFilePath = szDataFilePathBase;
	std::wstring szProtocalName;		

	Status retGetProtNameBase = pKeyInfoBase->m_KeyValue->GetAttributeValue(PROTOCAL,szProtocalName);
	if (SUCCESS == retGetProtNameBase)
	{
		pMetaFileInfoBase->m_szProtocal = szProtocalName;
		
		pMatchFiles->m_pBaseFileInfo = pMetaFileInfoBase;

		GetDataFileName(pKeyInfoBase->m_MetaFilePath,szDataFilePathBase);
		GetDataFileName(pKeyInfoModified->m_MetaFilePath,szDataFilePathModified);
		
		pMetaFileInfoModified->m_szMetaFilePath = pKeyInfoModified->m_MetaFilePath;
		pMetaFileInfoModified->m_szDataFilePath = szDataFilePathModified;
		pMetaFileInfoBase->m_szDataFilePath = szDataFilePathBase;

		Status retGetProtNameModi = pKeyInfoModified->m_KeyValue->GetAttributeValue(PROTOCAL,szProtocalName);										

		if (SUCCESS == retGetProtNameModi)
		{
			pMetaFileInfoModified->m_szProtocal = szProtocalName;
			pMatchFiles->m_pModifiedFileInfo = pMetaFileInfoModified;
			OutputCollector.m_MatchList.push_back(pMatchFiles);
			pKeyInfoBase->m_bMatched = true;
			pKeyInfoModified->m_bMatched = true;			
		}
		else
		{
			CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Modified List : Case Match");
			return FAILURE;
		}	
	}
	else
	{
		CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Base List : Case Match");
		return FAILURE;
	}
	return SUCCESS;
}

//************************************
// Method:    ProcessMismatchCondition
// FullName:  CComparator::ProcessMismatchCondition
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: CKeyInfo * pKeyInfoBase
// Parameter: CKeyInfo * pKeyInfoModified
// Parameter: Status IsDataMatchSuccessful
// Parameter: Status IsMetaMatchSuccessful
// Parameter: const Wstring & szDetailsBase
// Parameter: const Wstring & szDetailsModified
// Parameter: CDataFileInfo * pDataFileInfoBase
// Parameter: CDataFileInfo * pDataFileInfoModified
// Parameter: COutputCollector & OutputCollector
//************************************
Status CComparator::ProcessMismatchCondition(CKeyInfo		*pKeyInfoBase, 
											CKeyInfo		*pKeyInfoModified,
											Status			IsDataMatchSuccessful,
											Status			IsMetaMatchSuccessful,
										const Wstring		&szDetailsBase, 
										const Wstring		&szDetailsModified,
											CDataFileInfo	*pDataFileInfoBase,
											CDataFileInfo	*pDataFileInfoModified, 
											COutputCollector &OutputCollector
											)
{

	if (NULL == pKeyInfoBase || NULL == pKeyInfoModified)
	{
		return FAILURE;
	}

	String szDataFilePathBase;
	String szDataFilePathModified;

	CMismatchResource *pMismatch = new CMismatchResource();
	CResourceModificationInfo *pResourceModificationInfoBase = new CResourceModificationInfo();
	CResourceModificationInfo *pResourceModificationInfoModified = new CResourceModificationInfo();

	pResourceModificationInfoBase->m_pDataFileInfo = pDataFileInfoBase;		
	pResourceModificationInfoModified->m_pDataFileInfo = pDataFileInfoModified;

	if(FAILURE == IsDataMatchSuccessful)
	{											
		pResourceModificationInfoBase->m_szMismatchType = MISMATCH_TYPE_DATA;	
		pResourceModificationInfoModified->m_szMismatchType = MISMATCH_TYPE_DATA;
	}

	CMetaFileInfo *pMetaFileInfoBase = new CMetaFileInfo();
	CMetaFileInfo *pMetaFileInfoModified = new CMetaFileInfo();

	pMetaFileInfoBase->m_szMetaFilePath = pKeyInfoBase->m_MetaFilePath;
	GetDataFileName(pKeyInfoBase->m_MetaFilePath,szDataFilePathBase);

	pMetaFileInfoBase->m_szDataFilePath = szDataFilePathBase;

	std::wstring szProtocalName;
	Status retGetProtNameBase = pKeyInfoBase->m_KeyValue->GetAttributeValue(PROTOCAL,szProtocalName);

	if (SUCCESS == retGetProtNameBase)
	{
		pMetaFileInfoBase->m_szProtocal = szProtocalName;
		pResourceModificationInfoBase->m_pMetaFileInfo = pMetaFileInfoBase;
		GetDataFileName(pKeyInfoModified->m_MetaFilePath,szDataFilePathModified);
		pMetaFileInfoModified->m_szMetaFilePath = pKeyInfoModified->m_MetaFilePath;
		pMetaFileInfoModified->m_szDataFilePath = szDataFilePathModified;
		Status retGetProtNameModi = (pKeyInfoModified)->m_KeyValue->GetAttributeValue(PROTOCAL,szProtocalName);	

		if(SUCCESS == retGetProtNameModi)
		{
			pMetaFileInfoModified->m_szProtocal = szProtocalName;	
			pResourceModificationInfoModified->m_pMetaFileInfo = pMetaFileInfoModified;	

			if(CConfigurationStorage::getInstance()->GetEnableMatchMetaStatus() && FAILURE == IsMetaMatchSuccessful)
			{							
				pResourceModificationInfoBase->m_szMetaDetails = szDetailsBase;
				pResourceModificationInfoBase->m_szMismatchType.append("M");
				pResourceModificationInfoModified->m_szMetaDetails = szDetailsModified;
				pResourceModificationInfoModified->m_szMismatchType.append("M");
			}

			pMismatch->m_pResourceModificationInfoBase = pResourceModificationInfoBase;
			pMismatch->m_pResourceModificationInfoModified = pResourceModificationInfoModified;
			OutputCollector.m_MismatchList.push_back(pMismatch);
			pKeyInfoBase->m_bMatched = true;
			pKeyInfoModified->m_bMatched = true;

		}
		else
		{
			CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Modified List : Case Mismatch");
			return FAILURE;
		}										
	}
	else
	{
		CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Base List : Case Mismatch");
		return FAILURE;
	}
	return SUCCESS;
}


//************************************
// Method:    ProcessMissingCondition
// FullName:  CComparator::ProcessMissingCondition
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const std::list<CKeyInfo * > & KeyInfoBase
// Parameter: const std::list<CKeyInfo * > & KeyInfoModified
// Parameter: COutputCollector & OutputCollector
//************************************
Status CComparator::ProcessMissingCondition(const std::list<CKeyInfo*>	&KeyInfoBase,
											const std::list<CKeyInfo*>	&KeyInfoModified,
													COutputCollector	&OutputCollector
	)
{
	std::list<CKeyInfo*>::const_iterator ListIteratorBase;
	std::list<CKeyInfo*>::const_iterator ListIteratorModified;

	for(ListIteratorBase = KeyInfoBase.begin();ListIteratorBase != KeyInfoBase.end();ListIteratorBase++)
	{
		if(!(*ListIteratorBase)->m_bMatched )
		{			
			CMetaFileInfo *pMetaFileInfoBase = new CMetaFileInfo();
			CMetaFileInfo *pMetaFileInfoModified = new CMetaFileInfo();
			std::string szDataFilePath;
			pMetaFileInfoBase->m_szMetaFilePath = (*ListIteratorBase)->m_MetaFilePath;
			Status retGetDataFileName = GetDataFileName((*ListIteratorBase)->m_MetaFilePath,szDataFilePath);
			if(SUCCESS == retGetDataFileName)
			{
				pMetaFileInfoBase->m_szDataFilePath = szDataFilePath;
				std::wstring szProtocalName;
				Status retProtName = (*ListIteratorBase)->m_KeyValue->GetAttributeValue(PROTOCAL,szProtocalName);	
				if(SUCCESS == retProtName)
				{
					pMetaFileInfoBase->m_szProtocal = szProtocalName;			
					if (!(*ListIteratorBase)->m_bIsInvalid)
					{
						OutputCollector.m_MissingListBase.push_back(pMetaFileInfoBase);
					}
					else
					{
						OutputCollector.m_KeyReplicationListBase.push_back(pMetaFileInfoBase);
					}					
				}
				else
				{
					CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Modified List : Case Missing Base");
					return FAILURE;
				}				
			}
			else
			{
				CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Base List : Case Missing Base");
				return FAILURE;
			}			
		}
	}

	for(ListIteratorModified = KeyInfoModified.begin();ListIteratorModified != KeyInfoModified.end();ListIteratorModified++)
	{
		if(!(*ListIteratorModified)->m_bMatched)
		{			
			CMetaFileInfo *pMetaFileInfoModified = new CMetaFileInfo();
			std::string szDataFilePath;
			pMetaFileInfoModified->m_szMetaFilePath = (*ListIteratorModified)->m_MetaFilePath;
			Status retGetDataFileName = GetDataFileName((*ListIteratorModified)->m_MetaFilePath,szDataFilePath);
			if(SUCCESS == retGetDataFileName)
			{
				pMetaFileInfoModified->m_szDataFilePath = szDataFilePath;
				std::wstring szProtocalName;
				Status retProtName =  (*ListIteratorModified)->m_KeyValue->GetAttributeValue(PROTOCAL,szProtocalName);	
				if (SUCCESS == retProtName)
				{
					pMetaFileInfoModified->m_szProtocal = szProtocalName;	
					if (!(*ListIteratorModified)->m_bIsInvalid)
					{
						OutputCollector.m_MissingListModified.push_back(pMetaFileInfoModified);	
					}
					else
					{
						OutputCollector.m_KeyReplicationListModified.push_back(pMetaFileInfoModified);
					}									
				}
				else
				{
					CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Modified List : Case Missing Modified");
					return FAILURE;
				}				
			}
			else
			{
				CLogManager::CreateLog(LOG_ERROR,"Error Extracting Protocol Name : Base List : Case Missing Modified");
				return FAILURE;
			}
		}
	}
	return SUCCESS;
}

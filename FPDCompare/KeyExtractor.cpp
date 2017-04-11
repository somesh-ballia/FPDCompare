#include "StdAfx.h"
#include "KeyExtractor.h"
#include "MetaPropertyValue.h"
#include "MetaProperty.h"
#include "MetaReader.h"
#include "ConfigurationStorage.h"
#include "Utility.h"
#include "LogManager.h"
#include "Summary.h"

CKeyExtractor::CKeyExtractor(void)
{
}


CKeyExtractor::~CKeyExtractor(void)
{
}

//************************************
// Method:    ExtractKey
// FullName:  CKeyExtractor::ExtractKey
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaFilePath
// Parameter: CKey * pKeyValue
// Parameter: UINT32 & uiHashValue
//************************************
Status CKeyExtractor::ExtractKey(const String &szMetaFilePath,
									   CKey *pKeyValue,
									   UINT32 &uiHashValue )
{	
	CMetaPropertySet *pMetaProperty = new CMetaPropertySet();
	List_Wstr KeyAttributeList;
	CConfigurationStorage::getInstance()->GetKeyAttributeList(KeyAttributeList);	
	Status retFetchMetaFileInfo = FetchMetaFileInfo(szMetaFilePath,&pMetaProperty);
	if (SUCCESS == retFetchMetaFileInfo)
	{		
		std::list<std::wstring>::const_iterator ListIterator;
		std::map<std::wstring,CMetaPropertySet*>::iterator MapIterator;
		std::list<UINT32> ListHashValues;

		for(ListIterator = KeyAttributeList.begin();ListIterator != KeyAttributeList.end();ListIterator++)
		{
			Wstring szAttribute = *ListIterator;			
			CMetaPropertyValue* pMetaPropertyValue = pMetaProperty->m_Properties[szAttribute];
			if (NULL != pMetaPropertyValue)
			{
				ListHashValues.push_back(pMetaPropertyValue->m_uHashValue);
				pKeyValue->m_Properties[szAttribute] = pMetaPropertyValue;
				pMetaProperty->m_Properties.erase(szAttribute);
			}
			else
			{				
				CLogManager::CreateLog(LOG_ERROR,"Error Extracting Attribute Value from MAP");
				return FAILURE;
			}
		}
		uiHashValue = CalculateCombinedHash(ListHashValues);	
		pKeyValue->m_HashValue = uiHashValue;
		delete pMetaProperty;		
	}
	else
	{		
		delete pMetaProperty;
		String szMessage = "Error Parsing File : ";
		szMessage.append(szMetaFilePath);
		CLogManager::CreateLog(LOG_ERROR,szMessage);
		return FAILURE;
	}
	return SUCCESS;	
}

//************************************
// Method:    FetchMetaFileInfo
// FullName:  CKeyExtractor::FetchMetaFileInfo
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const std::string szMetaFilePath
// Parameter: CMetaPropertySet * * pMetaProperty
//************************************
Status CKeyExtractor::FetchMetaFileInfo( const std::string szMetaFilePath, CMetaPropertySet **pMetaProperty )
{
	CMetaReader MetaReader;

	*pMetaProperty = new CMetaPropertySet();
	Status retMetaReader = MetaReader.ReadMetaFile(szMetaFilePath,*pMetaProperty,true);
	if(SUCCESS == retMetaReader)
	{
		return SUCCESS;		
	}
	else
	{		
		CSummary::getInstance()->m_uiAmbiguousFiles++;
		String szMessage = "Error Reading Meta File : ";
		szMessage.append(szMetaFilePath);
		CLogManager::CreateLog(LOG_ERROR,szMessage);
		return FAILURE;
	}
}


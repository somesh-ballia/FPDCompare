#include "StdAfx.h"
#include "CommonAll.h"
#include "MetaReader.h"
#include "MetaProperty.h"
#include "MetaPropertyValue.h"
#include "MetaPropertySubValue.h"
#include "MetaPropertSubValue_String.h"
#include "MetaPropertSubValue_Integer.h"
#include "MetaPropertSubValue_FileName.h"
#include "MetaPropertSubValue_DateTime.h"
#include "ConfigurationStorage.h"
#include "LogManager.h"
#include "Utility.h"

CMetaReader::CMetaReader(void)
{
}


CMetaReader::~CMetaReader(void)
{
}

//************************************
// Method:    ReadMetaFile
// FullName:  CMetaReader::ReadMetaFile
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: const String & szMetaFilePath
// Parameter: CMetaPropertySet * pMetaProperty
// Parameter: const bool bCalculateHash
//************************************
Status CMetaReader::ReadMetaFile(const String &szMetaFilePath, CMetaPropertySet *pMetaProperty,const bool bCalculateHash )
{
	if (0 == szMetaFilePath.length())
	{		
		CLogManager::CreateLog(LOG_ERROR,"Invalid Meta File Name in Read Meta File");
		return FAILURE;
	}

	std::wstring szMetaFilePathW = std::wstring(szMetaFilePath.begin(),szMetaFilePath.end());
	const WCHAR* pszMetaFilePathW = szMetaFilePathW.c_str();
	if (CConfigurationStorage::getInstance()->GetUnicodeEnableStatus())
	{
		// for UNICODE FILES
		WCHAR szBuffer[BUFFER_SIZE] = {0};
		FILE *fpMetaFile = _wfopen(pszMetaFilePathW, L"rb");

		if(NULL == fpMetaFile)
		{			
			String szMessage = "Unable to open File : ";
			szMessage.append(szMetaFilePath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;
		}
		else
		{
			// Iterate through each line till the end of file
			while(!feof(fpMetaFile) && NULL != fpMetaFile)
			{
				wmemset(szBuffer,'\0',BUFFER_SIZE);
				fgetws(szBuffer, BUFFER_SIZE, fpMetaFile);
				if (0 != wcslen(szBuffer))
				{
					Status retParseBuffer = ParseBuffer(szBuffer,pMetaProperty,bCalculateHash);
					if(FAILURE == retParseBuffer)
					{	
						// log error
						String szMessage = "Unable to parse File : ";
						szMessage.append(szMetaFilePath);
						CLogManager::CreateLog(LOG_ERROR,szMessage);
						fclose(fpMetaFile);
						return FAILURE;
					}
				}
			}
			fclose(fpMetaFile);
		}
	}
	else
	{
		// FOR ANSI FILES
		char szBuffer[BUFFER_SIZE] = {0};
		WCHAR szBufferW[BUFFER_SIZE] = {0};
		FILE *fpMetaFile = fopen(szMetaFilePath.c_str(), "r");

		if(NULL == fpMetaFile)
		{
			String szMessage = "Unable to open File : ";
			szMessage.append(szMetaFilePath);
			CLogManager::CreateLog(LOG_ERROR,szMessage);
			return FAILURE;			
		}
		else
		{
			// Iterate through each line till the end of file
			while(!feof(fpMetaFile) && NULL != fpMetaFile)
			{
				wmemset(szBufferW,'\0',BUFFER_SIZE);
				memset(szBuffer,'\0',BUFFER_SIZE);

				fgets(szBuffer, BUFFER_SIZE, fpMetaFile);
				mbstowcs(szBufferW,szBuffer,BUFFER_SIZE);
				if (0 != strlen(szBuffer))
				{
					Status retParseBuffer = ParseBuffer(szBufferW,pMetaProperty,bCalculateHash);
					if(FAILURE == retParseBuffer)
					{	
						// log error
						String szMessage = "Unable to Parse File : ";
						szMessage.append(szMetaFilePath);
						CLogManager::CreateLog(LOG_ERROR,szMessage);
						fclose(fpMetaFile);
						return FAILURE;
					}
				}
			}
			fclose(fpMetaFile);
		}
	}
	return SUCCESS;
}

//************************************
// Method:    ParseBuffer
// FullName:  CMetaReader::ParseBuffer
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const Wstring & szBuffer
// Parameter: CMetaPropertySet * pMetaProperty
// Parameter: const bool bCalculateHash
//************************************
Status CMetaReader::ParseBuffer(const Wstring &szBuffer,CMetaPropertySet *pMetaProperty,const bool bCalculateHash)
{
	if(0 == szBuffer.length())
	{
		return FAILURE;
	}

	Wstring szAttributeName;
	Wstring szAttributeValue;
	List_Wstr ListValue;
	List_Wstr IgnoreList;
	CConfigurationStorage::getInstance()->GetIgnoreList(IgnoreList);

	unsigned short sOffset = 0;

	Datatype dtDatatype = GetDatatype(szBuffer,sOffset);
	if (DATATYPE_UNKNOWN == dtDatatype)
	{		
		return FAILURE;
	}

	Multiplicity mMultiplicity = GetMultiplicity(szBuffer,sOffset);	

	if (MULTIPLICITY_UNKNOWN == mMultiplicity)
	{
		return FAILURE;
	}

	Status retGetAttribName = GetAttributeName(szBuffer,sOffset,szAttributeName);
	if (SUCCESS == retGetAttribName)
	{
		Status retIgrnoreAttrib = IgnoreAttribute(szAttributeName,IgnoreList);
		if(FAILURE == retIgrnoreAttrib)
		{
			Status retGetAttribValue = GetAttributeValue(szBuffer,sOffset,szAttributeValue);
			if (SUCCESS == retGetAttribValue)
			{
				if (MULTIPLICITY_MULTIPLE == mMultiplicity)
				{			
					Status retGetMultipleValue = GetMultipleValue(szAttributeValue,ListValue);
					if (FAILURE == retGetMultipleValue)
					{						
						CLogManager::CreateLog(LOG_ERROR,"Error Parsing Multiple values");
						return FAILURE;
					}
				}
				else
				{
					ListValue.push_back(szAttributeValue);
				}

				Status retFillMetaPropValue = FillMetaPropertyValue(dtDatatype,mMultiplicity,szAttributeName,ListValue,pMetaProperty,bCalculateHash);
				if (SUCCESS == retFillMetaPropValue)
				{
					return SUCCESS;
				}
				else
				{						
					CLogManager::CreateLog(LOG_ERROR,"Error Filling values in the required structure ParseBuffer");
					return FAILURE;
				}
			}
			else
			{				
				String szMessage = "Error Fetching attribute value ParseBuffer : ";				
				CLogManager::CreateLog(LOG_ERROR,szMessage);
				return FAILURE;
			}				
		}	
	}
	else
	{
		String szMessage = "Error Extracting attribute Name : ";		
		CLogManager::CreateLog(LOG_ERROR,szMessage);
		return FAILURE;
	}

	return SUCCESS;
}

//************************************
// Method:    GetNewOffset
// FullName:  CMetaReader::GetNewOffset
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: const Wstring & szBuffer
// Parameter: WCHAR wchDelimeter
// Parameter: unsigned short & sOffset
//************************************
void CMetaReader::GetNewOffset(const Wstring &szBuffer,WCHAR wchDelimeter,unsigned short &sOffset)
{
	sOffset++;
	unsigned short sEndOffset = szBuffer.find(wchDelimeter,sOffset);
	sOffset = sEndOffset;
}

Datatype CMetaReader::GetDatatype(const Wstring &szBuffer,unsigned short &sEndOffset )
{
	WCHAR wchSpace = L' ';
	unsigned short sStartOffset = 0;
	if(L'S' == szBuffer[1] || L'D' == szBuffer[1] || L'F' == szBuffer[1] || L'N' == szBuffer[1])
	{
		sStartOffset = 1;
	}
	sEndOffset = szBuffer.find(wchSpace,sStartOffset);
	std::wstring szDataType = szBuffer.substr(sStartOffset,sEndOffset-sStartOffset);

	if(!szDataType.compare(L"D"))
	{
		return DATATYPE_DATETIME;
	}

	if(!szDataType.compare(L"S"))
	{
		return DATATYPE_STRING;
	}

	if(!szDataType.compare(L"F"))
	{
		return DATATYPE_FILENAME;
	}

	if(!szDataType.compare(L"N"))
	{
		return DATATYPE_NUMBER;
	}
	return DATATYPE_UNKNOWN;	

}

//************************************
// Method:    GetMultiplicity
// FullName:  CMetaReader::GetMultiplicity
// Access:    private 
// Returns:   Multiplicity
// Qualifier:
// Parameter: const Wstring & szBuffer
// Parameter: unsigned short & sOffset
//************************************
Multiplicity CMetaReader::GetMultiplicity(const Wstring &szBuffer,unsigned short &sOffset)
{
	WCHAR wchSpace = L' ';
	sOffset++;
	unsigned short sEndOffset = szBuffer.find(wchSpace,sOffset);
	std::wstring szMultiplicity = szBuffer.substr(sOffset,sEndOffset-sOffset);
	sOffset = sEndOffset;

	if(!szMultiplicity.compare(L"S"))
	{
		return MULTIPLICITY_SINGLE;
	}

	if(!szMultiplicity.compare(L"M"))
	{
		return MULTIPLICITY_MULTIPLE;
	}

	return MULTIPLICITY_UNKNOWN;
}

//************************************
// Method:    GetAttributeName
// FullName:  CMetaReader::GetAttributeName
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const Wstring & szBuffer
// Parameter: unsigned short & sOffset
// Parameter: Wstring & szAttributeName
//************************************
Status CMetaReader::GetAttributeName(const Wstring &szBuffer,unsigned short &sOffset,Wstring &szAttributeName)
{
	if(0 == szBuffer.length())
	{		
		CLogManager::CreateLog(LOG_ERROR,"Invalid Buffer Length");
		return FAILURE;
	}

	WCHAR wchSpace = L' ';
	GetNewOffset(szBuffer,wchSpace,sOffset);	
	sOffset++;
	unsigned short sEndOffset = szBuffer.find(wchSpace,sOffset);
	szAttributeName = szBuffer.substr(sOffset,sEndOffset-sOffset);
	sOffset = sEndOffset;	
	if (0 == szAttributeName.length())
	{
		CLogManager::CreateLog(LOG_ERROR,"Invalid Attribute Name in GetAttributeName");
		return FAILURE;
	}
	return SUCCESS;
}

//************************************
// Method:    GetAttributeValue
// FullName:  CMetaReader::GetAttributeValue
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const Wstring & szBuffer
// Parameter: unsigned short & sOffset
// Parameter: Wstring & szAttributeValue
//************************************
Status CMetaReader::GetAttributeValue(const Wstring &szBuffer,unsigned short &sOffset,Wstring &szAttributeValue)
{
	if(0 == szBuffer.length())
	{
		CLogManager::CreateLog(LOG_ERROR,"Invalid Buffer Length");
		return FAILURE;
	}

	unsigned int uiLength = szBuffer.length();
	WCHAR wchSpace = L' ';
	sOffset++;	
	szAttributeValue = szBuffer.substr(sOffset,uiLength-sOffset);
	sOffset = uiLength;	
	return SUCCESS;
}


//************************************
// Method:    GetMultipleValue
// FullName:  CMetaReader::GetMultipleValue
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const Wstring & szAttributeValue
// Parameter: List_Wstr & ListMultipleValues
//************************************
Status CMetaReader::GetMultipleValue(const Wstring &szAttributeValue,List_Wstr &ListMultipleValues)
{
	if(0 == szAttributeValue.length())
	{
		CLogManager::CreateLog(LOG_ERROR,"Invalid Buffer Length");
		return FAILURE;
	}
	Wstring szDelimeters = L"{},";
	ListMultipleValues = Tokenize(szAttributeValue,szDelimeters);	
	ListMultipleValues.sort(CompareNocase);
	return SUCCESS;
}

//************************************
// Method:    IgnoreAttribute
// FullName:  CMetaReader::IgnoreAttribute
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const Wstring & szAttributeName
// Parameter: const List_Wstr & IgnoreList
//************************************
Status CMetaReader::IgnoreAttribute(const Wstring &szAttributeName,const List_Wstr &IgnoreList)
{
	if(0 == szAttributeName.length())
	{
		CLogManager::CreateLog(LOG_ERROR,"Invalid Buffer Length");
		return SUCCESS;
	}

	if (0 == IgnoreList.size())
	{
		return FAILURE;
	}

	for(std::list<std::wstring>::const_iterator Iterator = IgnoreList.begin();Iterator != IgnoreList.end();Iterator++)
	{
		if(!szAttributeName.compare(*Iterator))
		{
			return SUCCESS;
		}
	}
	return FAILURE;
}

//************************************
// Method:    FillMetaPropertyValue
// FullName:  CMetaReader::FillMetaPropertyValue
// Access:    private 
// Returns:   Status
// Qualifier:
// Parameter: const Datatype & dtDatatype
// Parameter: const Multiplicity & mMultiplicity
// Parameter: const Wstring & szAttributeName
// Parameter: const List_Wstr & ListValue
// Parameter: CMetaPropertySet * pMetaProperty
// Parameter: const bool bCalculateHash
//************************************
Status CMetaReader::FillMetaPropertyValue(const Datatype &dtDatatype, 
										  const Multiplicity &mMultiplicity, 
										  const Wstring &szAttributeName, 
										  const List_Wstr &ListValue, 
												CMetaPropertySet *pMetaProperty,
												const bool bCalculateHash )
{
	std::list<std::wstring>::const_iterator Iterator;
	CMetaPropertyValue *pMetaPropertyValue = new CMetaPropertyValue();

	if (DATATYPE_UNKNOWN == dtDatatype || MULTIPLICITY_UNKNOWN == mMultiplicity || 0 == szAttributeName.length())
	{
		CLogManager::CreateLog(LOG_ERROR,"Error in FillMetaPropertyValue: Parsing failure values to be filled");
		return FAILURE;
	}

	switch(mMultiplicity)
	{
	case MULTIPLICITY_SINGLE:
		pMetaPropertyValue->m_Multiplicity = false;
		break;
	case MULTIPLICITY_MULTIPLE:
		pMetaPropertyValue->m_Multiplicity = true;
		break;	
	}

	switch(dtDatatype)
	{

	case DATATYPE_DATETIME:
		pMetaPropertyValue->m_Datatype = DATATYPE_DATETIME;
		for(Iterator = ListValue.begin();Iterator != ListValue.end(); Iterator++)
		{
			CMetaPropertSubValue_DateTime *pMPSV_DateTime = new CMetaPropertSubValue_DateTime();
			std::wstring value = *Iterator;
			pMPSV_DateTime->m_Value = _wtoi(value.c_str());
			pMetaPropertyValue->m_ListSubValues.push_back(pMPSV_DateTime);
			if (bCalculateHash)
				pMetaPropertyValue->m_uHashValue = CalculateHash(pMPSV_DateTime->m_Value);
			else
				pMetaPropertyValue->m_uHashValue = 0;
		}
		break;

	case DATATYPE_STRING:
		pMetaPropertyValue->m_Datatype = DATATYPE_STRING;
		for(Iterator = ListValue.begin();Iterator != ListValue.end(); Iterator++)
		{
			CMetaPropertSubValue_String *pMPSV_String = new CMetaPropertSubValue_String();
			std::wstring value = *Iterator;
			pMPSV_String->m_Value = value;
			pMetaPropertyValue->m_ListSubValues.push_back(pMPSV_String);
			if (bCalculateHash)
				pMetaPropertyValue->m_uHashValue = CalculateHash(pMPSV_String->m_Value);
			else
				pMetaPropertyValue->m_uHashValue = 0;
		}
		break;		

	case DATATYPE_FILENAME:
		pMetaPropertyValue->m_Datatype = DATATYPE_FILENAME;
		for(Iterator = ListValue.begin();Iterator != ListValue.end(); Iterator++)
		{
			CMetaPropertSubValue_FileName *pMPSV_FileName = new CMetaPropertSubValue_FileName();
			std::wstring value = *Iterator;
			pMPSV_FileName->m_Value = value;
			pMetaPropertyValue->m_ListSubValues.push_back(pMPSV_FileName);
			if (bCalculateHash)
				pMetaPropertyValue->m_uHashValue = CalculateHash(pMPSV_FileName->m_Value);
			else
				pMetaPropertyValue->m_uHashValue = 0;
		}
		break;

	case DATATYPE_NUMBER:
		pMetaPropertyValue->m_Datatype = DATATYPE_NUMBER;
		for(Iterator = ListValue.begin();Iterator != ListValue.end(); Iterator++)
		{
			CMetaPropertSubValue_Integer *pMPSV_Integer = new CMetaPropertSubValue_Integer();
			std::wstring value = *Iterator;
			pMPSV_Integer->m_Value = _wtoi(value.c_str());
			pMetaPropertyValue->m_ListSubValues.push_back(pMPSV_Integer);
			if (bCalculateHash)
				pMetaPropertyValue->m_uHashValue = CalculateHash(pMPSV_Integer->m_Value);
			else
				pMetaPropertyValue->m_uHashValue = 0;
		}
		break;	
	}	

	pMetaProperty->m_Properties.insert(std::pair<std::wstring,CMetaPropertyValue*>(szAttributeName,pMetaPropertyValue));
	return SUCCESS;
}
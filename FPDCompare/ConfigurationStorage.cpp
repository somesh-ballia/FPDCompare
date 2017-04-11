#include "StdAfx.h"
#include "ConfigurationStorage.h"


CConfigurationStorage::CConfigurationStorage(void)
{
	m_bEnableLogging = false;
	m_bIsUnicode = false;
	m_bEnableMetaMatch = false;
	m_bDumpFolderHierarchy = false;
}


CConfigurationStorage::~CConfigurationStorage(void)
{
}


CConfigurationStorage * CConfigurationStorage::m_pInstance = NULL;

CConfigurationStorage* CConfigurationStorage::getInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CConfigurationStorage();
	}
	return m_pInstance;
}


//************************************
// Method:    GetLoggingStatus
// FullName:  CConfigurationStorage::GetLoggingStatus
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool CConfigurationStorage::GetLoggingStatus()
{
	return m_bEnableLogging; 
}

//************************************
// Method:    SetLoggingStatus
// FullName:  CConfigurationStorage::SetLoggingStatus
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: bool bLoggingStatus
//************************************
void CConfigurationStorage::SetLoggingStatus(bool bLoggingStatus)
{
	m_bEnableLogging = bLoggingStatus;
}

//************************************
// Method:    GetUnicodeEnableStatus
// FullName:  CConfigurationStorage::GetUnicodeEnableStatus
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool CConfigurationStorage::GetUnicodeEnableStatus()
{
	return m_bIsUnicode;
}

//************************************
// Method:    SetUnicodeEnableStatus
// FullName:  CConfigurationStorage::SetUnicodeEnableStatus
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: bool bIsUnicode
//************************************
void CConfigurationStorage::SetUnicodeEnableStatus(bool bIsUnicode)
{
	m_bIsUnicode = bIsUnicode;
}

//************************************
// Method:    GetEnableMatchMetaStatus
// FullName:  CConfigurationStorage::GetEnableMatchMetaStatus
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool CConfigurationStorage::GetEnableMatchMetaStatus()
{
	return m_bEnableMetaMatch;
}

//************************************
// Method:    SetEnableMatchMeta
// FullName:  CConfigurationStorage::SetEnableMatchMeta
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: bool bEnableMetaMatch
//************************************
void CConfigurationStorage::SetEnableMatchMeta(bool bEnableMetaMatch)
{
	m_bEnableMetaMatch = bEnableMetaMatch;
}

//************************************
// Method:    GetEnableDumpFolderHierarchy
// FullName:  CConfigurationStorage::GetEnableDumpFolderHierarchy
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool CConfigurationStorage::GetEnableDumpFolderHierarchy()
{
	return m_bDumpFolderHierarchy;
}

//************************************
// Method:    SetEnableDumpFolderHierarchy
// FullName:  CConfigurationStorage::SetEnableDumpFolderHierarchy
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: bool bEnableDumpFolderHierarchy
//************************************
void CConfigurationStorage::SetEnableDumpFolderHierarchy(bool bEnableDumpFolderHierarchy)
{
	m_bDumpFolderHierarchy = bEnableDumpFolderHierarchy;
}

//************************************
// Method:    GetBasePath
// FullName:  CConfigurationStorage::GetBasePath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szBasePath
//************************************
void CConfigurationStorage::GetBasePath(String &szBasePath)
{
	szBasePath = m_szBasePath;
}

//************************************
// Method:    GetModifiedPath
// FullName:  CConfigurationStorage::GetModifiedPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szModifiedPath
//************************************
void CConfigurationStorage::GetModifiedPath(String &szModifiedPath)
{
	szModifiedPath = m_szModifiedPath;
}

//************************************
// Method:    GetOutputPath
// FullName:  CConfigurationStorage::GetOutputPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szOutputPath
//************************************
void CConfigurationStorage::GetOutputPath(String &szOutputPath)
{
	szOutputPath = m_szOutputFilePath;
}

//************************************
// Method:    GetLogFilePath
// FullName:  CConfigurationStorage::GetLogFilePath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szLogFilePath
//************************************
void CConfigurationStorage::GetLogFilePath(String &szLogFilePath)
{
	szLogFilePath = m_szLogFilePath;
}

//************************************
// Method:    GetDumpFolderPath
// FullName:  CConfigurationStorage::GetDumpFolderPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szDumpFolderPath
//************************************
void CConfigurationStorage::GetDumpFolderPath(String &szDumpFolderPath)
{
	szDumpFolderPath = m_szDumpFolderPath;
}

//************************************
// Method:    GetIgnoreList
// FullName:  CConfigurationStorage::GetIgnoreList
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: List_Wstr & IgnoreList
//************************************
void CConfigurationStorage::GetIgnoreList(List_Wstr &IgnoreList)
{
	IgnoreList = m_IgnoreList;
}

//************************************
// Method:    GetKeyAttributeList
// FullName:  CConfigurationStorage::GetKeyAttributeList
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: List_Wstr & KeyAttributeList
//************************************
void CConfigurationStorage::GetKeyAttributeList(List_Wstr &KeyAttributeList)
{
	KeyAttributeList = m_KeyAttributeList;
}

//************************************
// Method:    SetModifiedPath
// FullName:  CConfigurationStorage::SetModifiedPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szModifiedPath
//************************************
void CConfigurationStorage::SetModifiedPath(String &szModifiedPath)
{
	m_szModifiedPath = szModifiedPath;
}

//************************************
// Method:    SetBasePath
// FullName:  CConfigurationStorage::SetBasePath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szBasePath
//************************************
void CConfigurationStorage::SetBasePath(String &szBasePath)
{
	m_szBasePath = szBasePath;
}

//************************************
// Method:    SetOutputPath
// FullName:  CConfigurationStorage::SetOutputPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szOutputPath
//************************************
void CConfigurationStorage::SetOutputPath(String &szOutputPath)
{
	m_szOutputFilePath = szOutputPath;
}

//************************************
// Method:    SetLogFilePath
// FullName:  CConfigurationStorage::SetLogFilePath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szLogFilePath
//************************************
void CConfigurationStorage::SetLogFilePath(String &szLogFilePath)
{
	m_szLogFilePath = szLogFilePath;
}

//************************************
// Method:    SetDumpFolderPath
// FullName:  CConfigurationStorage::SetDumpFolderPath
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: String & szDumpFolderPath
//************************************
void CConfigurationStorage::SetDumpFolderPath(String &szDumpFolderPath)
{
	m_szDumpFolderPath = szDumpFolderPath;
}

//************************************
// Method:    SetKeyAttributeList
// FullName:  CConfigurationStorage::SetKeyAttributeList
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: List_Wstr & KeyAttributeList
//************************************
void CConfigurationStorage::SetKeyAttributeList(List_Wstr &KeyAttributeList)
{
	m_KeyAttributeList = KeyAttributeList;
}

//************************************
// Method:    SetIgnoreList
// FullName:  CConfigurationStorage::SetIgnoreList
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: List_Wstr & IgnoreList
//************************************
void CConfigurationStorage::SetIgnoreList(List_Wstr &IgnoreList)
{
	m_IgnoreList = IgnoreList;
}
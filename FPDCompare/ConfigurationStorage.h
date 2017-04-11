#pragma once

 /***************************************************************************
 *																			*
 *																			*
 * Copyright 2001-02 by Cleartrail Technologies, Inc. All rights reserved.	*
 *																			*
 * Warning:  This program is the unpublished, proprietary property of		*
 * 'Cleartrail Technologies, Inc.' and is to be maintained in strict		*
 * confidence. Unauthorized reproduction, distribution or disclosure of		*
 * this program, or any program derived from it is prohibited by State		*
 * and Federal law.															*
 ****************************************************************************/


class CConfigurationStorage
{
public:
	CConfigurationStorage(void);
	~CConfigurationStorage(void);
	
	static CConfigurationStorage* getInstance(void);

	//************************************
	// Method:    GetBasePath
	// FullName:  CConfigurationStorage::GetBasePath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szBasePath
	//************************************
	void GetBasePath(String &szBasePath);
	//************************************
	// Method:    SetBasePath
	// FullName:  CConfigurationStorage::SetBasePath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szBasePath
	//************************************
	void SetBasePath(String &szBasePath);

	//************************************
	// Method:    GetModifiedPath
	// FullName:  CConfigurationStorage::GetModifiedPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szModifiedPath
	//************************************
	void GetModifiedPath(String &szModifiedPath);
	//************************************
	// Method:    SetModifiedPath
	// FullName:  CConfigurationStorage::SetModifiedPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szModifiedPath
	//************************************
	void SetModifiedPath(String &szModifiedPath);

	//************************************
	// Method:    GetOutputPath
	// FullName:  CConfigurationStorage::GetOutputPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szOutputPath
	//************************************
	void GetOutputPath(String &szOutputPath);
	//************************************
	// Method:    SetOutputPath
	// FullName:  CConfigurationStorage::SetOutputPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szOutputPath
	//************************************
	void SetOutputPath(String &szOutputPath);

	//************************************
	// Method:    GetLogFilePath
	// FullName:  CConfigurationStorage::GetLogFilePath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szLogFilePath
	//************************************
	void GetLogFilePath(String &szLogFilePath);
	//************************************
	// Method:    SetLogFilePath
	// FullName:  CConfigurationStorage::SetLogFilePath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szLogFilePath
	//************************************
	void SetLogFilePath(String &szLogFilePath);

	//************************************
	// Method:    GetDumpFolderPath
	// FullName:  CConfigurationStorage::GetDumpFolderPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szDumpFolderPath
	//************************************
	void GetDumpFolderPath(String &szDumpFolderPath);
	//************************************
	// Method:    SetDumpFolderPath
	// FullName:  CConfigurationStorage::SetDumpFolderPath
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: String & szDumpFolderPath
	//************************************
	void SetDumpFolderPath(String &szDumpFolderPath);

	//************************************
	// Method:    GetKeyAttributeList
	// FullName:  CConfigurationStorage::GetKeyAttributeList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: List_Wstr & KeyAttributeList
	//************************************
	void GetKeyAttributeList(List_Wstr &KeyAttributeList);
	//************************************
	// Method:    SetKeyAttributeList
	// FullName:  CConfigurationStorage::SetKeyAttributeList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: List_Wstr & KeyAttributeList
	//************************************
	void SetKeyAttributeList(List_Wstr &KeyAttributeList);

	//************************************
	// Method:    GetIgnoreList
	// FullName:  CConfigurationStorage::GetIgnoreList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: List_Wstr & IgnoreList
	//************************************
	void GetIgnoreList(List_Wstr &IgnoreList);
	//************************************
	// Method:    SetIgnoreList
	// FullName:  CConfigurationStorage::SetIgnoreList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: List_Wstr & IgnoreList
	//************************************
	void SetIgnoreList(List_Wstr &IgnoreList);

	//************************************
	// Method:    GetLoggingStatus
	// FullName:  CConfigurationStorage::GetLoggingStatus
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	bool GetLoggingStatus();
	//************************************
	// Method:    SetLoggingStatus
	// FullName:  CConfigurationStorage::SetLoggingStatus
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: bool bLogging
	//************************************
	void SetLoggingStatus(bool bLogging);

	//************************************
	// Method:    GetUnicodeEnableStatus
	// FullName:  CConfigurationStorage::GetUnicodeEnableStatus
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	bool GetUnicodeEnableStatus();
	//************************************
	// Method:    SetUnicodeEnableStatus
	// FullName:  CConfigurationStorage::SetUnicodeEnableStatus
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: bool bIsUnicodeEnabled
	//************************************
	void SetUnicodeEnableStatus(bool bIsUnicodeEnabled);

	//************************************
	// Method:    GetEnableMatchMetaStatus
	// FullName:  CConfigurationStorage::GetEnableMatchMetaStatus
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	bool GetEnableMatchMetaStatus();
	//************************************
	// Method:    SetEnableMatchMeta
	// FullName:  CConfigurationStorage::SetEnableMatchMeta
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: bool bEnableMatchMeta
	//************************************
	void SetEnableMatchMeta(bool bEnableMatchMeta);

	//************************************
	// Method:    GetEnableDumpFolderHierarchy
	// FullName:  CConfigurationStorage::GetEnableDumpFolderHierarchy
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	bool GetEnableDumpFolderHierarchy();
	//************************************
	// Method:    SetEnableDumpFolderHierarchy
	// FullName:  CConfigurationStorage::SetEnableDumpFolderHierarchy
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: bool bDumpFolderHierarchy
	//************************************
	void SetEnableDumpFolderHierarchy(bool bDumpFolderHierarchy);

private:
	static CConfigurationStorage *m_pInstance;
	String m_szBasePath;
	String m_szModifiedPath;
	String m_szOutputFilePath;
	String m_szLogFilePath;
	String m_szDumpFolderPath;
	List_Wstr m_KeyAttributeList;
	List_Wstr m_IgnoreList;

	bool m_bEnableLogging;
	bool m_bIsUnicode;
	bool m_bEnableMetaMatch;
	bool m_bDumpFolderHierarchy;

};


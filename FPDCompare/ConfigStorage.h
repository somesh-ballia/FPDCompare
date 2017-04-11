#pragma once
class CConfigStorage
{
public:
	CConfigStorage(void);
	~CConfigStorage(void);
	std::string m_szBasePath;
	std::string m_szModifiedPath;
	std::string m_szOutputFilePath;
	std::string m_szLogFilePath;
	std::string m_szDumpFolderPath;
	std::list<std::wstring> m_KeyAttributeList;
	std::list<std::wstring> m_IgnoreList;
	int m_iIsUnicode;
	int m_iEnableMetaMatch;
	int m_iDumpFolderHierarchy;
};


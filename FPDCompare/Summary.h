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

class CSummary
{
public:
	CSummary(void);
	~CSummary(void);

	static CSummary* getInstance(void);

	std::string m_szKeyList;
	std::string m_szIgnoreList;
	std::string m_szStartTime;
	std::string m_szEndTime;

	unsigned int m_uiIsUnicode;
	unsigned int m_uiIsMetaComparisionEnabled;

	unsigned int m_uiTotalFiles;

	unsigned int m_uiTotalFilesBase;
	unsigned int m_uiValidFilesBase;
	unsigned int m_uiInvalidFilesBase;	

	unsigned int m_uiTotalFilesModified;
	unsigned int m_uiValidFilesModified;
	unsigned int m_uiInvalidFilesModified;	

	unsigned int m_uiMatchFiles;
	unsigned int m_uiMismatchFiles;
	unsigned int m_uiMissingFilesBase;
	unsigned int m_uiMissingFilesModified;

	unsigned int m_uiKeyReplicationBase;
	unsigned int m_uiKeyReplicationModified;
	unsigned int m_uiDumpFolderHierarchy;

	unsigned int m_uiAmbiguousFiles;

private:
	static CSummary *m_pSummary;
};


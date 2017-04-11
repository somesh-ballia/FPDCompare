#include "StdAfx.h"
#include "Summary.h"

CSummary::CSummary(void)
{
	  m_uiIsUnicode = 0;
	  m_uiIsMetaComparisionEnabled = 0;
	  m_uiTotalFiles = 0;
	  m_uiTotalFilesBase = 0;
	  m_uiValidFilesBase = 0;
	  m_uiInvalidFilesBase = 0;	 
	  m_uiTotalFilesModified = 0;
	  m_uiValidFilesModified = 0;
	  m_uiInvalidFilesModified = 0;	 
	  m_uiMatchFiles = 0;
	  m_uiMismatchFiles = 0;
	  m_uiMissingFilesBase = 0;
	  m_uiMissingFilesModified = 0;
	  m_uiKeyReplicationBase = 0;
	  m_uiKeyReplicationModified = 0;
	  m_uiDumpFolderHierarchy = 0;
	  m_uiAmbiguousFiles = 0;
}

CSummary::~CSummary(void)
{

}

CSummary* CSummary::m_pSummary = NULL;

//************************************
// Method:    getInstance
// FullName:  CSummary::getInstance
// Access:    public static 
// Returns:   CSummary*
// Qualifier:
//************************************
CSummary* CSummary::getInstance()
{
	if (NULL == m_pSummary)
	{
		m_pSummary = new CSummary();
	}

	return m_pSummary;
}

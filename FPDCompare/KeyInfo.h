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

class CKeyInfo
{
public:
	CKeyInfo(void);
	~CKeyInfo(void);

	CKey	*m_KeyValue;
	String	 m_MetaFilePath;
	UINT32	 m_HashValue;	
	bool	m_bMatched;
	bool	m_bIsInvalid;

	//************************************
	// Method:    Compare
	// FullName:  CKeyInfo::Compare
	// Access:    public 
	// Returns:   Status
	// Qualifier:
	// Parameter: CKeyInfo * pKeyInfo
	// Parameter: bool & out_return
	//************************************
	Status Compare(CKeyInfo *pKeyInfo,bool &out_return);
};


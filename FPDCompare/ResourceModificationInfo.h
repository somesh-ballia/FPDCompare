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

#include "MetaFileInfo.h"
#include "DataFileInfo.h"
class CResourceModificationInfo
{
public:
	CResourceModificationInfo(void);
	~CResourceModificationInfo(void);

	CMetaFileInfo	*m_pMetaFileInfo;
	CDataFileInfo	*m_pDataFileInfo;
	String			m_szMismatchType;
	Wstring			m_szMetaDetails;
};


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
class CMatchResource
{
public:
	CMatchResource(void);
	~CMatchResource(void);
	CMetaFileInfo	*m_pBaseFileInfo;
	CMetaFileInfo	*m_pModifiedFileInfo;
};


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

#include "ResourceModificationInfo.h"

class CMismatchResource
{
public:
	CMismatchResource(void);
	~CMismatchResource(void);
	CResourceModificationInfo *m_pResourceModificationInfoBase;
	CResourceModificationInfo *m_pResourceModificationInfoModified;
};


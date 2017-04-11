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

class CMatchResource;
class CMismatchResource;
class CMetaFileInfo;
class CCopyFileStorage;

class COutputCollector
{
public:
	COutputCollector(void);
	~COutputCollector(void);

	std::list<CMatchResource*>		m_MatchList;
	std::list<CMismatchResource*>	m_MismatchList;
	std::list<CMetaFileInfo*>		m_MissingListBase;
	std::list<CMetaFileInfo*>		m_MissingListModified;
	std::list<CMetaFileInfo*>		m_KeyReplicationListBase;
	std::list<CMetaFileInfo*>		m_KeyReplicationListModified;
	std::list<CCopyFileStorage*>	m_FileCopyList;
};


#include "StdAfx.h"
#include "ResourceModificationInfo.h"


CResourceModificationInfo::CResourceModificationInfo(void)
{
	m_pMetaFileInfo = NULL;
	m_pDataFileInfo = NULL;

}


CResourceModificationInfo::~CResourceModificationInfo(void)
{
	delete m_pDataFileInfo;
	delete m_pMetaFileInfo;
}

#include "StdAfx.h"
#include "MatchResource.h"

CMatchResource::CMatchResource(void)
{	
	m_pBaseFileInfo = NULL;
	m_pModifiedFileInfo = NULL;
}


CMatchResource::~CMatchResource(void)
{	
	delete m_pBaseFileInfo;
	delete m_pModifiedFileInfo;
}

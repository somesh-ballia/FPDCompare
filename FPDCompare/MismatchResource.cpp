#include "StdAfx.h"
#include "MismatchResource.h"

CMismatchResource::CMismatchResource(void)
{
	m_pResourceModificationInfoBase = NULL;
	m_pResourceModificationInfoModified = NULL;
}


CMismatchResource::~CMismatchResource(void)
{
	delete m_pResourceModificationInfoBase;
	delete m_pResourceModificationInfoModified;
}

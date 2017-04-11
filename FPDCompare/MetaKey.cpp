#include "StdAfx.h"
#include "MetaKey.h"


CMetaKey::CMetaKey(void)
{
	m_Matched = false;
	m_IsInvalid = false;
	m_usRepeatCounter = 0;
}


CMetaKey::~CMetaKey(void)
{
  //RGCR cleanup missing...
}

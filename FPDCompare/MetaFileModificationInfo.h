#pragma once

////////////////////////////////////////////////////////////////////////////////
//                                                                           
//           MAVEN Platform - Common Macro and Constant Definitions           
//
// Copyright (c) 20012, Clear Trail. All rights reserved.
//
// This software is CONFIDENTIAL and PROPRIETARY information of 
// Clear Trail,. and shall not be disclosed without 
// the express written permission of Clear Trail,.
//
//
// HISTORY:
//   Dec 11, 2012 – Created - Somesh Pathak
//
//
////////////////////////////////////////////////////////////////////////////////

#include "MetaFileInfo.h"

class CMetaFileModificationInfo
{
  //RGCR Class should be like Resource Modificaiton details.
public:
#pragma region Public Member Variables

  //RGCR Memeber ordering not as per coding standard.
	CMetaFileInfo	*m_pMetaFileInfo;
	std::string		m_szMissmatchType;
	unsigned long	m_ulFileSize;
	unsigned long	m_ulCRCValue;
	std::wstring	m_szMetaDetails;
#pragma endregion Public Member Variables
};


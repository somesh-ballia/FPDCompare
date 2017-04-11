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

class CMatchFiles
{
  //RGCR need to discuss when to have pointers as members.
public:
#pragma region Public Member Variables
	CMetaFileInfo		*m_pBaseFileInfo;
	CMetaFileInfo		*m_pModifiedFileInfo;
#pragma endregion Public Member Variables
};


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


#include "MetaFileModificationInfo.h"

class CMisMatchFiles
{
public:
#pragma region Public Member Variables
	CMetaFileModificationInfo		*m_pBaseFileModificationInfo;
	CMetaFileModificationInfo		*m_pModifiedFileModificationInfo;
#pragma endregion Public Member Variables
};


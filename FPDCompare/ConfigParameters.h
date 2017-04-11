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

class CConfigParameters
{
public:
	CConfigParameters(void);
	~CConfigParameters(void);	
#pragma region Public Method
	bool IsUnicodeFile()
	{
		return m_IsUnicode;
	}
#pragma endregion Public Method
private:
#pragma region Private Member Variable
	bool m_IsUnicode;
#pragma endregion Private Member Variable
};

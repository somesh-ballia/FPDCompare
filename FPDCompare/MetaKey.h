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
//   Dec 03, 2012 – Created - Somesh Pathak
//
//
////////////////////////////////////////////////////////////////////////////////

class CMetaKey //RGCR name of class seems invalid.
{
public:
	CMetaKey(void);
	~CMetaKey(void);

  //RGCR coding convention: member variables are in decreasing order w.r.t. size.
  //          1) Pointers.
  //          2) User defined data types.
  //          3) 8 bytes types.
  //          4) 4 bytes types. etc.

	CKey *m_KeyValue;
	std::string m_MetaFilePath;
	unsigned short m_usRepeatCounter;
	bool m_Matched;	
	bool m_IsInvalid;
	

};


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

#include "OutputCollector.h"
#include "MatchFiles.h"
#include "MetaFileInfo.h"
#include "MetaFileModificationInfo.h"
#include <iostream>
#include <windows.h>
#include "libxl.h" //RGCR why do you want to expose caller of this class that we are exporting output in excel file and using libxl for that.
//RGCR could have worked with forward declartions.

using namespace libxl;

class COutputFileGenerator
{
public:
	COutputFileGenerator(void);
	~COutputFileGenerator(void);
#pragma region Public Methods
	Status GenerateFile			(
		std::string szFilePath,
		const COutputCollector OutputCollector,
		CSummary Summary,
		std::list<std::string> InvalidPathListBase,
		std::list<std::string> InvalidPathListModified
		);

#pragma endregion Public Methods

private:
	Status MatchFile			(
		Book *&book,
		COutputCollector OutputCollector
		);

	Status MissingFile			(
		Book *&book,
		COutputCollector OutputCollector
		);

	Status MismatchFile			(
		Book *&book,
		COutputCollector OutputCollector
		);

  //RGCR very loose API Name.
  //RGCR you should be keen on API names
	Status Summary				(
		Book *&book,
		CSummary sSummary
		);

	Status InvalidFiles			(
		Book *&book,
		std::list<std::string> InvalidPathListBase,
		std::list<std::string> InvalidPathListModified
		);

	Status KeyReplication		(
		Book *&book,
		COutputCollector OutputCollector
		);

	std::wstring ConvertToWString(
		const std::string szInputString
		);

	std::wstring ConvertToHyperlink(
		const std::string szFilePath
		);

	Status GetNewPath( const std::string szOldPath, std::string &szNewPath,const ListType ltType , const DirectoryType dtType );

	Status CopyFiles(const std::string szOldPath,ListType ltType,DirectoryType dtType );

};


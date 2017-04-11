#include "StdAfx.h"
#include "OutputGenerator.h"
#include "OutputCollector.h"
#include "ExcelFileGenerator.h"

COutputGenerator::COutputGenerator(void)
{
}


COutputGenerator::~COutputGenerator(void)
{
}

//************************************
// Method:    GenerateOutput
// FullName:  COutputGenerator::GenerateOutput
// Access:    public 
// Returns:   Status
// Qualifier:
// Parameter: COutputCollector & OutputCollector
// Parameter: const List_Str & InvalidPathListBase
// Parameter: const List_Str & InvalidPathListModified
//************************************
Status COutputGenerator::GenerateOutput(COutputCollector &OutputCollector, 
										const List_Str &InvalidPathListBase, 
										const List_Str &InvalidPathListModified 
										)
{
	CExcelFileGenerator ExcelFileGenerator;
	Status retExcelFileGenerator = ExcelFileGenerator.GenerateFile(OutputCollector,
																	InvalidPathListBase,
																	InvalidPathListModified
																	);
	if (SUCCESS == retExcelFileGenerator)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}
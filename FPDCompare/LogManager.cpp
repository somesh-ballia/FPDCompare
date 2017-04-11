#include "StdAfx.h"
#include "LogManager.h"
#include "ConfigurationStorage.h"


CLogManager::CLogManager(void)
{
}


CLogManager::~CLogManager(void)
{
}

//************************************
// Method:    CreateLog
// FullName:  CLogManager::CreateLog
// Access:    public static 
// Returns:   Status
// Qualifier:
// Parameter: LogType ltLogType
// Parameter: String & szMessage
//************************************
Status CLogManager::CreateLog(LogType ltLogType,String &szMessage)
{
	String szLogPath;
	switch(ltLogType)
	{
	case LOG_UI:
		printf("\n%s",szMessage);
		break;
	case LOG_ERROR:
		CConfigurationStorage::getInstance()->GetLogFilePath(szLogPath);
		FILE *fpWriter = NULL;
		fpWriter = fopen(szLogPath.c_str(),"a+");
		if(NULL != fpWriter)
		{
			fprintf(fpWriter,"\n");
			fprintf(fpWriter,szMessage.c_str());
			fclose(fpWriter);
		}
		else
		{
			return FAILURE;
		}
		break;
	}
	return SUCCESS;
}


//************************************
// Method:    CreateLog
// FullName:  CLogManager::CreateLog
// Access:    public static 
// Returns:   Status
// Qualifier:
// Parameter: LogType ltLogType
// Parameter: int iMessage
//************************************
Status CLogManager::CreateLog(LogType ltLogType,int iMessage)
{
	switch(ltLogType)
	{
	case LOG_UI:
		printf("\n%d",iMessage);
		break;
	case LOG_ERROR:		
		break;
	}
	return SUCCESS;
}

//************************************
// Method:    CreateLog
// FullName:  CLogManager::CreateLog
// Access:    public static 
// Returns:   Status
// Qualifier:
// Parameter: LogType ltLogType
// Parameter: String & szMessage
// Parameter: int iMessage
//************************************
Status CLogManager::CreateLog(LogType ltLogType,String &szMessage,int iMessage)
{
	String szLogPath;
	switch(ltLogType)
	{
	case LOG_UI:
		printf("\n%s : %d",szMessage,iMessage);
		break;
	case LOG_ERROR:
		CConfigurationStorage::getInstance()->GetLogFilePath(szLogPath);
		FILE *fpWriter = NULL;
		fpWriter = fopen(szLogPath.c_str(),"a+");
		if(NULL != fpWriter)
		{
			fprintf(fpWriter,"\n");
			fprintf(fpWriter,szMessage.c_str(),iMessage);
			fclose(fpWriter);
		}
		else
		{
			return FAILURE;
		}
		break;
	}
	return SUCCESS;
}

//************************************
// Method:    CreateLog
// FullName:  CLogManager::CreateLog
// Access:    public static 
// Returns:   Status
// Qualifier:
// Parameter: LogType ltLogType
// Parameter: char * pszMessage
// Parameter: int iMessage
//************************************
Status CLogManager::CreateLog(LogType ltLogType,char *pszMessage,int iMessage)
{
	String szLogPath;
	switch(ltLogType)
	{
	case LOG_UI:
		printf("\n%s : %d",pszMessage,iMessage);
		break;
	case LOG_ERROR:
		CConfigurationStorage::getInstance()->GetLogFilePath(szLogPath);
		FILE *fpWriter = NULL;
		fpWriter = fopen(szLogPath.c_str(),"a+");
		if(NULL != fpWriter)
		{
			fprintf(fpWriter,"\n");
			fprintf(fpWriter,pszMessage,iMessage);
			fclose(fpWriter);
		}
		else
		{
			return FAILURE;
		}
		break;
	}
	return SUCCESS;
}

//************************************
// Method:    CreateLog
// FullName:  CLogManager::CreateLog
// Access:    public static 
// Returns:   Status
// Qualifier:
// Parameter: LogType ltLogType
// Parameter: char * pszMessage
//************************************
Status CLogManager::CreateLog(LogType ltLogType,char *pszMessage)
{
	String szLogPath;
	switch(ltLogType)
	{
	case LOG_UI:
		printf("\n%s",pszMessage,pszMessage);
		break;
	case LOG_ERROR:
		CConfigurationStorage::getInstance()->GetLogFilePath(szLogPath);
		FILE *fpWriter = NULL;
		fpWriter = fopen(szLogPath.c_str(),"a+");
		if(NULL != fpWriter)
		{
			fprintf(fpWriter,"\n");
			fprintf(fpWriter,pszMessage,pszMessage);
			fclose(fpWriter);
		}
		else
		{
			return FAILURE;
		}
		break;
	}
	return SUCCESS;
}
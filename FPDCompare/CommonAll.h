#pragma once
class CMatchResource;
class	CMetaPropertySet;
typedef CMatchResource CMissingResource;
typedef CMetaPropertySet CKey;
typedef std::string String;
typedef std::wstring Wstring;
typedef std::list<String> List_Str;
typedef std::list<Wstring> List_Wstr;

#define BUFFER_SIZE 32768
#define IMPMETA ".ImpMeta"

enum Status
{
	SUCCESS,
	FAILURE,
	ERRORU
};

enum Datatype
{
	DATATYPE_DATETIME,
	DATATYPE_STRING,
	DATATYPE_FILENAME,
	DATATYPE_NUMBER,
	DATATYPE_UNKNOWN
};

enum Multiplicity
{
	MULTIPLICITY_SINGLE,
	MULTIPLICITY_MULTIPLE,
	MULTIPLICITY_UNKNOWN
};

enum CompareResult
{
	COMPARE_MATCH,
	COMPARE_MISMATCH,
	COMPARE_MISSING,
	COMPARE_UNKNOWN
};

enum ListType
{
	LIST_MATCH,
	LIST_MISMATCH,
	LIST_MISSING,
	LIST_KEY_REPLICATION
};

enum DirectoryType
{
	BASE,
	MODIFIED
};

enum LogType
{
	LOG_UI,
	LOG_ERROR
};
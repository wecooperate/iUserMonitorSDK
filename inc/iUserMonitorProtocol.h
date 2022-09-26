#pragma once

class MonitorMessage : public IUserMonitorMessage
{
public:
	emMSGProcessType CurrentProcessType() { return (emMSGProcessType)GetHeader()->CurrentProcessType; }
	auto CurrentProcessName() { return GetString(emMSGFieldCurrentProcessName); };
	auto CurrentProcessPath() { return GetString(emMSGFieldCurrentProcessPath); };
	auto CurrentProcessCommandline() { return GetString(emMSGFieldCurrentProcessCommandline); };

protected:
	LPCWSTR GetPath(ULONG Index) { return GetString(Index); }
	bool GetBool(ULONG Index) { return GetULONG(Index) == TRUE; }
	emMSGFilePathType GetFilePathType(ULONG Index) { return (emMSGFilePathType)GetULONG(Index); }
};

class cxMSGShellRenameFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSrcPath,
		emMSGFieldSrcPathType,
		emMSGFieldDesPath,
		emMSGFieldDesPathType,
	};

public:
	auto SrcPath() { return GetPath(emMSGFieldSrcPath); }
	auto SrcPathType() { return GetFilePathType(emMSGFieldSrcPathType); }
	auto DesPath() { return GetPath(emMSGFieldDesPath); }
	auto DesPathType() { return GetFilePathType(emMSGFieldDesPathType); }
};
class cxMSGShellMoveFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSrcPath,
		emMSGFieldSrcPathType,
		emMSGFieldDesPath,
		emMSGFieldDesPathType,
	};

public:
	auto SrcPath() { return GetPath(emMSGFieldSrcPath); }
	auto SrcPathType() { return GetFilePathType(emMSGFieldSrcPathType); }
	auto DesPath() { return GetPath(emMSGFieldDesPath); }
	auto DesPathType() { return GetFilePathType(emMSGFieldDesPathType); }
};
class cxMSGShellDeleteFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldPathType,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto PathType() { return GetFilePathType(emMSGFieldPathType); }
};
class cxMSGShellCopyFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSrcPath,
		emMSGFieldSrcPathType,
		emMSGFieldDesPath,
		emMSGFieldDesPathType,
	};

public:
	auto SrcPath() { return GetPath(emMSGFieldSrcPath); }
	auto SrcPathType() { return GetFilePathType(emMSGFieldSrcPathType); }
	auto DesPath() { return GetPath(emMSGFieldDesPath); }
	auto DesPathType() { return GetFilePathType(emMSGFieldDesPathType); }
};
class cxMSGDownloadFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSrcPath,
		emMSGFieldSrcPathType,
		emMSGFieldDesPath,
		emMSGFieldDesPathType,
	};

public:
	auto SrcPath() { return GetPath(emMSGFieldSrcPath); }
	auto SrcPathType() { return GetFilePathType(emMSGFieldSrcPathType); }
	auto DesPath() { return GetPath(emMSGFieldDesPath); }
	auto DesPathType() { return GetFilePathType(emMSGFieldDesPathType); }
};
class cxMSGUploadFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSrcPath,
		emMSGFieldSrcPathType,
		emMSGFieldDesPath,
		emMSGFieldDesPathType,
	};

public:
	auto SrcPath() { return GetPath(emMSGFieldSrcPath); }
	auto SrcPathType() { return GetFilePathType(emMSGFieldSrcPathType); }
	auto DesPath() { return GetPath(emMSGFieldDesPath); }
	auto DesPathType() { return GetFilePathType(emMSGFieldDesPathType); }
};

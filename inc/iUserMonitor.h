//******************************************************************************
/*++
	FileName:		iUserMonitor.h
	Description:

--*/
//******************************************************************************
#ifndef __iUserMonitor_h_1606c8e5_7a4a_472e_ac14_76606bfcaab8__
#define __iUserMonitor_h_1606c8e5_7a4a_472e_ac14_76606bfcaab8__
//******************************************************************************
#ifndef IUSERMONITOR_BEGIN_NAMESPACE
#define IUSERMONITOR_BEGIN_NAMESPACE
#define IUSERMONITOR_END_NAMESPACE
#endif
//******************************************************************************
IUSERMONITOR_BEGIN_NAMESPACE
//******************************************************************************
#ifndef BIT
#define BIT(n) (1 << n)
#endif
//******************************************************************************
enum emMSGType {
	emMSGBegin,
	emMSGShellRenameFile,
	emMSGShellMoveFile,
	emMSGShellDeleteFile,
	emMSGShellCopyFile,
	emMSGDownloadFile,
	emMSGUploadFile,
	emMSGEnd,
};
//******************************************************************************
enum emMSGConfig {
	emMSGConfigDefault = 0,
	emMSGConfigPost = BIT(0),
	emMSGConfigSend = BIT(1),
	emMSGConfigEnable = emMSGConfigPost | emMSGConfigSend,
};
//******************************************************************************
enum emMSGDataType {
	//
	//    base
	//
	emMSGDataUnknown = 0,
	emMSGDataULONG = 0x10000,
	emMSGDataULONGLONG = 0x20000,
	emMSGDataString = 0x30000,
	emMSGDataPath = 0x40000,
	emMSGDataBinary = 0x50000,
	emMSGDataCallstack = 0x60000,

#define MSG_GET_BASE_TYPE(type) (type & 0xFFFF0000)

	//
	//    extension
	//
	emMSGDataBool = emMSGDataULONG + 1,
	emMSGDataFilePathType,

	emMSGDataTime = emMSGDataULONGLONG + 1,
};
//******************************************************************************
enum emMSGProcessType {
	emMSGProcessTypeUnknown,
	emMSGProcessTypeExplorer,
	emMSGProcessTypePrinter,
	emMSGProcessTypeQQ,
	emMSGProcessTypeWeChat,
	emMSGProcessTypeBaiduYunPan,
	emMSGProcessTypeQQYunPan,
	emMSGProcessType360YunPan,
	emMSGProcessTypeFoxmail,
	emMSGProcessTypeEvernote,
};
//******************************************************************************
enum emMSGFilePathType {
	emMSGFilePathUnknown,
	emMSGFilePathLocal,
	emMSGFilePathUSB,
	emMSGFilePathUNC,
	emMSGFilePathFTP,
	emMSGFilePathUrl,
	emMSGFilePathProcess,
};
//******************************************************************************
enum emMSGField {
	emMSGFieldInvalid = -1,
	emMSGFieldCurrentProcessName,
	emMSGFieldCurrentProcessPath,
	emMSGFieldCurrentProcessCommandline,
	emMSGFieldPrivateBegin,
	emMSGFieldPath = emMSGFieldPrivateBegin,

	emMSGFieldDefault = 0xFFFFFFFF,
};
//******************************************************************************
struct cxMSGHeader
{
	ULONG Type;
	ULONG Length;
	ULONG Status;
	ULONG Config;
	ULONG SeqId;
	ULONG Fields;
	ULONG CurrentProcessId;
	ULONG CurrentThreadId;
	ULONG CurrentProcessType;
	ULONG Reserved1;
	ULONGLONG Time;

	//
	//    后面跟着多个 cxMSGDataHeader + Data
	//
};
//******************************************************************************
struct cxMSGDataHeader
{
	ULONG Type;
	ULONG Length;

	template<typename T>
	T* GetData(void) { return (T*)(this + 1); }
	PVOID GetData(void) { return (PVOID)(this + 1); }

	cxMSGDataHeader* Next(void) { return (cxMSGDataHeader*)((ULONG_PTR)this + Length); }
};
//******************************************************************************
IUSERMONITOR_END_NAMESPACE
//******************************************************************************
#endif

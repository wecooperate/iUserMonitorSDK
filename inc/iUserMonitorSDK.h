//******************************************************************************
/*++
	FileName:		iUserMonitorSDK.h
	Description:

--*/
//******************************************************************************
#ifndef __iUserMonitorSDK_h_e689dffd_3e2f_48ad_8971_19e87a658f2a__
#define __iUserMonitorSDK_h_e689dffd_3e2f_48ad_8971_19e87a658f2a__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <tchar.h>
#include <windows.h>
#include <atlbase.h>
#include <atlstr.h>
//******************************************************************************
#include "iUserMonitor.h"
//******************************************************************************
#ifdef _M_IX86
#define MONITOR_MODULE_NAME _T("iUserMonitor.dll")
#else
#define MONITOR_MODULE_NAME _T("iUserMonitor64.dll")
#endif
//******************************************************************************
#define IUSER_MONITOR_IID "{EFED7F42-3713-4769-B774-5A093B43D7D7}"
//******************************************************************************
IUSERMONITOR_BEGIN_NAMESPACE
//******************************************************************************
//
//	interface
//
//******************************************************************************
interface IUserMonitorMessage
{
	struct Binary {
		PVOID Data;
		ULONG Length;
	};

	virtual cxMSGHeader*	GetHeader			(void) = 0;
	inline ULONG			GetType				(void) { return GetHeader()->Type; }
	inline ULONG			GetStatus			(void) { return GetHeader()->Status; }
	inline ULONG			GetCurrentProcessId	(void) { return GetHeader()->CurrentProcessId; }
	inline ULONG			GetCurrentThreadId	(void) { return GetHeader()->CurrentThreadId; }

	virtual LPCWSTR			GetTypeName			(void) = 0;
	virtual ULONG			GetFieldCount		(void) = 0;
	virtual emMSGDataType	GetFieldType		(ULONG Index) = 0;
	virtual LPCWSTR			GetFieldName		(ULONG Index) = 0;
	virtual ULONG			GetFieldIndex		(LPCWSTR Name) = 0;

	virtual ULONG			GetULONG			(ULONG Index) = 0;
	virtual ULONGLONG		GetULONGLONG		(ULONG Index) = 0;
	virtual LPCWSTR			GetString			(ULONG Index) = 0;
	virtual LPCWSTR			GetFormatedString	(ULONG Index) = 0;
	virtual Binary			GetBinary			(ULONG Index) = 0;
};
//******************************************************************************
interface IUserMonitorCallback
{
	virtual void			OnCallback			(IUserMonitorMessage* Message) = 0;
};
//******************************************************************************
interface __declspec (uuid(IUSER_MONITOR_IID)) IUserMonitorManager : public IUnknown
{
	virtual HRESULT			Start				(IUserMonitorCallback* Callback) = 0;
	virtual HRESULT			Stop				(void) = 0;
};
//******************************************************************************
//
//	helper
//
//******************************************************************************
// clang-format on
//******************************************************************************
class UserMonitorManager
{
public:
	UserMonitorManager(void)
		: m_MonitorModule(NULL)
	{
	}

	~UserMonitorManager(void)
	{
		Stop();

		m_Monitor = NULL;
	}

	HRESULT Start(IUserMonitorCallback* Callback, LPCTSTR Path = MONITOR_MODULE_NAME)
	{
		HRESULT hr = LoadMonitor(Path);

		if (hr != S_OK && hr != S_FALSE)
			return hr;

		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Start(Callback);
	}

	HRESULT Stop(void)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Stop();
	}

protected:
	HRESULT LoadMonitor(LPCTSTR Path)
	{
		if (m_Monitor)
			return S_FALSE;

		if (!Path)
			Path = MONITOR_MODULE_NAME;

		if (!m_MonitorModule) {
			m_MonitorModule = LoadLibraryEx(Path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

			if (!m_MonitorModule)
				return HRESULT_FROM_WIN32(GetLastError());
		}

		typedef HRESULT(STDAPICALLTYPE * PFN_DllGetClassObject)(REFCLSID, REFIID, PVOID*);

		PFN_DllGetClassObject pfn = (PFN_DllGetClassObject)GetProcAddress(m_MonitorModule, "DllGetClassObject");

		if (!pfn)
			return E_FAIL;

		return pfn(CLSID_NULL, __uuidof(IUserMonitorManager), (PVOID*)&m_Monitor);
	}

protected:
	HMODULE m_MonitorModule;
	CComPtr<IUserMonitorManager> m_Monitor;
};
//******************************************************************************
IUSERMONITOR_END_NAMESPACE
//******************************************************************************
#endif

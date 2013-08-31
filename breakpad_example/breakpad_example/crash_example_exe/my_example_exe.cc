/**
example process
cswuyg@gmail.com
2013.8.30
*/
#include "stdafx.h"

#include "my_example_exe.h"
#include "MainDlg.h"
#include "..\common\common.h"

#include <common\windows\http_upload.h>
#include <client\windows\handler\exception_handler.h>


namespace MyClient
{
	CAppModule _Module;
	static std::wstring g_dump_path;

	void MyExampleMain(HINSTANCE hInstance)
	{
		StartServerExe();
		AddExceptionCatch();

		HRESULT hRes = ::CoInitialize(NULL);
		ATLASSERT(SUCCEEDED(hRes));
		::DefWindowProc(NULL, 0, 0, 0L);
		AtlInitCommonControls(ICC_BAR_CLASSES);	
		hRes = _Module.Init(NULL, hInstance);
		ATLASSERT(SUCCEEDED(hRes));

		int nRet = 0;
		{
			CMainDlg dlgMain;
			nRet = dlgMain.DoModal();
		}
		_Module.Term();
		::CoUninitialize();
	}


	DWORD WINAPI AsynUpload( void* context )
	{
		std::map<std::wstring, std::wstring> parameters;
		int timeout = 30000;  //30second send or receive timeout
		std::wstring response_body;
		int response_code = 0;
		bool bRet = google_breakpad::HTTPUpload::SendRequest(L"http://172.17.195.141/hfs_up/",
			parameters,
			g_dump_path.c_str(),
			L"ufile01",
			&timeout,
			&response_body,
			&response_code);
		return 0;
	}

	bool ShowDumpResults(const wchar_t* dump_path,
		const wchar_t* minidump_id,
		void* context,
		EXCEPTION_POINTERS* exinfo,
		MDRawAssertionInfo* assertion,
		bool succeeded) {
			//In case of out-of-process dump generation, dump_path will be NULL.
			if (dump_path == NULL)
			{
				return succeeded;
			}
			g_dump_path = dump_path;
			QueueUserWorkItem(AsynUpload, NULL, WT_EXECUTEDEFAULT);
			return succeeded;
	}

	void AddExceptionCatch()
	{
		std::wstring dump_folder = L"C:\\dumps\\"; 
		::CreateDirectory(dump_folder.c_str(), NULL);
		google_breakpad::CustomClientInfo custom_info = {kCustomInfoEntries, kCustomInfoCount};
		static google_breakpad::ExceptionHandler* handler = new google_breakpad::ExceptionHandler(dump_folder.c_str(),
			NULL,
			ShowDumpResults,
			NULL,
			google_breakpad::ExceptionHandler::HANDLER_ALL,
			MiniDumpNormal,
			kPipeName,
			&custom_info);
	}

	std::wstring GetGUIDStr()
	{
		wchar_t buffer[128] = { 0 };
		GUID guid;
		if (::CoCreateGuid(&guid) != S_OK)
		{
			return L"";
		}
		::_snwprintf_s(buffer, _countof(buffer), _countof(buffer), L"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3, 
			guid.Data4[0], guid.Data4[1], guid.Data4[2], 
			guid.Data4[3], guid.Data4[4], guid.Data4[5], 
			guid.Data4[6], guid.Data4[7]);
		return buffer;
	}

	void StartServerExe()
	{
		wchar_t lpszFileName[MAX_PATH] = {0};
		::GetModuleFileName(NULL, lpszFileName, MAX_PATH);
		std::wstring strFullName = lpszFileName;
		std::wstring strGUID = GetGUIDStr();
		HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, strGUID.c_str());
		std::wstring strParam = L"crash_server=";
		strParam += strGUID;
		::ShellExecute(NULL, L"open", strFullName.c_str(), strParam.c_str(), NULL, SW_SHOWNORMAL);
		if (hEvent != NULL)
		{
			// wait for the crash_server start, wait 2 seconds.
			DWORD dwRet = ::WaitForSingleObject(hEvent, 2000);
			if (dwRet != WAIT_OBJECT_0)
			{
				//error
			}
			::CloseHandle(hEvent);
		}
		else 
		{
			//error
		}
	}
}
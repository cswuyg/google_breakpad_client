/**
crash guard process
cswuyg@gmail.com
2013.8.30
*/
#include "stdafx.h"
#include "guard_process_main_exe.h"
#include "crash_generation_server.h"
#include "..\common\common.h"

#include <common\windows\http_upload.h>

namespace GuardProcess
{
	static std::wstring g_dump_path;
	static HANDLE g_uploadover = NULL;
	static BOOL g_client_exit = FALSE;
	static BOOL g_restart_client = FALSE;
	google_breakpad::CrashGenerationServer* g_crash_server = NULL;
	BOOL CrashServerStart(const std::wstring& event_name)
	{
		std::wstring dump_path = L"C:\\Dumps\\";   
		::CreateDirectory(dump_path.c_str(), NULL);
		g_crash_server = new google_breakpad::CrashGenerationServer(
			kPipeName, NULL,
			NULL, NULL,
			ShowClientCrashed, NULL,
			ShowClientExited, NULL,
			NULL, NULL,
			true, &dump_path);

		if (!g_crash_server->Start()) 
		{
			delete g_crash_server;
			g_crash_server = NULL;
			return FALSE;
		}
		HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, event_name.c_str());
		if (hEvent != NULL)
		{
			::SetEvent(hEvent);
		}
		::CloseHandle(hEvent);
		return TRUE;
	}

	void _cdecl ShowClientCrashed( void* context, const google_breakpad::ClientInfo* client_info, const std::wstring* dump_path )
	{
		g_dump_path = *dump_path;
		::QueueUserWorkItem(AsynUpload, NULL, WT_EXECUTEDEFAULT);
		g_uploadover = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		g_restart_client = TRUE;
	}

	void ShowClientExited(void* context, const google_breakpad::ClientInfo* client_info)
	{
		g_client_exit = TRUE;
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
	
		if (g_uploadover != NULL)
		{
			::SetEvent(g_uploadover);
		}
		return 0;
	}

	void GuardProcessMain(const std::wstring& server_start_event_name)
	{
		if (!CrashServerStart(server_start_event_name))
		{
			return;
		}

		while(!g_client_exit)
		{
			::Sleep(1000);
		}
		if (g_restart_client)
		{
			delete g_crash_server;
			g_crash_server = NULL;
			wchar_t lpszFileName[MAX_PATH] = {0};
			::GetModuleFileName(NULL, lpszFileName, MAX_PATH);
			std::wstring strFullName = lpszFileName;
			::ShellExecute(NULL, L"open", strFullName.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
		if (g_uploadover != NULL)
		{
			DWORD dwRet = ::WaitForSingleObject(g_uploadover, 15000);
			if (dwRet != WAIT_OBJECT_0)
			{
				//error
			}
		}

	}


}
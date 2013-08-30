/**
crash guard process
cswuyg@gmail.com
2013.8.30
*/
#include "stdafx.h"
#include "crash_server_main_exe.h"
#include "crash_generation_server.h"
#include "..\common\common.h"

#include <common\windows\http_upload.h>

namespace MyServer
{
	static std::wstring g_dump_path;
	BOOL CrashServerStart(const std::wstring& event_name)
	{
		std::wstring dump_path = L"C:\\Dumps\\";
		google_breakpad::CrashGenerationServer* crash_server = new google_breakpad::CrashGenerationServer(kPipeName,
			NULL,
			NULL,
			NULL,
			ShowClientCrashed,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			true,
			&dump_path);

		if (!crash_server->Start()) 
		{
			delete crash_server;
			crash_server = NULL;
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
		QueueUserWorkItem(AsynUpload, NULL, WT_EXECUTEDEFAULT);
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

	void ServerMain(const std::wstring& mutex_name)
	{
		if (!CrashServerStart(mutex_name + L"_"))
		{
			return;
		}

		HANDLE mutex_handle = ::CreateMutex(NULL, TRUE, mutex_name.c_str());
		while(TRUE)
		{
			if (::WaitForSingleObject(mutex_handle, 1000) != WAIT_ABANDONED)
			{
				::Sleep(1000);
			}
			else
			{
				break;
			}
		}

	}
}
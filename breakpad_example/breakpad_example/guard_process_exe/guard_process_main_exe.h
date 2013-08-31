/**
crash guard process
cswuyg@gmail.com
2013.8.30
*/
#pragma once
#include "client_info.h"

#include <string>
#include <map>

namespace GuardProcess
{
	void GuardProcessMain(const std::wstring& server_start_event_name);

	BOOL CrashServerStart(const std::wstring& event_name); 
	void ShowClientCrashed(void* context, const google_breakpad::ClientInfo* client_info, const std::wstring* dump_path);
	void ShowClientExited(void* context, const google_breakpad::ClientInfo* client_info);
	DWORD WINAPI AsynUpload(void* context);
}
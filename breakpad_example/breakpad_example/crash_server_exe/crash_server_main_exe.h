/**
crash guard process
cswuyg@gmail.com
2013.8.30
*/
#pragma once
#include "client_info.h"

#include <string>
#include <map>

namespace MyServer
{
	void ServerMain(const std::wstring& mutex_name);

	BOOL CrashServerStart(const std::wstring& event_name); 
	void ShowClientConnected(void* context, const google_breakpad::ClientInfo* client_info);
	void ShowClientCrashed(void* context, const google_breakpad::ClientInfo* client_info, const std::wstring* dump_path);
	void ShowClientExited(void* context, const google_breakpad::ClientInfo* client_info);
	DWORD WINAPI AsynUpload(void* context);
}
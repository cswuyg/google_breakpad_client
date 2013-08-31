/**
example process
cswuyg@gmail.com
2013.8.30
*/
#pragma once

#include <client\windows\common\ipc_protocol.h>


namespace WorkProcess
{
	static int kCustomInfoCount = 2;
	static google_breakpad::CustomInfoEntry kCustomInfoEntries[] = {
		google_breakpad::CustomInfoEntry(L"prod", L"CrashTestApp"),
		google_breakpad::CustomInfoEntry(L"ver", L"1.0"),
	};

	std::wstring GetGUIDStr();
	void AddExceptionCatch();
	void WorkProcessMain(HINSTANCE hInstance);
	void StartServerExe();
}
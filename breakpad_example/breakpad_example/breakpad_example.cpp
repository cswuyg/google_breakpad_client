/**
both gurad process and example process's main funcion 
cswuyg@gmail.com
2013.8.30
*/
#include "stdafx.h"

#include "common\cmdline_parse.h"
#include "guard_process_exe\guard_process_main_exe.h"
#include "work_process_exe\work_process_exe.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
	CmdlineParser cmd_parse(lpstrCmdLine);
	std::wstring server_start_event_name = cmd_parse.GetValueByKey(L"crash_server");
	if (!server_start_event_name.empty())
	{
		GuardProcess::GuardProcessMain(server_start_event_name);
		return 0;
	}
	else
	{
		WorkProcess::WorkProcessMain(hInstance);
		return 0;
	}
}

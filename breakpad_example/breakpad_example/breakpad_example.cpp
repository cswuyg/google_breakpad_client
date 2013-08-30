/**
both gurad process and example process's main funcion 
cswuyg@gmail.com
2013.8.30
*/
#include "stdafx.h"

#include "common\cmdline_parse.h"
#include "crash_server_exe\crash_server_main_exe.h"
#include "crash_example_exe\my_example_exe.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
	CmdlineParser cmd_parse(lpstrCmdLine);
	std::wstring mutex_name = cmd_parse.GetValueByKey(L"crash_server");
	if (!mutex_name.empty())
	{
		MyServer::ServerMain(mutex_name);
		return 0;
	}
	else
	{
		MyClient::MyExampleMain(hInstance);
		return 0;
	}
}

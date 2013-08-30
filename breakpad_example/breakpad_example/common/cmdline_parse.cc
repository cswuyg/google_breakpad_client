/**
command line parse
cswuyg@gmail.com
2013.8.30
*/
#include "stdafx.h"
#include "cmdline_parse.h"


CmdlineParser::CmdlineParser( const std::wstring& cmdline )
	: cmdline_(cmdline)
{
	Parser();
}

CmdlineParser::~CmdlineParser()
{
}

std::wstring CmdlineParser::GetValueByKey( const std::wstring& key )
{
	if (key.empty())
	{
		return L"";
	}
	std::map<std::wstring, std::wstring>::iterator itFind = all_key_value_.find(key);
	if (itFind != all_key_value_.end())
	{
		return itFind->second;
	}
	return L"";
}

void CmdlineParser::Parser()
{
	if (cmdline_.empty())
	{
		return;
	}

	CComBSTR bstrKey;
	CComBSTR bstrValue;
	int num_args = 0;
	LPWSTR* lpwszArgv = ::CommandLineToArgvW(cmdline_.c_str(), &num_args);	
//Just first argument, I don't care other argument.
	std::wstring argum = lpwszArgv[0];
	if (argum.empty())
	{
		return;
	}
	while (!argum.empty())
	{
		std::wstring::size_type left_pos = argum.find(L"=");
		std::wstring left = argum.substr(0, left_pos);
		argum = argum.substr(left_pos+1);
		std::wstring::size_type space_pos = argum.find(L" ");
		if (space_pos == std::wstring::npos)
		{
			all_key_value_.insert(std::make_pair(left, argum));
			break;
		}
		else
		{
			std::wstring right = argum.substr(0, space_pos-1);
			all_key_value_.insert(std::make_pair(left, right));
		}
		space_pos = argum.find_first_not_of(L' ');
		if (space_pos == std::wstring::npos)
		{
			break;
		}
		argum = argum.substr(space_pos);
	}

}

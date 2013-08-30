/**
command line parse
cswuyg@gmail.com
2013.8.30
*/
#pragma once

#include <map>
#include <string>

class CmdlineParser
{
 
public:
	CmdlineParser(const std::wstring& cmdline);
	~CmdlineParser();

	std::wstring GetValueByKey(const std::wstring& key);

private:
	void Parser();

private:
	std::map<std::wstring, std::wstring> all_key_value_;
	std::wstring cmdline_;
};
// breakpad_report_sender.cpp : Defines the entry point for the console application.
//

#include "sender/http_upload.h"
#include <map>
#include <iostream>
#include <string>


void test_http_upload()
{
	std::map<std::wstring, std::wstring> parameters;
	parameters.insert(std::make_pair(L"myname1", L"myvalue1"));
	parameters.insert(std::make_pair(L"myname2", L"myvalue2"));

	int timeout = 30000;  //30second send or receive timeout
	std::wstring response_body;
	int response_code = 0;
	bool bRet = google_breakpad::HTTPUpload::SendRequest(L"http://172.17.195.141/hfs_up/",
							parameters,
							L"C:\\temp\\a.txt",
							L"ufile01",
							&timeout,
							&response_body,
							&response_code);
}



int main(int argc, char* argv[])
{
	test_http_upload();
	return 0;
}


/* package data :*/
/*

POST /hfs_up/ HTTP/1.1
Content-Type: multipart/form-data; boundary=---------------------------0000002900004823
User-Agent: Breakpad/1.0 (Windows)
Host: 172.17.195.141
Content-Length: 769
Cache-Control: no-cache
-----------------------------0000002900004823
Content-Disposition: form-data; name="myname1"

myvalue1
-----------------------------0000002900004823
Content-Disposition: form-data; name="myname2"
myvalue2
-----------------------------0000002900004823
Content-Disposition: form-data; name="ufile01"; filename="C:\temp\a.txt"
Content-Type: application/octet-stream

{"block_num":"8","blocks":[{"len":"0","pos":"2097152"},{"len":"0","pos":"4194304"},{"len":"0","pos":"6291456"},{"len":"0","pos":"8388608"},{"len":"0","pos":"10485760"},{"len":"0","pos":"12582912"},{"len":"0","pos":"14680064"},{"len":"0","pos":"16282464"}],"file_name":"C:/temp/BaiduHi.exe","filesize":"16282464","filetime":"20130827072856"}
-----------------------------0000002900004823--
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 2123
Accept-Ranges: bytes
Server: HFS 2.2f
*/
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<regex>
#include <tchar.h>
#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <winuser.h>
#include <strstream>
using namespace std;
wchar_t path[MAX_PATH];
DWORD bufCharCount[MAX_PATH];
string CompName() {

	char buffer[256];
	DWORD size = 256;
	GetComputerNameA(buffer, &size);
	cout << "Computer Name is " << buffer << endl;
	return (string)buffer;
}
string UserName() {
	char buffer[257];
	DWORD size;
	size = sizeof(buffer);
	GetUserNameA(buffer, &size);

	cout << "User name is " << buffer << endl;
	return (string)buffer;
}
string Windows() {
	GetWindowsDirectoryW(path, MAX_PATH);
	std::wcout << L"Windows directory is " << path << L'\n';
	wstring ws(path);
	string str(ws.begin(), ws.end());
	return str;
}
string System() {

	GetSystemDirectoryW(path, MAX_PATH);
	std::wcout << L"System Directory is " << path << L'\n';
	wstring ws(path);
	string str(ws.begin(), ws.end());
	return str;
}
string getWeight() {
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	cout << "Weight: " << screenW << endl;
	return to_string(screenW);
}
string getRAM() {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	cout << (float)status.ullTotalPhys / (1024 * 1024 * 1024) << " Gb " << endl;
	return to_string((float)status.ullTotalPhys / (1024 * 1024 * 1024));
}
string getHDD() {
	char DRV[] = "X:\\";
	DRV[0] = 'D';
	char volName[MAX_PATH] = { 0 };
	char pFSName[MAX_PATH] = { 0 };
	DWORD dwSerial;
	DWORD dwMaxLen;
	DWORD SysFlags;
	if
		(
			!GetVolumeInformation
			(
				DRV,
				volName,
				MAX_PATH,
				&dwSerial,
				&dwMaxLen,
				&SysFlags,
				pFSName,
				MAX_PATH
			)
			)
		cout << "incorrect tome" << endl;
	else
		cout << "DRIVE \t  : " << DRV << endl
		<< "VOLName\t : " << volName << endl
		<< "MAXLen    : " << dwMaxLen << endl
		<< "sFileSys  : " << pFSName << endl;
	return string(DRV) + string(volName) + string(pFSName);
}
string Mouse() {
	int result = GetSystemMetrics(SM_CMOUSEBUTTONS);
	cout << "Mouse has " << result << " buttons" << endl;
	return to_string(result);
}
void main() {
	cout << "Enter path to write files of your programm" << endl;
	string path;
	cin >> path;
	path += "lab_1.cpp";
	string k = "copy C:\\Users\\intet\\source\\repos\\lab_1\\lab_1.cpp " + path;
	const char* b = k.c_str();
	cout << path;
	system(b);
	string path2 = "\software\Kupriienko";
	string info = CompName() + UserName() + Windows() + System() + Mouse() + getWeight() + getRAM() + getHDD();
	int signature = hash<string>{}(info);
	string str_sign = to_string(signature);
	string* a = &str_sign;
	HKEY h;
	LPCTSTR value = TEXT("signature");

	if (RegCreateKeyEx(HKEY_CURRENT_USER, "software\\Kupriienko", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &h, NULL) == ERROR_SUCCESS)
	{

	}

	if (RegSetValueEx(h, value, 0, REG_SZ, (BYTE*)a, str_sign.length()) != ERROR_SUCCESS) {
		cout << "NOP";
	}

}
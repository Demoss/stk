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
string PATH("list_of_users.txt");

void CreateFile() {
	ofstream fout;
	fout.open(PATH, ofstream::app);
	fout << "ADMIN" << ":" << "" << ":" << "0" << ":" << "0\n" << endl;
	fout.close();
}

vector<vector<string>> readFile() {
	vector<string> a;
	vector<vector<string>> users;
	ifstream fin;
	fin.open(PATH);
	string s;
	string b;
	if (!fin.is_open()) {
		CreateFile();
		fin.open(PATH);
	}

	while (!fin.eof()) {
		getline(fin, s);
		if (s == "") {
			break;
		}
		stringstream ss;
		ss = stringstream(s);
		while (getline(ss, b, ':')) {
			a.push_back(b);
		}
		users.push_back(a);
		a.clear();
	}
	return users;
	fin.close();

}

void WriteFile(vector<vector<string>> user) {
	ofstream fout;
	fout.open(PATH, ofstream::in);
	for (size_t i = 0; i < user.size(); i++)
	{
		fout << user[i][0] << ":" << user[i][1] << ":" << user[i][2] << ":" << user[i][3] << endl;
	}
	fout.close();
}

bool verify(string pass) {
	int uppercase = count_if(pass.cbegin(), pass.cend(), [](const char& a) {return isupper(a); });
	int lowercase = count_if(pass.cbegin(), pass.cend(), [](const char& a) {return islower(a); });
	int operand = count_if(pass.cbegin(), pass.cend(), [](const char& a) {return a == '+' || a == '-' || a == '/' || a == '*'; });
	if (uppercase == 0) {
		cout << "Your password must contain at least 1 uppercase letter" << endl;
		return false;
	}
	else if (lowercase == 0) {
		cout << "Your password must contain at least 1 lowercase letter" << endl;
		return false;
	}
	else if (operand == 0) {
		cout << "Your password must contain at least 1 operand" << endl;
		return false;
	}
	else {
		return true;
	}

}


string ChangePass(int isLimited, string oldpass) {
	cout << "Enter your current password" << endl;
	string old;
	cin.ignore(256, '\n');
	getline(cin, old);
	if (old == oldpass) {
		cout << "Enter new password" << endl;
		string pass;
		cin >> pass;
		string repass;
		if (isLimited == 1) {

			if (verify(pass)) {
				cout << "Enter new password 1 more time" << endl;
				cin >> repass;
				if (repass == pass) {
					cout << "your password has changed" << endl;
					return repass;
				}
				else
				{
					cout << "passwords are different " << endl;
					return oldpass;
				}
			}
			else {
				do
				{
					cin >> pass;
				} while (!verify(pass));
				cout << "Enter new password 1 more time" << endl;
				cin >> repass;
				if (repass == pass) {
					cout << "your password has changed" << endl;
					return repass;
				}
				else
				{
					cout << "passwords are different " << endl;
					return oldpass;
				}
			}


		}
		else {
			cout << "Enter new password 1 more time" << endl;
			cin >> repass;
			if (repass == pass) {
				cout << "your password has changed" << endl;
				return repass;
			}
			else
			{
				cout << "passwords are different " << endl;
				return oldpass;
			}
		}
	}
	else {
		cout << "incorrect password" << endl;
		exit(1);
	}
}
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
	
	cout <<"User name is "<< buffer << endl;
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
string getWeight(){
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	cout <<"Weight: "<< screenW << endl;
	return to_string(screenW);
}
string getRAM() {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	cout << (float)status.ullTotalPhys/(1024*1024*1024)<<" Gb "<<endl;
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
		cout << "incorrect tome" <<  endl;
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
int main()
{
	/*string info = CompName()+UserName()+Windows()+System()+Mouse()+getWeight()+getRAM()+getHDD();*/
	/*int signature = hash<string>{}(info);
	string str_sign = to_string(signature);
	cout << str_sign << endl;
	string *a = &str_sign;
	HKEY h;
	LPCTSTR value = TEXT("signature");
	LONG IRValue;
	LONG Val;
	CHAR KeyBuffer[32];
	DWORD RegType = REG_SZ;
	string NewUniqueId;
	DWORD RegSize = sizeof(NewUniqueId);
	IRValue = RegOpenKeyEx(HKEY_CURRENT_USER, "software\\Kupriienko", 0, KEY_QUERY_VALUE, &h);
		if (IRValue == ERROR_SUCCESS) {
			cout << "Opened the subkey successfully." << endl;
			Val = RegQueryValueEx(h, "signature",0,&RegType,(LPBYTE)&NewUniqueId,&RegSize);
			if (Val == ERROR_SUCCESS) {
				cout << "Value was extracted" << endl;
				if (str_sign == NewUniqueId) {
					cout << "sign is similar" << endl;
				}
				else {
					exit(1);
				}
				}
			else {
				cout << "No" << endl;
			}
		}
		else {
			cout<<"Error encountered."<<endl;
			exit(EXIT_FAILURE);
		}
		RegCloseKey(h);*/
	
	string login;
	string SecPhrase;
	string pass;
	string isBlocked;
	string isLimited;
	string text ="";
	int attempts = 1;
	int opt;
	string newpass = "";
	vector<vector<string>> users = readFile();
	vector<string> NewUser;
	int id = -1;
	HCRYPTPROV hProv = NULL;
	HCRYPTHASH hHash;
	string ex;
	const char* b;
	HCRYPTKEY hSessionKey;
	DWORD counts;
	HCRYPTKEY Key;
	string tmp;
	string res = "";
	HCRYPTKEY* phKey = &Key;
	const char* e = res.c_str();
	DWORD ct = strlen(e);
	const char* c = SecPhrase.c_str();
	DWORD count = strlen(c);

	char* hash_value = static_cast<char*>(malloc(count + 1));
	ZeroMemory(hash_value, count + 1);
	if (!CryptAcquireContext(&hProv,NULL, MS_DEF_RSA_SCHANNEL_PROV, PROV_RSA_FULL, 0))
	{
		cout << "!CryptAcquireContext" << endl;
		return 1;
	}
	if (!CryptGenKey(hProv, CALG_RC4,
		CRYPT_ENCRYPT | CRYPT_DECRYPT, phKey))
	{
		cout << "!CryptGenKey" << endl;
		return 1;
	}
	if (!CryptDecrypt(Key, 0, true, 0, (BYTE*)e, &ct))
	{
		cout << "CryptDecrypt" << endl;
		return 1;
	}
	std::cout << "Розшифрований файл: " << e << std::endl;
	ofstream fout;
	fout.open("list.txt", ofstream::out);
	fout << e;
	fout.close();
	CryptDestroyKey(Key);
	if (!CryptDeriveKey(hProv, CALG_RC4, hHash, CRYPT_NO_SALT, &Key)) {
		cout << "!CryptDeriveKey" << endl;
		return 1;
	}
	
	
	
	
	
	
	cout << "press 1 to log in as admin" << endl;
	cout << "press 2 to log in as user" << endl;
	cout << "press 3 to get info" << endl;
	cout << "press 4 to exit" << endl;
	int choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Enter your password" << endl;

		cin.ignore(256, '\n');
		getline(cin, pass);

		while (true)
		{
			if (pass == users[0][1]) {
				cout << "OK" << endl;
				break;
			}
			else {
				cout << "incorrect password" << endl;
				cout << "you have " << 3 - attempts << " more attempts" << endl;
				attempts += 1;
				cin.ignore(256, '\n');
				getline(cin, pass);
				if (attempts == 3) {
					id = -1;
					cout << "no more attempts" << endl;
					exit(1);
				}
			}
		}
		cout << "press 1 to change password" << endl;
		cout << "press 2 to get list of users" << endl;
		cout << "press 3 to add new user" << endl;
		cout << "press 4 to block user" << endl;
		cout << "press 5 to set/unset limit on user password" << endl;
		cout << "press 6 to exit" << endl;
		cout << "press 7 to enter secret phrase" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1:
			newpass = ChangePass(0, pass);
			if (pass != newpass) {
				users[0][1] = newpass;
				WriteFile(users);
				exit(1);
			}
		case 2:
			for (size_t i = 1; i < users.size(); i++)
			{
				cout << users[i][0] << " is blocked:" << users[i][2] << " password is limited:" << users[i][3] << endl;
			}
			break;
		case 3:
			cout << "Enter user name: ";
			cin >> login;
			NewUser.push_back(login);
			NewUser.push_back("");
			cout << "If user is blocked press 1, other 0" << endl;
			cin >> isBlocked;
			NewUser.push_back(isBlocked);
			cout << "If user password is limited press 1, other 0" << endl;
			cin >> isLimited;
			NewUser.push_back(isLimited);
			users.push_back(NewUser);
			WriteFile(users);
			cout << "User has been added" << endl;
			break;
		case 4:
			cout << "Enter username: " << endl;
			cin >> login;
			while (true)
			{
				for (size_t i = 0; i < users.size(); i++)
				{
					if (login == (string)users[i][0]) {
						id = i;
						break;
					}
					
				}
				break;
				if (id == -1) {
					cout << "No such username" << endl;
					cout << "If you want to exit, press 1" << endl;
					cin >> login;
					if (login == "1") {
						exit(1);
					}
				}
			}
			cout << "user is blocked" << endl;
			users[id][2] = "1";
			WriteFile(users);
			break;
		case 5:
			cout << "Enter username: " << endl;
			cin >> login;
			while (true)
			{
				for (size_t i = 0; i < users.size(); i++)
				{
					if (login == (string)users[i][0]) {
						id = i;
						break;
					}
				}
				break;
				if (id == -1) {
					cout << "No such username" << endl;
					cout << "If you want to exit, press 1" << endl;
					cin >> login;
					if (login == "1") {
						exit(1);
					}
				}
			}
			if (users[id][3] == "0") {
				users[id][3] = "1";
				cout << "password is limited" << endl;
			}
			else {
				users[id][3] = "0";
				cout << "password is unlimited" << endl;
			}
			WriteFile(users);
			break;
		case 6:
			exit(1);
		}
		case 7:
			cout<<"Enter pass phrase"
			cin >> SecPhrase;
			if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0))
			{
				cout << "!CryptAcquireContext" << endl;
				return 1;
			}
			
			if (!CryptGenKey(hProv, CALG_RC4,
				CRYPT_ENCRYPT | CRYPT_DECRYPT, &Key))
			{
				cout << "!CryptGenKey" << endl;
				return 1;
			}
			
			b = text.c_str();
			counts = strlen(b);
			cout << Key << endl;
			if (!CryptEncrypt(Key, 0, true, 0, (BYTE*)b,
				&counts, strlen(b)))
			{
				cout << "!CryptEncrypt" << endl;
				return 1;
			}
			cout << b<<endl;
			ofstream fout;
			fout.open("list.txt", ofstream::out);
			fout << b;
			fout.close();
			cout << "File is enctypted" << endl;
			
			
	case 2:
		cout << "Enter your login" << endl;

		cin >> login;
		while (true)
		{
			for (size_t i = 0; i < users.size(); i++)
			{
				if (login == (string)users[i][0]) {
					id = i;
					if (users[id][2] == "1") {
						cout << "you are blocked" << endl;
						exit(1);
					}
					break;
				}

			}
			if (id == -1) {
				cout << "No such username" << endl;
				cout << "If you want to exit, press 1" << endl;
				cin >> login;
				if (login == "1") {
					exit(1);
				}
			}
			else {
				cout << "Enter your password" << endl;
				cin.ignore(256, '\n');
				getline(cin, pass);
				while (true)
				{
					if (pass == users[id][1]) {
						cout << "OK" << endl;
						break;
					}
					else {
						cout << "incorrect password" << endl;
						cout << "you have " << 3 - attempts << " more attempts" << endl;
						attempts += 1;
						cin.ignore(256, '\n');
						getline(cin, pass);
						if (attempts == 3) {
							id = -1;
							cout << "no more attempts" << endl;
							exit(1);
						}
					}
				}
			}
			cout << "press 1 to change password" << endl;
			cout << "press 2 to exit" << endl;
			cin >> opt;
			switch (opt)
			{
			case 1:
				newpass = ChangePass((int)users[id][3][0] - 48, pass);
				if (pass != newpass) {
					users[id][1] = newpass;
					WriteFile(users);
					exit(1);
				}
			case 2:
				exit(1);
			}
		}
	case 3:
		cout << "Artem Kupriienko" << endl;
		cout << "Pass must contain upper and lowercase letters and operands";
		exit(1);
	case 4:
		exit(1);
	default:
		cout << "something went wrong";
		break;
	}

}


	
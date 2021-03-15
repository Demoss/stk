#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<regex>
using namespace std;
string PATH("list_of_users.txt");

void CreateFile() {
	ofstream fout;
	fout.open(PATH, ofstream::app);
	fout << "ADMIN" << ":" << " " << ":" << "0" << ":" << "0\n" << endl;
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
	cin >> old;
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

int main()
{
	cout << "press 1 to log in as admin" << endl;
	cout << "press 2 to log in as user" << endl;
	cout << "press 3 to get info" << endl;
	cout << "press 4 to exit" << endl;
	int choice = 0;
	cin >> choice;
	string login;
	string pass;
	string isBlocked;
	string isLimited;
	int attempts = 1;
	int opt;
	string newpass = "";
	vector<vector<string>> users = readFile();
	vector<string> NewUser;
	int id = -1;
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
				if (id == -1) {
					cout << "No such username" << endl;
					cout << "If you want to exit, press 1" << endl;
					cin >> login;
					if (login == "1") {
						exit(1);
					}
				}
			}
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
				users[id][3] == "1";
			}
			else {
				users[id][3] == "0";
			}
			WriteFile(users);
			break;
		case 6:
			exit(1);
		}
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


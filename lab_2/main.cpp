#include<iostream>
#include<string>
using namespace std;
void main() {
	string path;
	cin >> path;
	path += "lab_1.cpp";
	string a = "copy C:\\Users\\intet\\source\\repos\\lab_1\\lab_1.cpp " + path;
	const char* b = a.c_str();
	cout << path;
	system(b);

}
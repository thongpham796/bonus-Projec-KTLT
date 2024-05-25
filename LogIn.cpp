#include "Header.h"

void menu()
{
	cout << "What do you want to do ? \n";
	cout << "1. Log in.\n";
	cout << "2. Sign up.\n";
	cout << "Enter number: ";
}

void menu1()
{
	cout << "Who are you ? \n";
	cout << "1. Academic staff member.\n";
	cout << "2. Student.\n";
	cout << "Enter number: ";
}

User inputUser(int x)
{
	User a;
		cout << "User name: ";
		cin >> a.username;
		cout << "Password: ";
		cin >> a.password;
	while (!hasUser(a, x)) {
		cout << "The username or password you entered is invalid, please enter again!" << endl;
		cout << "User name: ";
		cin >> a.username;
		cout << "Password: ";
		cin >> a.password;
	}
	return a;
}

void outputUser(User a)
{
	cout << a.username << " " << a.password << endl;
}


bool hasUser(User a, int x)
{
	ifstream file;
	string userFile;
	if (x == 1)
	{
		userFile = "academicStaffUser.txt";
	}
	else
		userFile = "studentUser.txt";

	file.open(userFile);
	if (!file.is_open()) {
		cout << "File error !\n";
		return false;
	}
	User temp;
	bool hasAccount = false;
	while (file >> temp.username)
	{
		file >> temp.password;
		if (temp.username == a.username && temp.password == a.password)
		{
			hasAccount = true;
			break;
		}
	}
	file.close();
	return hasAccount;
}

void sighUp(int k)
{
	User a;
	cout << "User name: ";
	cin.ignore(1);
	getline(cin, a.username);
	cout << "Password: ";
	getline(cin, a.password);
	string fileName;
	if (k == 1)

	{
		fileName = "academicStaffUser.txt";
	}
	else
		fileName = "studentUser.txt";
	ofstream file;
	file.open(fileName, ios::app);
	if (!file.is_open())
	{
		cout << "File error";
		return;
	}
	file << endl;
	file << a.username << " ";
	file << a.password;
	file.close();
}

void viewProfile(int x) {
	if (x == 1) {
		cout << "----------Student's profile infomation----------" << endl;
		cout <<"No: "<<
	}
}
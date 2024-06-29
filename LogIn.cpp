#include "Header.h"

void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//Khong hien thi con tro
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//Ham tao mau
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
//ham to mau cho mot chuoi
void ToMau(int x, int y, string a, int color) {
	gotoXY(x, y);
	textcolor(color);
	cout << a << endl;
	textcolor(7);
}
void setConsoleSize(int width, int height) {
	// Lấy handle của console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Lấy thông tin hiện tại của console
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// Thiết lập kích thước buffer của console
	SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &rect);

	// Thiết lập kích thước của buffer để tránh thanh cuộn
	COORD coord = { width, height };
	SetConsoleScreenBufferSize(hConsole, coord);
}
void setBackgroudAndText(int code) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, code);
}
void fillFullScreen(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	int consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

	setBackgroudAndText(color);
	for (int i = 0; i < consoleHeight; i++)
	{
		for (int j = 0; j < consoleWidth; j++)
		{
			std::cout << " ";
		}
	}
}
void disableConsoleDragging() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style &= ~WS_THICKFRAME; // Loại bỏ khả năng kéo cửa sổ
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void menu()
{

	cout << "What do you want to do ? \n";
	cout << "1. Log in.\n";
	cout << "2. Sign up.\n";
	cout << "Enter number : ";
}

void menu1()
{
	cout << "Who are you ? \n";
	cout << "1. Academic staff member.\n";
	cout << "2. Student.\n";
	cout << "Enter number: ";
}

//Init linkedlist
void initList(StudentUserList& l) {
	l.pHead = NULL;
}
void initList(AcademicStaffUserList& l) {
	l.pHead = NULL;
}

//Input Users functions
StudentUserNode* inputStudentUser(StudentUserList &list)
{
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	while (hasStudentUser(username, password) == NULL) {
		cout << "The username or password you entered is invalid, please enter again!" << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
	}
	StudentUserNode* tmp = hasStudentUser(username, password);
	addTail(list, tmp);
	return tmp;
}

//void outputUser(int x)
//{
//	cout << a.username << " " << a.password << endl;
//}
////Function to check if student user is in the system (by username and password)
StudentUserNode* hasStudentUser(string username, string password)
{
	ifstream file;
	string userFile = "studentUser.txt";
	file.open(userFile);
	if (!file.is_open()) {
		cout << "File error !\n";
		return NULL;
	}
	StudentUser temp;
	string line;
	string value;
	while (getline(file, temp.username)) {
		getline(file, temp.password);
		getline(file, value);
		temp.student.no = stoi(value);
		getline(file, value);
		temp.student.studentId = stoi(value);
		getline(file, temp.student.socialId);
		getline(file, temp.student.firstName);
		getline(file, temp.student.lastName);
		getline(file, temp.student.gender);
		getline(file, value);
		temp.student.dateOfBirth.day = stoi(value);
		getline(file, value);
		temp.student.dateOfBirth.month = stoi(value);
		getline(file, value);
		temp.student.dateOfBirth.year = stoi(value);
		getline(file, value);
		temp.student.yearNumber = stoi(value);
		getline(file, temp.student.placeOfBirth);
		if (temp.username == username && temp.password == password) {
			file.close();
			return createStudentUserNode(temp);
		}
	}
	return NULL;
}

//Create student user node
StudentUserNode* createStudentUserNode(StudentUser su) {
	StudentUserNode* tmp = new StudentUserNode;
	tmp->su.username = su.username;
	tmp->su.password = su.password;
	tmp->su.student.no = su.student.no;
	tmp->su.student.firstName = su.student.firstName;
	tmp->su.student.lastName = su.student.lastName;
	tmp->su.student.studentId = su.student.studentId;
	tmp->su.student.socialId = su.student.socialId;
	tmp->su.student.gender = su.student.gender;
	tmp->su.student.dateOfBirth.day = su.student.dateOfBirth.day;
	tmp->su.student.dateOfBirth.month = su.student.dateOfBirth.month;
	tmp->su.student.dateOfBirth.year = su.student.dateOfBirth.year;
	tmp->su.student.yearNumber = su.student.yearNumber;
	tmp->su.student.placeOfBirth = su.student.placeOfBirth;
	tmp->pNext = NULL;
	return tmp;
}
//Add student user node to list
void addTail(StudentUserList& sul, StudentUserNode* node) {
	if (sul.pHead == NULL) {
		sul.pHead = node;
	}
	else {
		StudentUserNode* tmp = sul.pHead;
		while (tmp->pNext != NULL) {
			tmp = tmp->pNext;
		}
		tmp->pNext = node;
	}
}
//Function to sign up in the system
void sighUpAsAStudent()
{
	string fileName;
	ofstream writeFile;
	StudentUser s;
	cout << "User name: ";
	cin >> s.username;
	cout << "Password: ";
	cin >> s.password;
	cout << "Enter No: ";
	cin >> s.student.no;
	cout << "Enter student id: ";
	cin >> s.student.studentId;
	cout << "Enter social id: ";
	cin >> s.student.socialId;
	cout << "Enter firstname: ";
	cin.ignore();
	getline(cin,s.student.firstName);
	cout << "Enter lastname: ";
	cin.ignore();
	getline(cin,s.student.lastName);
	cout << "Enter gender: ";
	cin >> s.student.gender;
	cout << "Enter date of birth: " << endl;
	cout << "Enter day: ";
	cin >> s.student.dateOfBirth.day;
	cout << "Enter month: ";
	cin >> s.student.dateOfBirth.month;
	cout << "Enter year: ";
	cin >> s.student.dateOfBirth.year;
	cout << "Enter yearNumber: ";
	cin >> s.student.yearNumber;
	cout << "Enter place of birth: ";
	cin.ignore();
	getline(cin,s.student.placeOfBirth);

	//Add student user to text file
	fileName = "studentUser.txt";
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open())
	{
		cout << "File error!"<<endl;
		return;
	}
	writeFile << s.username << endl << s.password << endl << s.student.no << endl << s.student.studentId << endl << s.student.socialId << endl << s.student.firstName << endl << s.student.lastName << endl << s.student.gender << endl << s.student.dateOfBirth.day << endl << s.student.dateOfBirth.month << endl << s.student.dateOfBirth.year << endl << s.student.yearNumber << endl << s.student.placeOfBirth << "\n";
	writeFile.close();
}
//Function to view user profile
void viewProfile(StudentUser su) {
	cout << "-----------------PROFILE-----------------" << endl;
	cout << "No: " << su.student.no << endl;
	cout << "Student id: " << su.student.studentId << endl;
	cout << "Social id: " << su.student.socialId << endl;
	cout << "Firstname: " << su.student.firstName << endl;
	cout << "Lastname: " << su.student.lastName << endl;
	cout << "Gender: " << su.student.gender << endl;
	cout << "Date of birth: " << su.student.dateOfBirth.day << "/" << su.student.dateOfBirth.month << "/" << su.student.dateOfBirth.year << endl;
	cout << "Year number: " << su.student.yearNumber << endl;
	cout << "Place of birth: " << su.student.placeOfBirth << endl;
}

AcademicStaffUserNode* inputAcademicStaffUser(AcademicStaffUserList& list)
{
	string username, password;
	cout << "User name: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	AcademicStaffUserNode* node = hasAcademicUserNode(username, password);
	while (hasAcademicUserNode(username, password) == NULL) {
		cout << "The username or password you entered is invalid, please enter again!" << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
	}
	addTail(list, node);
	return node;
}

//Function to check if academic staff user is in the system	(by username and password). If  academic staff user is in the system, return true and vice verse
AcademicStaffUserNode* hasAcademicUserNode(string username, string password)
{
	AcademicStaffUser asu;
	ifstream rfile;
	rfile.open("academicStaffUser.txt");
	if (!rfile.is_open()) {
		cout << "File error!" << endl;
		return NULL;
	}
	string value;
	while (getline(rfile, asu.username)) {
		getline(rfile, asu.password);
		getline(rfile, value);
		asu.academicStaff.staffId = stoi(value);
		getline(rfile, asu.academicStaff.socialId);
		getline(rfile, asu.academicStaff.firstName);
		getline(rfile, asu.academicStaff.lastName);
		getline(rfile, asu.academicStaff.gender);
		getline(rfile, value);
		asu.academicStaff.dateOfBirth.day = stoi(value);
		getline(rfile, value);
		asu.academicStaff.dateOfBirth.month = stoi(value);
		getline(rfile, value);
		asu.academicStaff.dateOfBirth.year = stoi(value);
		getline(rfile, asu.academicStaff.placeOfBirth);

		if (asu.username == username && asu.password == password) {
			rfile.close();
			return createAcademicStaffUserNode(asu);
		}
	}
	return NULL;
}

//Create academic staff user node
AcademicStaffUserNode* createAcademicStaffUserNode(AcademicStaffUser asu) {
	AcademicStaffUserNode* tmp = new AcademicStaffUserNode;
	tmp->au.username = asu.username;
	tmp->au.password = asu.password;
	tmp->au.academicStaff.firstName = asu.academicStaff.firstName;
	tmp->au.academicStaff.lastName = asu.academicStaff.lastName;
	tmp->au.academicStaff.socialId = asu.academicStaff.socialId;
	tmp->au.academicStaff.staffId = asu.academicStaff.staffId;
	tmp->au.academicStaff.gender = asu.academicStaff.gender;
	tmp->au.academicStaff.placeOfBirth = asu.academicStaff.placeOfBirth;
	tmp->au.academicStaff.dateOfBirth.day = asu.academicStaff.dateOfBirth.day;
	tmp->au.academicStaff.dateOfBirth.month = asu.academicStaff.dateOfBirth.month;
	tmp->au.academicStaff.dateOfBirth.year = asu.academicStaff.dateOfBirth.year;
	tmp->pNext = NULL;
	return tmp;
}
//Add academic staff user node to list
void addTail(AcademicStaffUserList& asul, AcademicStaffUserNode* node) {
	if (asul.pHead == NULL) {
		asul.pHead = node;
	}
	else {
		AcademicStaffUserNode* tmp = asul.pHead;
		while (tmp->pNext != NULL) {
			tmp = tmp->pNext;
		}
		tmp->pNext = node;
	}
}

void sighUpAsAAcademicStaff() {
	AcademicStaffUser a;
	cout << "User name: ";
	cin >> a.username;
	cout << "Password: ";
	cin >> a.password;
	cout << "Enter staff id: ";
	cin >> a.academicStaff.staffId;
	cout << "Enter social id: ";
	cin >> a.academicStaff.socialId;
	cout << "Enter first name: ";
	cin.ignore();
	getline(cin, a.academicStaff.firstName);
	cout << "Endter last name: ";
	cin.ignore();
	getline(cin, a.academicStaff.lastName);
	cout << "Enter gender: ";
	cin >> a.academicStaff.gender;
	cout << "Enter date of birth: " << endl;
	cout << "Enter day: ";
	cin >> a.academicStaff.dateOfBirth.day;
	cout << "Enter month: ";
	cin >> a.academicStaff.dateOfBirth.month;
	cout << "Enter year: ";
	cin >> a.academicStaff.dateOfBirth.year;
	cout << "Enter place of birth: ";
	cin.ignore();
	getline(cin, a.academicStaff.placeOfBirth);

	//Add academic staff user to text file
	string fileName = "academicStaffUser.txt";
	ofstream writeFile;
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open())
	{
		cout << "File error!" << endl;
		return;
	}
	writeFile << a.username << endl << a.password << endl << a.academicStaff.staffId << endl << a.academicStaff.socialId << endl << a.academicStaff.firstName << endl << a.academicStaff.lastName << endl << a.academicStaff.gender << endl << a.academicStaff.dateOfBirth.day << endl << a.academicStaff.dateOfBirth.month << endl << a.academicStaff.dateOfBirth.year << endl << a.academicStaff.placeOfBirth << endl;
	writeFile.close();
}

//Function to view academic staff user profile
void viewProfile(AcademicStaffUser au) {
	cout << "-----------------PROFILE-----------------" << endl;
	cout << "Staff id: " << au.academicStaff.staffId << endl;
	cout << "Firstname: " << au.academicStaff.firstName << endl;
	cout << "Lastname: " << au.academicStaff.lastName << endl;
	cout << "Gender: " << au.academicStaff.gender << endl;
	cout << "Social id: " << au.academicStaff.socialId << endl;
	cout << "Date of birth: " << au.academicStaff.dateOfBirth.day << "/" << au.academicStaff.dateOfBirth.month << "/" << au.academicStaff.dateOfBirth.year << endl;
}

//Function to change student user password
void changeStudentUserPassword(StudentUserNode* &node, StudentUserList& list) {
	StudentUserNode* tempnode = list.pHead;
	while (tempnode != NULL && node->su.username != tempnode->su.username && node->su.password != tempnode->su.password) {
		tempnode = tempnode->pNext;
	}
	if (tempnode == NULL) {
		cout << "The specified user was not found in the list." << endl;
		return;
	}
	string oldPass, newPass;
	cout << "Enter old password: ";
	cin >> oldPass;
	while (oldPass != tempnode->su.password) {
		cout << "The password you entered is invalid, please try again!" << endl;
		cout << "Enter old password: ";
		cin >> oldPass;
	}
	cout << "Enter new password: ";
	cin >> newPass;
	tempnode->su.password = newPass;
	cout << "Password has been changed to: " << tempnode->su.password << endl;
}

//Function to change academic staff user password
void changeAcademicStaffUserPassword(AcademicStaffUserNode* node, AcademicStaffUserList& list) {
	AcademicStaffUserNode* tempnode = list.pHead;
	while (tempnode != NULL && node->au.username != tempnode->au.username && node->au.password != tempnode->au.password) {
		tempnode = tempnode->pNext;
	}
	if (tempnode == NULL) {
		cout << "The specified user was not found in the list." << endl;
		return;
	}
	string oldPass, newPass;
	cout << "Enter old password: ";
	cin >> oldPass;
	while (oldPass != tempnode->au.password) {
		cout << "The password you entered is invalid, please try again!" << endl;
		cout << "Enter old password: ";
		cin >> oldPass;
	}
	cout << "Enter new password: ";
	cin >> newPass;
	tempnode->au.password = newPass;
	cout << "Password has been changed to: " << tempnode->au.password << endl;
}
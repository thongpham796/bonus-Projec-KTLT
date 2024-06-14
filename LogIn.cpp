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

//Init linkedlist
void initList(StudentUserList& l) {
	l.pHead = NULL;
}
void initList(AcademicStaffUserList& l) {
	l.pHead = NULL;
}

//Input Users functions
StudentUser inputStudentUser(StudentUserList l)
{
	StudentUserNode* node = new StudentUserNode;
	cout << "User name: ";
	cin >> node->su.username;
	cout << "Password: ";
	cin >> node->su.password;
	StudentUserNode* tmp = hasStudentUser(l, node);
	while (tmp == NULL) {
		cout << "The username or password you entered is invalid, please enter again!" << endl;
		cout << "User name: ";
		cin >> node->su.username;
		cout << "Password: ";
		cin >> node->su.password;
	}
	return tmp->su;
}

//void outputUser(int x)
//{
//	cout << a.username << " " << a.password << endl;
//}
////Function to check if student user is in the system (by username and password)
StudentUserNode* hasStudentUser(StudentUserList sul, StudentUserNode* node)
{
	if (sul.pHead == NULL) return NULL;
	ifstream file;
	string userFile;
	userFile = "studentUser.txt";
	file.open(userFile);
	if (!file.is_open()) {
		cout << "File error !\n";
		return NULL;
	}
	StudentUser temp;
	while (file >> temp.username)
	{
		file >> temp.password;
		StudentUserNode* tmp = sul.pHead;
		while (tmp != NULL) {
			if (tmp->su.username == temp.username && tmp->su.password == temp.password) {
				file.close();
				return createStudentUserNode(tmp->su);

			}
			tmp = tmp->pNext;
		}
	}
	return NULL;
}

AcademicStaffUserNode* inputAcademicStaffUser(AcademicStaffUserList asul)
{
	AcademicStaffUserNode* node = new AcademicStaffUserNode;
	cout << "User name: ";
	cin >> node->au.username;
	cout << "Password: ";
	cin >> node->au.password;
	while (hasAcademicUserNode(asul, node) == NULL) {
		cout << "The username or password you entered is invalid, please enter again!" << endl;
		cout << "Username: ";
		cin >> node->au.username;
		cout << "Password: ";
		cin >> node->au.password;
	}
	node = hasAcademicUserNode(asul, node);
	return node;
}

//Function to check if academic staff user is in the system	(by username and password). If  academic staff user is in the system, return true and vice verse
AcademicStaffUserNode* hasAcademicUserNode(AcademicStaffUserList asul, AcademicStaffUserNode* node)
{
	AcademicStaffUserNode* tmp = asul.pHead;
	while (tmp != NULL) {
		if (tmp->au.username == node->au.username && tmp->au.password == node->au.password) {
			return createAcademicStaffUserNode(tmp->au);
		}
		tmp = tmp->pNext;
	}
	return NULL;
}

//Create student user node
StudentUserNode* createStudentUserNode(StudentUser su) {
	StudentUserNode* tmp = new StudentUserNode;
	tmp->su.username = su.username;
	tmp->su.password = su.password;
	tmp->su.student.firstName = su.student.firstName;
	tmp->su.student.lastName = su.student.lastName;
	tmp->su.student.socialId = su.student.socialId;
	tmp->su.student.studentId = su.student.studentId;
	tmp->su.student.gender = su.student.gender;
	tmp->su.student.yearNumber = su.student.yearNumber;
	tmp->su.student.placeOfBirth = su.student.placeOfBirth;
	tmp->su.student.dateOfBirth.day = su.student.dateOfBirth.day;
	tmp->su.student.dateOfBirth.month = su.student.dateOfBirth.month;
	tmp->su.student.dateOfBirth.year = su.student.dateOfBirth.year;
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
StudentUserNode* sighUpAsAStudent(StudentUserList &sul)
{
	string fileName;
	ofstream writeFile;
	StudentUser s;
	cout << "User name: ";
	cin.ignore(1);
	getline(cin, s.username);
	cout << "Password: ";
	getline(cin, s.password);
	cout << "Enter No: ";
	cin >> s.student.no;
	cout << "Enter student id: ";
	cin >> s.student.studentId;
	cout << "Enter firstname: ";
	cin >> s.student.firstName;
	cout << "Enter lastname: ";
	cin >> s.student.lastName;
	cout << "Enter gender: ";
	cin >> s.student.gender;
	cout << "Enter date of birth: " << endl;
	cout << "Enter day: ";
	cin >> s.student.dateOfBirth.day;
	cout << "Enter month: ";
	cin >> s.student.dateOfBirth.month;
	cout << "Enter year: ";
	cin >> s.student.dateOfBirth.year;

	//Add student node to student list
	StudentUserNode* node = createStudentUserNode(s);
	if (node == NULL) {
		cout << "Can't create student user node!!" << endl;
		return NULL;
	}
	addTail(sul, node);

	//Add student user to text file
	fileName = "studentUser.txt";
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open())
	{
		cout << "File error!"<<endl;
		return node;
	}
	writeFile << endl;
	writeFile << s.username << " " << s.password;
	//write username and password to text file
	writeFile.close();
	return node;
}
//Function to view user profile
void viewProfile(StudentUser su) {
	cout << "-----------------PROFILE-----------------" << endl;
	cout << "No: " << su.student.no << endl;
	cout << "Student id: " << su.student.studentId << endl;
	cout << "Firstname: " << su.student.firstName << endl;
	cout << "Lastname: " << su.student.lastName << endl;
	cout << "Gender: " << su.student.gender << endl;
	cout << "Date of birth: " << su.student.dateOfBirth.day << "/" << su.student.dateOfBirth.month << "/" << su.student.dateOfBirth.year << endl;
	cout << "Year number: " << su.student.yearNumber << endl;
	cout << "Social id: " << su.student.socialId << endl;
	cout << "Date of birth: " << su.student.dateOfBirth.day << "/" << su.student.dateOfBirth.month << "/" << su.student.dateOfBirth.year << endl;
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
void addTail(AcademicStaffUserList& asul, AcademicStaffUserNode* &node) {
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

AcademicStaffUserNode* sighUpAsAAcademicStaff(AcademicStaffUserList& asul) {
	AcademicStaffUser a;
	cout << "User name: ";
	cin.ignore(1);
	getline(cin, a.username);
	cout << "Password: ";
	getline(cin, a.password);
	cout << "Enter staff id: ";
	cin >> a.academicStaff.staffId;
	cout << "Enter social id: ";
	cin >> a.academicStaff.socialId;
	cout << "Enter first name: ";
	cin >> a.academicStaff.firstName;
	cout << "Endter last name: ";
	cin >> a.academicStaff.lastName;
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
	cin.ignore(1);
	getline(cin,a.academicStaff.placeOfBirth);
	
	//Add academic staff user node to list
	AcademicStaffUserNode* node = createAcademicStaffUserNode(a);
	if (node == NULL) {
		cout << "Can't create academic staff user node!!" << endl;
		return NULL;
	}
	addTail(asul, node);

	string fileName;
	ofstream writeFile;
	fileName = "academicStaffUser.txt";
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open())
	{
		cout << "File error";
		return node;
	}
	writeFile << endl;
	writeFile << a.username << " " << a.password;
	writeFile.close();
	return node;
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
void changeStudentUserPassword(StudentUserNode* &node) {
	string oldPass, newPass;
	cout << "Enter old password: ";
	cin >> oldPass;
	while (oldPass != node->su.password) {
		cout << "The password you entered is invalid, please try again!" << endl;
		cout << "Enter old password: ";
		cin >> oldPass;
	}
	cout << "Enter new password: ";
	cin >> newPass;
	node->su.password = newPass;
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


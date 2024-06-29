#ifndef Header_h
#define Header_h

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
// Mã ANSI cho nền trắng
#define WHITE_BG "\033[47m"
// Mã ANSI cho chữ xanh
#define BLUE_TEXT "\033[34m"
using namespace std;

void gotoXY(int x, int y);
void ShowCur(bool CursorVisibility);
void textcolor(int x);
void ToMau(int x, int y, string a, int color);
void setConsoleSize(int width, int height);
void setBackgroudAndText(int code);
void fillFullScreen(int color);
void disableConsoleDragging();

void menu();
void menu1();

struct Date {
	int day, month, year;
};
struct Student {
	int no;
	int studentId;
	string socialId;
	string firstName;
	string lastName;
	string gender;
	Date dateOfBirth;
	int yearNumber; // 1st-year students, 2st-year student,...
	string placeOfBirth;
};
struct StudentUser
{
	Student student;
	string username;
	string password;
};
struct StudentUserNode {
	StudentUser su;
	StudentUserNode* pNext;
};
//Create a list of Student users
struct StudentUserList {
	StudentUserNode* pHead;
};

struct AcademicStaff {
	int staffId;
	string firstName;
	string lastName;
	string gender;
	Date dateOfBirth;
	string socialId;
	string placeOfBirth;
};
struct AcademicStaffUser {
	AcademicStaff academicStaff;
	string username;
	string password;

};
struct AcademicStaffUserNode {
	AcademicStaffUser au;
	AcademicStaffUserNode* pNext;
};
//Create a list of Academic staff users
struct AcademicStaffUserList {
	AcademicStaffUserNode* pHead;
};

struct Classes {
	int numOfStudent;
	Student *student;
	string className;
	int yearNumber; // 1st-year students, 2st-year student,...
};
struct Session {
	string dayOfWeek; // Ex: MON, TUE,...
	string classPeriod;	//Ex: S1(7:30), S2(9:30),...
};

//Log in and sign up
void initList(StudentUserList& l);
void initList(AcademicStaffUserList& l);

StudentUserNode* inputStudentUser(StudentUserList &list);
StudentUserNode* hasStudentUser(string username, string password);
StudentUserNode* createStudentUserNode(StudentUser su);
void addTail(StudentUserList& sul, StudentUserNode* node);
void sighUpAsAStudent();
void viewProfile(StudentUser su);

AcademicStaffUserNode* inputAcademicStaffUser(AcademicStaffUserList& list);
AcademicStaffUserNode* hasAcademicUserNode(string username, string password);
AcademicStaffUserNode* createAcademicStaffUserNode(AcademicStaffUser asu);
void addTail(AcademicStaffUserList& asul, AcademicStaffUserNode* node);
void sighUpAsAAcademicStaff();
void viewProfile(AcademicStaffUser au);

void changeStudentUserPassword(StudentUserNode*& node, StudentUserList& list);
void changeAcademicStaffUserPassword(AcademicStaffUserNode* node, AcademicStaffUserList& list);

//Create scoreboard of a student
struct Point {
	Student s;
	double homework;
	double midterm;
	double final;
	double total = homework * 20 / 100 + midterm * 30 / 100 + final * 50 / 100;
};


//Create list of courses
struct Course {
	int courseId;
	string courseName;
	string className;
	string teacherName;
	int numberOfCredit;
	int maximumNumberOfStudent = 50;
	int dayOfWeek;
	Session session;
	int numOfStudent;
	Student* student;
	Point* scoreboard;
};
struct Node {
	Course course;
	Node* pNext;
};
struct List {
	Node* pHead;
};
struct Semester {
	int semOrdiNum; // semester ordinal number
	string schoolYear;
	Date startDate;
	Date endDate;
	List listOfCourse;
};

struct SchoolYear {
	string nameOfSY;
	List semesters;
};

// Log in system:
// hàm menu hỏi quyền hạn của người dùng
// file chứa tên đăng nhập và mật khẩu sẵn (txt), 1 hàm để đọc file txt, 1 hàm để so với các tên đăng nhập và mật khẩu đã có
// Register system (tạo tài khoản mới và lưu về trong file)

// Stuct class: class name, *student,sĩ số
// Tạo struct student bao gồm: No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
// Student sẽ xuất như sau: 
// 1 hàm để đọc dữ liệu trong csv

string createSchoolYear();
void createSeveralClasses(Classes*& cls, int& numOfClasses);
void addStudentToCSVFile(const char* fileName, Student st);
void addNewStudentToClasses();
void addStudentToClassesFromCsvFile(const char* filename, Classes* cls, int numOfClasses);

Semester createSemester();
Node* createNode();
void addAfterCourseList(List& lst, Node* node);
void addCourseToSemester(Semester& sem);

void uploadCSVFileContainingListStudentInCourse(const char fileName[], Course course);
void addStudentToCourse(Course& course);

void viewListOfClass(Classes* cls, int numOfClass);
void viewStudentOfClass(Classes cls);

void exportListOfStudentsInCourseToCSVFile(const char fileName[], List listOfCourses);
void importScoreboard(const char* file, List*& listofcourse);
void viewScoreboard(Course course);

#endif
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

//Create scoreboard of a student
struct Point {
	Student s;
	double homework;
	double midterm;
	double final;
	double total;
};

//Create list of courses
struct Course {
	string courseId;
	string courseName;
	string className;
	string teacherName;
	int numberOfCredit;
	int maximumNumberOfStudent = 50;
	string dayOfWeek;
	Session session;
	int numOfStudent = 0;
	Point* scoreboard = NULL;
};
struct CourseNode {
	Course course;
	CourseNode* pNext;
};
struct CourseList {
	CourseNode* pHead;
};
struct Semester {
	int semOrdiNum; // semester ordinal number
	string schoolYear;
	Date startDate;
	Date endDate;
	CourseList listOfCourse;
};

void initList(StudentUserList& l);
void initList(AcademicStaffUserList& l);

StudentUserNode* inputStudentUser(StudentUserList& list);
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

struct SchoolYear {
	string nameOfSY;
	CourseList semesters;
};

// Log in system:
// hàm menu hỏi quyền hạn của người dùng
// file chứa tên đăng nhập và mật khẩu sẵn (txt), 1 hàm để đọc file txt, 1 hàm để so với các tên đăng nhập và mật khẩu đã có
// Register system (tạo tài khoản mới và lưu về trong file)

// Stuct class: class name, *student,sĩ số
// Tạo struct student bao gồm: No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
// Student sẽ xuất như sau: 
// 1 hàm để đọc dữ liệu trong csv

//At the beginning of a school year (often in September)
string createSchoolYear(); //1
void createSeveralClasses(Classes*& cls, int& numOfClasses);//2
void addStudentToCSVFile(const char* fileName, Student st);
void addNewStudentToClasses(const char* fileName);//3
void addStudentToClassesFromCsvFile(const char* filename, Classes* cls, int numOfClasses);//4

//At the beginning of a semester, an academic staff member can:
Semester createSemester();//6
CourseNode* createCourseNode();
void addAfterCourseList(CourseList& lst, CourseNode* node);
void addCourseToSemester(Semester& sem);//7
void uploadCSVFileContainingListStudentInCourse(const char fileName[], CourseList& course);//8
void viewListOfCourse(CourseList listOfCourse);//9
void updateCourseInfo(CourseList& listOfCourse);//10
void addStudentToCourse(CourseList& listOfCourse);//11
void removeStudentFromStudentArr(Point*& scoreboard, int& n, int pos);
void removeStudentFromCourse(CourseList& listOfCourse);//12
void deleteACourse(CourseList& listOfCourse);//13

//In a semester, a student still can:
void viewListOfCourseByStudent(CourseList courseList, int id);//14

//At any time, an academic staff member can:
void viewListOfClasses(Classes* cls, int numOfClass);//15
void viewStudentOfClass(Classes cls);//16
void viewListOfCourse(const char fileName[], CourseList courseList);//17
void viewListOfStudentInCourse(CourseList courseList);//18

//At the end of a semester
void exportListOfStudentsInCourseToCSVFile(CourseList listOfCourse, string id);//19
void importScoreboard(string cid, CourseList& listOfCourse);//20
void viewScoreboard(Course course);//21
void updateResult(CourseList& List);//22
double findGPAOfAStudent(int MSSV, Semester sem);
void findGPAOfClass(Classes* cls, int numOfClass, Semester sem);//23
void viewScoreboard(StudentUserNode* sun, Semester sem);//24
#endif
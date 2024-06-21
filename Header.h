#ifndef Header_h
#define Header_h

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

void menu();
void menu1();
struct User
{
	string username;
	string password;
};

struct Date {
	int day, month, year;
};
struct AcademicStaff {
	int staffId;
	string firstName;
	string lastName;
	string gender;
	Date dateOfBirth;
	string socialId;
};
struct Student {
	int no;
	int studentId;
	string firstName;
	string lastName;
	string gender;
	Date dateOfBirth;
	string socialId;
	int yearNumber; // 1st-year students, 2st-year student,...
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
	double total = homework * 20 / 100 + midterm * 30 / 100 + final * 50 / 100;
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
	Point *scoreboard = NULL;
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

User inputUser(int x);
bool hasUser(User a, int x);
void outputUser(User a);
void sighUp(int k);
void viewProfile(User a);

// Log in system:
// hàm menu hỏi quyền hạn của người dùng
// file chứa tên đăng nhập và mật khẩu sẵn (txt), 1 hàm để đọc file txt, 1 hàm để so với các tên đăng nhập và mật khẩu đã có
// Register system (tạo tài khoản mới và lưu về trong file)

// Stuct class: class name, *student,sĩ số
// Tạo struct student bao gồm: No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
// Student sẽ xuất như sau: 
// 1 hàm để đọc dữ liệu trong csv

//At the beginning of a school year (often in September)
string createSchoolYear();
void createSeveralClasses(Classes*& cls, int& numOfClasses);
void addStudentToCSVFile(const char* fileName, Student st);
void addNewStudentToClasses();
void addStudentToClassesFromCsvFile(const char* filename, Classes* cls, int numOfClasses);

//At the beginning of a semester
Semester createSemester();
CourseNode* createCourseNode();
void addAfterCourseList(CourseList& lst, CourseNode* node);
void addCourseToSemester(Semester& sem);

void uploadCSVFileContainingListStudentInCourse(const char fileName[], Course course);
void viewListOfCourse(CourseList listOfCourse);
void addStudentToCourse(CourseList& listOfCourse);
void updateCourseInfo(CourseList& listOfCourse);
void removeStudentFromStudentArr(Point*& scoreboard, int n, int pos);
void removeStudentFromCourse(CourseList& listOfCourse);
void deleteACourse(CourseList& listOfCourse);

void viewListOfClass(Classes* cls, int numOfClass);
void viewStudentOfClass(Classes cls);

//At the end of a semester
void exportListOfStudentToCsvFile(const char* file, Course course);
void importScoreboard(const char* file, CourseList& listofcourse);
void viewScoreboard(Course course);

#endif
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

struct Date {
	int day, month, year;
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

StudentUser inputStudentUser(StudentUserList l);
StudentUserNode* hasStudentUser(StudentUserList sul, StudentUserNode* node);

AcademicStaffUserNode* inputAcademicStaffUser(AcademicStaffUserList asul);
AcademicStaffUserNode* hasAcademicUserNode(AcademicStaffUserList asul, AcademicStaffUserNode* a);
StudentUserNode* createStudentUserNode(StudentUser su);
void addTail(StudentUserList& sul, StudentUserNode* node);
StudentUserNode* sighUpAsAStudent(StudentUserList& sul);
void viewProfile(StudentUser su);

AcademicStaffUserNode* createAcademicStaffUserNode(AcademicStaffUser asu);
void addTail(AcademicStaffUserList& asul, AcademicStaffUserNode* &node);
AcademicStaffUserNode* sighUpAsAAcademicStaff(AcademicStaffUserList& asul);
void viewProfile(AcademicStaffUser au);

void changeStudentUserPassword(StudentUserNode*& node);
void changeAcademicStaffUserPassword(AcademicStaffUserNode* node, AcademicStaffUserList& list);

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
	int dayOfWeek;
	Session session;
	int numOfStudent;
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

void exportListOfStudentToCsvFile(const char* file, Course course);
void importScoreboard(const char* file, List*& listofcourse);
void viewScoreboard(Course course);
void updateResult(Point& s);

#endif
#include "Header.h"

// 1. Create a school year (2020-2021, for example)
string createSchoolYear() {
	string s = "";
	int start, end;
	cout << "The start of school year (Ex: 2020,...): ";
	cin >> start;
	cout << "The end of school year (Ex: 2021,...): ";
	cin >> end;
	s = to_string(start) + "-" + to_string(end);
	return s;
}

//2. Create several classes for 1st-year students. For example: class 20APCS1, class 20APCS2,
//class 20CLC1..., class 20CLC11, class 20VP...
void createSeveralClasses(Classes*& cls, int& numOfClasses) {
	cout << "The number of several classes for 1st-year students you want to create: ";
	cin >> numOfClasses;
	cls = new Classes[numOfClasses];
	for (int i = 0; i < numOfClasses; i++) {
		cout << "The classes " << i + 1 << " is: ";
		cin >> cls[i].className;
		cls[i].numOfStudent = 0;
		cls[i].yearNumber = 1;
	}
}

//3. Add new 1st year students to 1st-year classes.
void addStudentToCSVFile(const char* fileName, Student st) {
	ofstream writeFile;
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open()) {
		cout << "File \"" << fileName << " \" error!" << endl;
		return;
	}
	cout << "Enter student: " << endl;
	cout << "Enter No: ";
	cin >> st.no;
	cout << "Enter Student ID: ";
	cin >> st.studentId;
	cout << "Enter Firstname: ";
	cin.ignore();
	getline(cin,st.firstName);
	cout << "Enter Lastname: ";
	cin.ignore();
	getline(cin, st.lastName);
	cout << "Enter Gender: ";
	cin >> st.gender;
	cout << "Enter Date of Birth: " << endl;
	cout << "Day: ";
	cin >> st.dateOfBirth.day;
	cout << "Month: ";
	cin >> st.dateOfBirth.month;
	cout << "Year: ";
	cin >> st.dateOfBirth.year;
	cout << "Enter Social Id: ";
	cin >> st.socialId;
	st.yearNumber = 1;

	writeFile << st.no << "," << st.studentId << "," << st.firstName << "," << st.lastName << "," << st.gender << "," << st.dateOfBirth.day << "," << st.dateOfBirth.month << "," << st.dateOfBirth.year << "," << st.socialId << "," << st.yearNumber << endl;
	writeFile.close();
}
void addNewStudentToClasses(const char* fileName) {
	Student st;
	addStudentToCSVFile(fileName, st);
}

// 4. Add student from csv file:
void addStudentToClassesFromCsvFile(const char* filename, Classes* cls, int numOfClasses)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
	{
		cout << "File error !!" << endl;
		return;
	}
	string temp;
	getline(file, temp);
	stringstream linetemp(temp);
	string classtemp;
	getline(linetemp, classtemp, ',');
	int numOfStudent;
	string num;
	getline(linetemp, num, ',');
	numOfStudent = stoi(num);
	int i = 0;
	while (i < numOfClasses)
	{
		if (cls[i].className == classtemp)
		{
			cls[i].student = new Student[numOfStudent];
			string line;
			int j = 0;
			while (getline(file, line))
			{
				stringstream linestream(line);
				string value;
				getline(linestream, value, ',');
				cls[i].student[j].no = stoi(value);
				getline(linestream, value, ',');
				cls[i].student[j].studentId = stoi(value);
				getline(linestream, value, ',');
				cls[i].student[j].firstName = value;
				getline(linestream, value, ',');
				cls[i].student[j].lastName = value;
				getline(linestream, value, ',');
				cls[i].student[j].gender = value;
				getline(linestream, value, ',');
				cls[i].student[j].dateOfBirth.day = stoi(value);
				getline(linestream, value, ',');
				cls[i].student[j].dateOfBirth.month = stoi(value);
				getline(linestream, value, ',');
				cls[i].student[j].dateOfBirth.year = stoi(value);
				getline(linestream, value, ',');
				cls[i].student[j].socialId = value;
				getline(linestream, value, ' ');
				cls[i].student[j].yearNumber = stoi(value);
				j++;
			}
			cls[i].numOfStudent = j;
			file.close();
			cout << "Write file successful!!" << endl;
			return;
		}
		i++;
	}
	cout << "The class doesn't exist!!" << endl;
	file.close();
	return;
}


// 6. Create a semester: 1, 2, or 3, school year, start date, end date. Choose the school year
// that the newly created semester belongs to.The created semester will be the current /
// default semester for all the below actions.
Semester createSemester() {
	Semester sem;
	cout << "Enter the semester ordinal number: ";
	cin >> sem.semOrdiNum;
	cout << "Enter school year: ";
	cin >> sem.schoolYear;
	cout << "Enter start date: " << endl;
	cout << "Day: ";
	cin >> sem.startDate.day;
	cout << "Month: ";
	cin >> sem.startDate.month;
	cout << "Year: ";
	cin >> sem.startDate.year;
	cout << "Enter end date: " << endl;
	cout << "Day: ";
	cin >> sem.endDate.day;
	cout << "Month: ";
	cin >> sem.endDate.month;
	cout << "Year: ";
	cin >> sem.endDate.year;
	sem.listOfCourse.pHead = NULL;
	return sem;
}


//7. Add a course to this semester: course id, course name, class name, teacher name,
//number of credits, the maximum number of students in the course(default 50), day of
//the week, and the session that the course will be performed(MON / TUE / WED / THU /
//	FRI / SAT, S1(07:30), S2(09:30), S3(13:30) and S4(15:30)).A course will be taught in
//	only one session in a week.
CourseNode* createCourseNode() {
	CourseNode* tmp = new CourseNode;
	Course crs;
	cout << "Course id: ";
	cin >> crs.courseId;
	cout << "Course name: ";
	cin >> crs.courseName;
	cout << "Class name: ";
	cin >> crs.className;
	cout << "Teacher name: ";
	cin.ignore();
	getline(cin,crs.teacherName);
	cout << "Number of credits: ";
	cin >> crs.numberOfCredit;
	cout << "The maximum number of students in course: ";
	cin >> crs.maximumNumberOfStudent;
	cout << "Day of the week: ";
	cin >> crs.dayOfWeek;
	cout << "The session that the course will be performed: " << endl;
	cout << "Day of the week the course will be performed (Ex: MON, TUE,...): ";
	cin >> crs.session.dayOfWeek;
	cout << "Class period the course will be performed (Ex: S1, S2,...): ";
	cin >> crs.session.classPeriod;

	crs.numOfStudent = 0;
	crs.scoreboard = NULL;

	tmp->course = crs;
	tmp->pNext = NULL;
	return tmp;
}

void addAfterCourseList(CourseList& lst, CourseNode* node) {
	if (lst.pHead == NULL) {
		lst.pHead = node;
	}
	else {
		CourseNode* tmp = lst.pHead;
		while (tmp->pNext != NULL) {
			tmp = tmp->pNext;
		}
		tmp->pNext = node;
	}
}

void addCourseToSemester(Semester& sem) {
	cout << "Enter a new course to semester: " << endl;
	CourseNode* node = createCourseNode();
	if (sem.listOfCourse.pHead == NULL) {
		sem.listOfCourse.pHead = node;
	}
	else {
		CourseNode* tmp = sem.listOfCourse.pHead;
		while (tmp != NULL) {
			if ((tmp->course.session.dayOfWeek == node->course.session.dayOfWeek) && (tmp->course.session.classPeriod == node->course.session.classPeriod)) {
				cout << "The session of the course you want to add is a duplicate of the session of the other course in the semester!!!" << endl;
				cout << "Enter a other new course to semester: " << endl;
				node = createCourseNode();
				tmp = sem.listOfCourse.pHead;
			}
			else {
				tmp = tmp->pNext;
			}
		}
		addAfterCourseList(sem.listOfCourse, node);
	}

	cout << "The course is successfully added to the semester!" << endl;
}

//8. Then he/she will upload a CSV file, containing a list of students enrolled in the course.
void uploadCSVFileContainingListStudentInCourse(const char fileName[], Course course) {
	ofstream writeFile;
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open()) {
		cout << "File \"" << fileName << " \" error!" << endl;
		return;
	}
	writeFile << course.numOfStudent << endl;
	for (int i = 0; i < course.numOfStudent; i++) {
		writeFile << course.scoreboard[i].s.no << "," << course.scoreboard[i].s.studentId << "," << course.scoreboard[i].s.firstName << "," << course.scoreboard[i].s.lastName << "," << course.scoreboard[i].s.gender << "," << course.scoreboard[i].s.dateOfBirth.day << "/" << course.scoreboard[i].s.dateOfBirth.month << "/" << course.scoreboard[i].s.dateOfBirth.year << "," << course.scoreboard[i].s.socialId << "," << course.scoreboard[i].s.yearNumber << endl;
		cout << course.scoreboard[i].s.no << "," << course.scoreboard[i].s.studentId << "," << course.scoreboard[i].s.firstName << "," << course.scoreboard[i].s.lastName << "," << course.scoreboard[i].s.gender << "," << course.scoreboard[i].s.dateOfBirth.day << "/" << course.scoreboard[i].s.dateOfBirth.month << "/" << course.scoreboard[i].s.dateOfBirth.year << "," << course.scoreboard[i].s.socialId << "," << course.scoreboard[i].s.yearNumber << endl;
	}
	writeFile.close();
}

//9. View list of course
void viewListOfCourse(CourseList listOfCourse) {
	if (listOfCourse.pHead == NULL) {
		cout << "The course list in this semester is empty!" << endl;
		return;
	}
	else {
		cout << "List of course in this semester: " << endl;
		CourseNode* tmp = listOfCourse.pHead;
		while (tmp != NULL) {
			cout << "Course name: " << tmp->course.courseName << endl;
			cout << "Course id: " << tmp->course.courseId << endl;
			cout << "Class name: " << tmp->course.className << endl;
			cout << "Teacher name: " << tmp->course.teacherName << endl;
			cout << "Number of credit: " << tmp->course.numberOfCredit << endl;
			cout << "The maximum number of students in the course: " << tmp->course.maximumNumberOfStudent << endl;
			cout << "Day of the week: " << tmp->course.dayOfWeek << endl;
			cout << "The session that the course will be perform: " << tmp->course.session.dayOfWeek << " - " << tmp->course.session.classPeriod << endl;
			cout << endl;
			tmp = tmp->pNext;
		}
	}


}

//10. Update course information
void updateCourseInfo(CourseList& listOfCourse) {
	string id;

	cout << "Enter the course id of the course you want to update information: ";
	cin >> id;
	CourseNode* tmp = listOfCourse.pHead;
	while (tmp != NULL) {
		if (tmp->course.courseId == id) {
			while (1) {
				int choice;
				cout << "Which information do you want to update?" << endl;
				cout << "1. Course name." << endl;
				cout << "2. Course id." << endl;
				cout << "3. Class name." << endl;
				cout << "4. Teacher name." << endl;
				cout << "5. Number of credit. " << endl;
				cout << "6. Maximum number of students in the course." << endl;
				cout << "7. Day of the week." << endl;
				cout << "8. The session that the course will be perform." << endl;
				cout << "9. Exit." << endl;
				cout << "Enter number: ";
				cin >> choice;
				if (choice == 1) {
					cout << "The new course name: ";
					cin >> tmp->course.courseName;
					continue;
				}
				else if (choice == 2) {
					cout << "The new course id: ";
					cin >> tmp->course.courseId;
					continue;
				}
				else if (choice == 3) {
					cout << "The new class name: ";
					cin >> tmp->course.className;
					continue;
				}
				else if (choice == 4) {
					cout << "The new teacher name: ";
					cin >> tmp->course.teacherName;
					continue;
				}
				else if (choice == 5) {
					cout << "The new number of credit: ";
					cin >> tmp->course.numberOfCredit;
					continue;
				}
				else if (choice == 6) {
					cout << "The new maximum number of student: ";
					cin >> tmp->course.maximumNumberOfStudent;
					continue;
				}
				else if (choice == 7) {
					cout << "The new day of the week: ";
					cin >> tmp->course.dayOfWeek;
					continue;
				}
				else if (choice == 8) {
					cout << "The new session: ";
					cout << "Day of week: ";
					cin >> tmp->course.session.dayOfWeek;
					cout << "Class Period: ";
					cin >> tmp->course.session.classPeriod;
					continue;
				}
				else if (choice == 9) {
					break;
				}
				else {
					cout << "Our program doesn't support this option, please try again\n";
					continue;
				}
			}
			break;
		}
		tmp = tmp->pNext;
	}
}


//11. Add a student to the course.
void addStudentToCourse(CourseList& listOfCourse) {
	if (listOfCourse.pHead == NULL) {
		cout << "The course you want to add student is not exist!!!";
		return;
	}
	string id;
	cout << "Enter the course id of the course you want to add student: ";
	cin >> id;
	Student st;
	cout << "Enter student infomation: " << endl;
	cout << "Enter No: ";
	cin >> st.no;
	cout << "Enter Student ID: ";
	cin >> st.studentId;
	cout << "Enter Firstname: ";
	cin.ignore();
	getline(cin,st.firstName);
	cout << "Enter Lastname: ";
	cin.ignore(0);
	getline(cin,st.lastName);
	cout << "Enter Gender: ";
	cin >> st.gender;
	cout << "Enter Date of Birth: " << endl;
	cout << "Day: ";
	cin >> st.dateOfBirth.day;
	cout << "Month: ";
	cin >> st.dateOfBirth.month;
	cout << "Year: ";
	cin >> st.dateOfBirth.year;
	cout << "Enter Social Id: ";
	cin >> st.socialId;
	cout << "Enter yearNumber: ";
	cin >> st.yearNumber;
	CourseNode* tmp = listOfCourse.pHead;
	while (tmp != NULL) {
		if (tmp->course.courseId == id) {
			if (tmp->course.scoreboard == NULL) {
				tmp->course.scoreboard = new Point[1];
				tmp->course.scoreboard[0].s = st;
				tmp->course.numOfStudent++;
			}
			else {
				int n = tmp->course.numOfStudent + 1;
				Student* tmpStu = new Student[n];
				for (int i = 0; i < n - 1; i++) {
					tmpStu[i] = tmp->course.scoreboard[i].s;
				}
				tmpStu[n - 1] = st;
				tmp->course.numOfStudent++;
				tmp->course.scoreboard = new Point[tmp->course.numOfStudent];
				for (int i = 0; i < tmp->course.numOfStudent; i++) {
					tmp->course.scoreboard[i].s = tmpStu[i];
				}
			}
			return;
		}
		tmp = tmp->pNext;
	}
	cout << "The course you want to add student is not exist!" << endl;
}

//12. Remove a student from a course with position users enter
void removeStudentFromStudentArr(Point*& scoreboard, int& n, int pos) {
	for (int i = 0; i < n; i++) {
		if (i == pos) {
			for (int j = i; j < n - 1; j++) {
				scoreboard[j] = scoreboard[j + 1];
			}
			n--;
		}
	}
}
void removeStudentFromCourse(CourseList& listOfCourse) {
	string crsId;
	cout << "Enter the course id of the course you want to remove student: ";
	cin >> crsId;
	CourseNode* tmp = listOfCourse.pHead;
	while (tmp != NULL) {
		if (tmp->course.courseId == crsId) {
			int stId;
			cout << "Enter the student id of the student you want to remove from a course: ";
			cin >> stId;
			for (int i = 0; i < tmp->course.numOfStudent; i++) {
				if (tmp->course.scoreboard[i].s.studentId == stId) {
					removeStudentFromStudentArr(tmp->course.scoreboard, tmp->course.numOfStudent, stId);
				}
			}
		}
		tmp = tmp->pNext;
	}
}

//13. Delete a course.
void deleteACourse(CourseList& listOfCourse) {

	if (listOfCourse.pHead == NULL) {
		cout << "This course list is empty!" << endl;
		return;
	}
	string id;
	cout << "Enter the course id of the course you want to delete: ";
	cin >> id;
	if (listOfCourse.pHead->course.courseId == id) {
		CourseNode* tmp = listOfCourse.pHead;
		listOfCourse.pHead = listOfCourse.pHead->pNext;
		delete tmp;
		tmp = NULL;
	}
	else {
		CourseNode* prev = listOfCourse.pHead;
		CourseNode* tmp = listOfCourse.pHead->pNext;
		while (tmp != NULL) {
			if (tmp->course.courseId == id) {
				prev->pNext = tmp->pNext;
				delete tmp;
				tmp = NULL;
				return;
			}
			prev = tmp;
			tmp = tmp->pNext;
		}
		cout << "The course you want to delete is not exist!" << endl;
	}
}

//14. View a list of his/her courses. He/she will study these courses in this semester.
void viewListOfCourseByStudent(CourseList courseList, int id) {
	if (courseList.pHead == NULL) {
		cout << "Empty course list!!!" << endl;
		return;
	}
	else {
		cout << "List of courses you are learning: " << endl;
		CourseNode* tmp = courseList.pHead;
		while (tmp != NULL) {
			for (int i = 0; i < tmp->course.numOfStudent; i++) {
				if (tmp->course.scoreboard[i].s.studentId == id) {
					cout << tmp->course.courseId << " - " << tmp->course.courseName << endl;
				}
			}
			tmp = tmp->pNext;
		}
	}
}

// 15. View a list of classes.
void viewListOfClasses(Classes* cls, int numOfClass)
{
	cout << "List of classes: \n";
	for (int i = 0; i < numOfClass; i++)
	{
		cout << "Class: " << cls[i].className << endl;
		cout << "Number of student: " << cls[i].numOfStudent << endl;
		cout << "Classyear: " << cls[i].yearNumber << endl;
	}
}

//16. View a list of students in a class (for example, 20APCS1...)
void viewStudentOfClass(Classes cls)
{
	cout << "Class: " << cls.className << endl;
	cout << "Number of students: " << cls.numOfStudent << endl;
	cout << "Classyear: " << cls.yearNumber << endl;
	cout << "List of student: \n";
	for (int i = 0; i < cls.numOfStudent; i++)
	{
		cout << cls.student[i].no << " " << cls.student[i].studentId << " ";
		cout << cls.student[i].firstName << " " << cls.student[i].lastName << " ";
		cout << cls.student[i].gender << " ";
		cout << cls.student[i].dateOfBirth.day << "/" << cls.student[i].dateOfBirth.month << "/" << cls.student[i].dateOfBirth.year << " ";
		cout << cls.student[i].socialId << " ";
		cout << cls.student[i].yearNumber;
		cout << endl;
	}
}

//17.View a list of courses
void viewListOfCourse(const char fileName[], CourseList courseList)
{
	ofstream writeFile;
	writeFile.open(fileName, ios::app);
	if (!writeFile.is_open()) {
		cout << "File \"" << fileName << " \" error!" << endl;
		return;
	}
	writeFile << "The list of courses: " << endl;
	CourseNode* temp = courseList.pHead;
	while (temp->pNext != NULL)
	{
		cout << "Course ID " << temp->course.courseId << endl;
		cout << "Course Name: " << temp->course.courseName << endl;
		cout << "Class Name: " << temp->course.className << endl;
		cout << "Teacher Name :" << temp->course.teacherName << endl;
		cout << "Number of Credit: " << temp->course.numberOfCredit << endl;
		cout << "Session: " << temp->course.session.classPeriod << endl;
		cout << "Day of week: " << temp->course.dayOfWeek << endl;
		cout << "Number of student: " << temp->course.numOfStudent;
		temp = temp->pNext;
	}
}

//18. View a list of student of a course.
void viewListOfStudentInCourse(CourseList courseList)
{
	string id;
	cout << "Enter the course id of the course you want to view a list of student: ";
	cin >> id;
	CourseNode* tmp = courseList.pHead;
	while (tmp != NULL) {
		if (tmp->course.courseId == id) {
			cout << "CourseName: " << tmp->course.courseName << endl;
			cout << "CourseID: " << tmp->course.courseId << endl;
			cout << "Name of class of Course: " << tmp->course.className << endl;
			cout << "TeacherName: " << tmp->course.teacherName << endl;
			cout << "The maximum number of students of Course: " << tmp->course.maximumNumberOfStudent << endl;
			cout << "The credit number of students of Course: " << tmp->course.numberOfCredit << endl;
			cout << "The number of students of Course: " << tmp->course.numOfStudent << endl;
			cout << "Course Year: " << tmp->course.session.classPeriod << endl;
			cout << "Day of Week: " << tmp->course.dayOfWeek << endl;
			cout << "List od students in course: " << endl;
			for (int i = 0; i < tmp->course.numOfStudent; i++) {
				cout << "No: " << tmp->course.scoreboard->s.no << endl;
				cout << "Student ID: " << tmp->course.scoreboard->s.studentId << endl;
				cout << "FullName: " << tmp->course.scoreboard->s.firstName << " " << tmp->course.scoreboard->s.lastName << endl;
				cout << "Gender: " << tmp->course.scoreboard->s.gender << endl;
				cout << "BirthDay: " << tmp->course.scoreboard->s.dateOfBirth.day << "/" << tmp->course.scoreboard->s.dateOfBirth.month << "/" << tmp->course.scoreboard->s.dateOfBirth.year << endl;
				cout << "SocialID: " << tmp->course.scoreboard->s.socialId << endl;
				cout << "YearNumber: " << tmp->course.scoreboard->s.yearNumber << endl;
				cout << "************************************************" << endl;

			}
			return;
		}
		tmp = tmp->pNext;
	}
}


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
void createSeveralClasses(Classes *&cls, int& numOfClasses) {
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
	cin >> st.firstName;
	cout << "Enter Lastname: ";
	cin >> st.lastName;
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

	writeFile << st.no << "," << st.studentId << "," << st.firstName << "," << st.lastName << "," << st.gender << "," << st.dateOfBirth.day << "/" << st.dateOfBirth.month << "/" << st.dateOfBirth.year << "," << st.socialId << "," << st.yearNumber << endl;
	writeFile.close();
}
void addNewStudentToClasses() {
	Student st;
	char fileName[] = "1st-yearStudents.txt";
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
	while (i<numOfClasses)
	{
		if (cls[i].className == classtemp)
		{
			cls[i].student = new Student[numOfStudent];
			string line;
			int j = 0;
			while (getline(file,line))
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
				getline(linestream, value,' ');
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
Node* createNode() {
	Node* tmp = new Node;
	Course crs;
	cout << "Course id: ";
	cin >> crs.courseId;
	cout << "Course name: ";
	cin >> crs.courseName;
	cout << "Class name: ";
	cin >> crs.teacherName;
	cout << "Number of credits: ";
	cin >> crs.numberOfCredit;
	cout << "The maximum number of students in course: ";
	cin >> crs.maximumNumberOfStudent;
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

void addAfterCourseList(List& lst, Node* node) {
	if (lst.pHead == NULL) {
		lst.pHead = node;
	}
	else {
		Node* tmp = lst.pHead;
		while (tmp->pNext != NULL) {
			tmp = tmp->pNext;
		}
		tmp->pNext = node;
	}
}

void addCourseToSemester(Semester& sem) {
	cout << "Enter a new course to semester: " << endl;
	Node* node = createNode();
	if (sem.listOfCourse.pHead == NULL) {
		sem.listOfCourse.pHead = node;
	}
	else {
		Node* tmp = sem.listOfCourse.pHead;
		while (tmp != NULL) {
			if ((tmp->course.session.dayOfWeek == node->course.session.dayOfWeek) && (tmp->course.session.classPeriod == node->course.session.classPeriod)) {
				cout << "The session of the course you want to add is a duplicate of the session of the other course in the semester!!!" << endl;
				cout << "Enter a other new course to semester: " << endl;
				node = createNode();
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


//11. Add a student to the course.
void addStudentToCourse(Course& course) {
	Student st;
	cout << "Enter student: " << endl;
	cout << "Enter No: ";
	cin >> st.no;
	cout << "Enter Student ID: ";
	cin >> st.studentId;
	cout << "Enter Firstname: ";
	cin >> st.firstName;
	cout << "Enter Lastname: ";
	cin >> st.lastName;
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
	int n = course.numOfStudent + 1;
	Student* tmp = new Student[n];
	for (int i = 0; i < n - 1; i++) {
		tmp[i] = course.scoreboard[i].s;
	}
	tmp[n - 1] = st;
	course.numOfStudent++;
	course.scoreboard = new Point[course.numOfStudent];
	for (int i = 0; i < course.numOfStudent; i++) {
		course.scoreboard[i].s = tmp[i];
	}
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

//14. View a list of his/her courses. He/she will study these courses in this semester.

// 15. View a list of classes.
void viewListOfClass(Classes* cls, int numOfClass)
{
	cout << "List of classes: \n";
	for (int i = 0; i < numOfClass; i++)
	{
		cout << "Class: " << cls[i].className << " Number of student: " << cls[i].numOfStudent << " Classyear: " << cls[i].yearNumber << endl;
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
		cout << cls.student[i].gender<<" ";
		cout << cls.student[i].dateOfBirth.day << "/" << cls.student[i].dateOfBirth.month << "/" << cls.student[i].dateOfBirth.year << " ";
		cout << cls.student[i].socialId << " ";
		cout << cls.student[i].yearNumber;
		cout << endl;
	}
}

//19. Export a list of students in a course to a CSV file
void exportListOfStudentsInCourseToCSVFile(const char fileName[], List listOfCourses) {
	int no;
	string schoolYear, id;
	cout << "Some information of course you want to export to CSV file: ";
	cout << "Enter school year: ";
	cin >> schoolYear;
	cout << "Enter semester ordinal number in course: ";
	cin >> no;
	cout << "Enter course id: ";
	cin >> id;
	Node* tmp = listOfCourses.pHead;
	while (tmp != NULL) {

		tmp = tmp->pNext;
	}
}
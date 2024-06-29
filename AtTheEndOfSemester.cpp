#include "Header.h"

//19. Export a list of students in a course to a CSV file.
void exportListOfStudentsInCourseToCSVFile(CourseList listOfCourse) {
	int no;
	string id;
	cout << "Some information of course you want to export to CSV file: " << endl;
	cout << "Enter course id: ";
	cin >> id;
	CourseNode* tmp = listOfCourse.pHead;
	while (tmp != NULL) {
		if (tmp->course.courseId == id) {
			string fileName = "studentInCourse" + tmp->course.courseId + "NeedPoint.csv";
			ofstream wfile;
			wfile.open(fileName, ios::app);
			if (!wfile.is_open()) {
				cout << "File error!" << endl;
				return;
			}
			wfile << tmp->course.courseId << "," << tmp->course.numOfStudent << endl;
			wfile << "Student id" << "," << "Student name" << endl;
			for (int i = 0; i < tmp->course.numOfStudent; i++) {
				wfile << tmp->course.scoreboard[i].s.no << "," << tmp->course.scoreboard[i].s.studentId << "," << tmp->course.scoreboard[i].s.firstName << " " << tmp->course.scoreboard[i].s.lastName << endl;
			}
		}
		tmp = tmp->pNext;
	}
}


//20. Import the scoreboard of a course.A scoreboard will have at least the following
//columns : No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, and
//Other Mark.(An academic staff member will export the list of students in a course, and
//send the CSV file to the teacher, the teacher will enter student results in this file, send it
//back to the staff, and then the staff will import the scoreboard to the system)
void importScoreboard(const char* file, CourseList*& listofcourse)
{
	ifstream rfile;
	rfile.open(file);
	if (!rfile.is_open())
	{
		cout << "File error!!" << endl;
		return;
	}
	string temp;
	getline(rfile, temp);
	stringstream linetemp(temp);
	string id;
	getline(linetemp, id, ',');
	getline(rfile, temp);
	CourseNode* n = listofcourse->pHead;
	while (n != NULL)
	{
		if (id == n->course.courseId)
		{
			string line;
			int j = 0;
			while (getline(rfile, line))
			{
				stringstream linestream(line);
				string value;
				getline(linestream, value, ',');
				getline(linestream, value, ',');
				getline(linestream, value, ',');
				getline(linestream, value, ',');
				n->course.scoreboard->homework = stod(value);
				getline(linestream, value, ',');
				n->course.scoreboard->midterm = stod(value);
				getline(linestream, value, ',');
				n->course.scoreboard->final = stod(value);
				n->course.scoreboard->total = n->course.scoreboard->homework * 20 / 100 + n->course.scoreboard->midterm * 30 / 100 + n->course.scoreboard->final * 50 / 100;
				j++;
			}
		}
		n = n->pNext;
	}
}

void viewScoreboard(Course course)
{
	cout << course.courseId << "-" << course.courseName << endl;
	cout << "Numbers of student: " << course.numOfStudent << endl;
	for (int i = 0; i < course.numOfStudent; i++)
		cout << course.scoreboard[i].s.no << "," << course.scoreboard[i].s.studentId << "," << course.scoreboard[i].s.firstName << " " << course.scoreboard[i].s.lastName << "," << course.scoreboard[i].s.gender << ',' << course.scoreboard[i].homework << ',' << course.scoreboard[i].midterm << ',' << course.scoreboard[i].final << ',' << course.scoreboard[i].total << endl;

}

void updateResult(Point& s)
{
	cout << "Input new point: \n";
	cout << "Input homework point: ";
	cin >> s.homework;
	cout << "Input midterm point: ";
	cin >> s.midterm;
	cout << "Input final point: ";
	cin >> s.final;
	s.total = s.homework * 20 / 100 + s.midterm * 30 / 100 + s.final * 50 / 100;
	cout << "Total point: " << s.total;
}

double findGPAOfAStudent(int MSSV, Semester sem)
{
	CourseNode* temp = sem.listOfCourse.pHead;
	int count = 0;
	double point = 0;
	for (; temp != NULL; temp = temp->pNext)
	{
		for (int i = 1; i < temp->course.numOfStudent; i++)
		{
			if (temp->course.scoreboard[i].s.studentId == MSSV)
			{
				cout << temp->course.courseName << ":";
				cout << temp->course.scoreboard[i].total << "  ";
				point = point + temp->course.scoreboard[i].total;
				count++;
			}
		}
	}
	return point / count;
}

void findGPAOfClass(Classes cls, Semester sem)
{
	for (int a = 1; a < cls.numOfStudent; a++)
	{
		cout << findGPAOfAStudent(cls.student[a].studentId, sem);
	}
}


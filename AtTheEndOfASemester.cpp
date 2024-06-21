#include "Header.h"

//19. Export a list of Student to CSV file
void exportListOfStudentToCsvFile(const char* file, Course course)
{
	ofstream wfile;
	wfile.open(file);
	if (!wfile.is_open())
	{
		cout << "File error!!" << endl;
		return;
	}
	wfile << course.courseId << "," << course.courseName << "," << course.className << "," << course.teacherName << ",";
	wfile << course.numberOfCredit << "," << course.numOfStudent << "/" << course.maximumNumberOfStudent << "," << course.dayOfWeek << ",";
	wfile << course.session.classPeriod << "/" << course.session.dayOfWeek << endl;
	for (int i = 0; i < course.numOfStudent; i++)
		wfile << course.scoreboard[i].s.no << "," << course.scoreboard[i].s.studentId << "," << course.scoreboard[i].s.firstName << "," << course.scoreboard[i].s.lastName << "," << course.scoreboard[i].s.gender << endl;
	wfile.flush();
	wfile.close();
}

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


#include "Header.h"

//19. Export a list of students in a course to a CSV file.
void exportListOfStudentsInCourseToCSVFile(CourseList listOfCourse, string id) {
	int no;
	CourseNode* tmp = listOfCourse.pHead;
	while (tmp != NULL) {
		if (tmp->course.courseId == id) {
			string fileName = "studentInCourse" + tmp->course.courseId + "NeedPoint.csv";
			ofstream wfile;
			wfile.open(fileName);
			if (!wfile.is_open()) {
				cout << "File error!" << endl;
				return;
			}
			wfile << tmp->course.courseId << "," << tmp->course.numOfStudent << endl;
			wfile << "No"<<","<<"Student id" << ", " << "Student name" << endl;
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
void importScoreboard(string cid, CourseList& listOfCourse)
{
	CourseNode* n = listOfCourse.pHead;
	string file = "studentInCourse" + cid + "NeedPoint.csv";
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
	while (n != NULL)
	{
		if (id == n->course.courseId)
		{
			string line;
			int i = 0;
			while (i<n->course.numOfStudent)
			{
				getline(rfile, line);
				stringstream linestream(line);
				string value;
				getline(linestream, value, ',');
				getline(linestream, value, ',');
				getline(linestream, value, ',');
				getline(linestream, value, ',');
				n->course.scoreboard[i].homework = stod(value);
				getline(linestream, value, ',');
				n->course.scoreboard[i].midterm = stod(value);
				getline(linestream, value, ',');
				n->course.scoreboard[i].final = stod(value);
				n->course.scoreboard[i].total = n->course.scoreboard[i].homework * 20 / 100 + n->course.scoreboard[i].midterm * 30 / 100 + n->course.scoreboard[i].final * 50 / 100;
				i++;
			}
			rfile.close();
			return;
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

void updateResult(CourseList &List)
{
	CourseNode* temp = List.pHead;
	string id;
	cout << "Input course id that you want to update result: \n";
	cin >> id;
	while (temp != NULL)
	{
		if (temp->course.courseId == id)
		{
			Course c = temp->course;
			cout << "Input student id that you want to update result: \n";
			int sid;
			cin >> sid;
			for (int i = 0; i < c.numOfStudent; i++)
			{
				if (c.scoreboard[i].s.studentId == sid)
				{
					Point s=c.scoreboard[i];
					cout << "Input new point: \n";
					cout << "Input homework point: ";
					cin >> s.homework;
					cout << "Input midterm point: ";
					cin >> s.midterm;
					cout << "Input final point: ";
					cin >> s.final;
					s.total = s.homework * 20 / 100 + s.midterm * 30 / 100 + s.final * 50 / 100;
					cout << "Total point: " << s.total << endl;
					return;
				}
			}
		}
	} 
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
				cout << temp->course.scoreboard[i].total << " \n";
				point = point + temp->course.scoreboard[i].total;
				count++;
			}
		}
	}
	cout << "The final GPA of this semester is: ";
	return point / count;
}

void findGPAOfClass(Classes *cls, int numOfClass, Semester sem)
{
	string clsname;
	cout << "Input class you that you want to show GPA: ";
	cin >> clsname;
	for (int i = 0; i < numOfClass; i++)
	{
		if (cls[i].className == clsname)
		{
			for (int a = 1; a < cls[i].numOfStudent; a++)
			{
				cout << findGPAOfAStudent(cls[i].student[a].studentId, sem);
			}
		}
	}
}

//24. View student's scoreboard
void viewScoreboard(StudentUserNode *sun,Semester sem)
{
	int id = sun->su.student.studentId;
	cout<< findGPAOfAStudent(id, sem);
}
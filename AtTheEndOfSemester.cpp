#include "Header.h"

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

void importScoreboard(const char* file, List*& listofcourse)
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
	int idd = stoi(id);
	Node* n = listofcourse->pHead;
	while (n != NULL)
	{
		if (idd == n->course.courseId)
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
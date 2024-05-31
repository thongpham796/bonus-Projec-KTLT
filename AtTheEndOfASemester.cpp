#include "Header.h"

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
		wfile << course.student[i].no << "," << course.student[i].studentId << "," << course.student[i].firstName << "," << course.student[i].lastName << "," << course.student[i].gender << endl;
	wfile.flush();
	wfile.close();
}
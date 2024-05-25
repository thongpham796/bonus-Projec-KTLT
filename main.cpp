#include "Header.h"

int main()
{
	cout << "\t--------------------------A COURSE MANAGEMENT SYSTEM--------------------------\n\n" << endl;
	menu();
	int selection;
	cin >> selection;
	switch (selection)
	{
	case 1:
	{
		menu1();
		int a;
		cin >> a;
		User x = inputUser(a);
		break;
	}
	case 2:
	{
		menu1();
		int a;
		cin >> a;
		sighUp(a);
		break;
	}
	default:
		cout << "Our program doesn't support this option!\n";
	}
	//1. Create a school year(2020 - 2021, for example)
	string schoolYear = createSchoolYear();
	cout << "School year: " << schoolYear << endl;

	//2. Create several classes for 1st - year students. For example : class 20APCS1, class 20APCS2,
	//class 20CLC1..., class 20CLC11, class 20VP...
	/*string* classes;
	int numOfClasses;
	createSeveralClasses(classes, numOfClasses);*/
	Classes* cls ;
	int num = 0;
	createSeveralClasses(cls, num);
	addStudentToClassesFromCsvFile("listStudents.csv", cls, num);
	viewListOfClass(cls, num);
	for (int i = 0; i < num; i++)
	{
		viewStudentOfClass(cls[i]);
	}
	//3. Add new 1st year students to 1st-year classes.
	//addNewStudentToClasses();

	//6. Create a semester: 1, 2, or 3, school year, start date, end date. Choose the school year
	//	that the newly created semester belongs to.The created semester will be the current /
	//	default semester for all the below actions.
	Semester sem = createSemester();

	//7. Add a course to this semester: course id, course name, class name, teacher name,
	//number of credits, the maximum number of students in the course(default 50), day of
	//the week, and the session that the course will be performed(MON / TUE / WED / THU /
	//FRI / SAT, S1(07:30), S2(09:30), S3(13:30) and S4(15:30)).A course will be taught in
	//only one session in a week.
	addCourseToSemester(sem);
	addCourseToSemester(sem);
	addCourseToSemester(sem);
	//8. Then he/she will upload a CSV file, containing a list of students enrolled in the course.
	/*char fileName[] = "studentInCourse.csv";
	addStudentToCourse(sem.listOfCourse.pHead->course);	
	uploadCSVFileContainingListStudentInCourse(fileName, sem.listOfCourse.pHead->course);*/
	return 0;
}

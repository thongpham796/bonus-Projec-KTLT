#include "Header.h"

int main()
{
		cout << "\t--------------------------A COURSE MANAGEMENT SYSTEM--------------------------\n\n" << endl;
		//Option: Log in or Sign up
		menu();
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1:
		{
			//Option: Academic staff(1) or Student(2)
			menu1();
			int a;
			cin >> a;
			User x = inputUser(a);
			if (a == 1) {
				//1. Create a school year(2020 - 2021, for example)
				/*string schoolYear = createSchoolYear();
				cout << "School year: " << schoolYear << endl;*/

				//2. Create several classes for 1st - year students. For example : class 20APCS1, class 20APCS2,
				//class 20CLC1..., class 20CLC11, class 20VP...
				Classes* cls;
				int num = 0;
				char fileName2[] = "listStudents.csv";
				createSeveralClasses(cls, num);
				addStudentToClassesFromCsvFile(fileName2, cls, num);
				viewListOfClasses(cls, num);
				for (int i = 0; i < num; i++)
				{
					viewStudentOfClass(cls[i]);
				}
				//3. Add new 1st year students to 1st-year classes.
				addNewStudentToClasses(fileName2);

				//4. For quick input, he / she can import a CSV file containing all students in a specific class to
				//the system, instead of adding one by one : No, Student ID, First name, Last name,
				//Gender, Date of Birth, and Social ID.


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
				
				//8. Then he/she will upload a CSV file, containing a list of students enrolled in the course.
				char fileName8[] = "studentInCourse.csv";
				addStudentToCourse(sem.listOfCourse);
				uploadCSVFileContainingListStudentInCourse(fileName8, sem.listOfCourse.pHead->course);

				//9. View the list of courses.
				viewListOfCourse(sem.listOfCourse);				

				//10. Update course information.
				updateCourseInfo(sem.listOfCourse);
				viewListOfCourse(sem.listOfCourse);

				//11. Add a student to the course.
				addStudentToCourse(sem.listOfCourse);
				addStudentToCourse(sem.listOfCourse);

				//12. Remove a student from the course.
				removeStudentFromCourse(sem.listOfCourse);
				
				//13. Delete a course.
				deleteACourse(sem.listOfCourse);
				viewListOfCourse(sem.listOfCourse);

				//15. View a list of classes.
				viewListOfClasses(cls, num);

				//16. View a list of students in a class (for example, 20APCS1...)
				viewStudentOfClass(cls[0]);

				//17. View a list of courses.
				viewListOfCourse(sem.listOfCourse);

				//18. View a list of students in a course
				viewListOfStudentInCourse(sem.listOfCourse);

				//19. Export a list of students in a course to a CSV file

			}
			else if (a == 2) {

			}
			else {
				cout << "Our program doesn't support this option, please enter 1 or enter 2)\n";
			}
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
	return 0;
}

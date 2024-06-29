#include "Header.h"

int main()
{
	disableConsoleDragging();
	fillFullScreen(0x77);
	gotoXY(4, 4);
	textcolor(5);
	cout << WHITE_BG BLUE_TEXT R"(
                                      ____  _             _            _
                                     / ___|| |_ _   _  __| | ___ _ __ | |_
                                     \___ \| __| | | |/ _` |/ _ \ '_ \| __|
                                      ___) | |_| |_| | (_| |  __/ | | | |_
                   ___  ___          |____/ \__|\__,_|\__,_|\___|_| |_|\__| ___           __
                   |  \/  | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_    ___  / _|
                   | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|  / _ \| |
                   | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_  | (_) |  _|
                   |_|  |_|\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|  \____|_|
                               \___/   
                                                ___________ __ __
                                               |_   _/ _ \| |/ /
                                                 | || | | | ' /
                                                 | || |_| | . \
                                                 |_| \__\_\_|\_\
 )" << endl;

	AcademicStaffUserList asul;
	initList(asul);
	StudentUserList sul;
	initList(sul);

	while (1) {
		//Option: Log in or Sign up
		menu();
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1:
			// Log in 
			while (1) {
				//Option: Academic staff(1) or Student(2)
				menu1();
				int a;
				cin >> a;
				if (a == 1) {
					AcademicStaffUserNode* node = inputAcademicStaffUser(asul);
					
					cout << "Choose what you want to do: " << endl;
					cout << "1. View profie info" << endl;
					cout << "2. Change pasword" << endl;
					cout << "3. Perform the operations below: " << endl;
					cout << "- Create a school year (2020-2021, for example)" << endl;
					cout << "- Create several classes for 1st-year students. For example: class 20APCS1, class 20APCS2, class 20CLC1..., class 20CLC11, class 20VP..." << endl;
					cout << "- Add new 1st year students to 1st-year classes." << endl;
					cout << "- For quick input, he/she can import a CSV file containing all students in a specific class to the system, instead of adding one by one: No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID." << endl;
					cout << "- He/she does not need to add 2nd-year, 3rd-year, or 4th-year students, because these students had been added in the previous years." << endl;
					cout << "- Create a semester: 1, 2, or 3, school year, start date, end date. Choose the school year that the newly created semester belongs to.The created semester will be the current default semester for all the below actions." << endl;
					cout << "- Add a course to this semester: course id, course name, class name, teacher name, number of credits, the maximum number of students in the course(default 50), day of the week," << endl;
					cout << "and the session that the course will be performed(MON / TUE / WED / THU / FRI / SAT, S1(07:30), S2(09:30), S3(13:30) and S4(15:30)).A course will be taught in only one session in a week." << endl;
					cout << "- Then he/she will upload a CSV file, containing a list of students enrolled in the course." << endl;
					cout << "- View the list of courses." << endl;
					cout << "- Update course information." << endl;
					cout << "- Add a student to the course." << endl;
					cout << "- Remove a student from the course." << endl;
					cout << "- Delete a course." << endl;
					cout << "4. Back to before" << endl;
					cout << "5. Log out" << endl;
					int choice;
					cin >> choice;
					if (choice == 1) {
						viewProfile(node->au);
					}
					else if (choice == 2) {
						changeAcademicStaffUserPassword(node, asul);
						cout << "Log in: " << endl;
						break;
					}
					else if (choice == 3) {
						//1. Create a school year(2020 - 2021, for example)
						SchoolYear sy;
						sy.nameOfSY = createSchoolYear();
						cout << "School year: " << sy.nameOfSY << endl;

						//2. Create several classes for 1st - year students. For example : class 20APCS1, class 20APCS2,
						//class 20CLC1..., class 20CLC11, class 20VP...
						/*string* classes;
						int numOfClasses;
						createSeveralClasses(classes, numOfClasses);*/
						Classes* cls;
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
					}
					else if (choice == 4) {
						continue;
					}
					else if (choice == 5) {
						break;
					}
					else {
						cout << "Our program doesn't support this option\n";
					}

					
				}
				else if (a == 2) {
					StudentUserNode* node = inputStudentUser(sul);
					viewProfile(node->su);
				}
				else {
					cout << "Our program doesn't support this option, please enter 1 or enter 2\n";
				}
				break;
			}
			break;
		case 2:
			//Sign up
			//Option: Academic staff(1) or Student(2)
			menu1();
			int a;
			cin >> a;
			if (a == 1) {
				sighUpAsAAcademicStaff();
			}
			if (a == 2) {
				sighUpAsAStudent();
			}
			break;	
		default:
			cout << "Our program doesn't support this option!\n";
			break;
		}
	}
	system("pause");
	system("cls");
	return 0;
}
// This program reads user details as input outputs course details and billing information


/************
Darryl Thompson
dthomp11@my.athens.edu
00108377
Project 3
*************/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
//#include <cmath>

using namespace std;
const int COURSE_NUM = 4;
const int CLASS_NUM = 12;


typedef int courseType[COURSE_NUM];  // declares a new data type: int array of 4 elements
typedef string classType[CLASS_NUM]; // declares a new data type: string array of 12 elements
typedef int hourType[CLASS_NUM];	 // declares a new data type: int array of 12 elements

// Prototype of the functions

void displayMenu(int& menuChoice);
void selectClasses(courseType courseNo, classType mathClass, classType infoTechClass, 
	classType compSciClass, classType& chosenClass, hourType mathHours, hourType infoTechHours, 
	hourType compSciHours, hourType& chosenHours, int& howManyClasses);
void selectScholarship(int& scholType, float& scholAmount, float SCHOLAMOUNT1, float SCHOLAMOUNT2, 
	string SCHOLTYPETITLE1, string SCHOLTYPETITLE2, string& scholTitle);
void viewSchedule(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, int howManyClasses);
void saveSchedule(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, int howManyClasses, ofstream& dataOut);
void viewBill(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, const float TUITIONHOURCOST, const float REGFEES, int howManyClasses, int scholType, string scholTitle, float scholAmount);
void saveBill(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, const float TUITIONHOURCOST, const float REGFEES, int howManyClasses,int scholType, string scholTitle, float scholAmount, ofstream& dataOut);
void printDetails(classType chosenClass, hourType chosenHours, const float TUITIONHOURCOST, const float REGFEES, string firstName, string lastName, int studentID, int howManyClasses, int scholType, string scholTitle, float scholAmount, ofstream& dataOut);

void exitProgram();

int main()
{
	courseType courseNo = {310,452,305,308};
	classType mathClass =	   {"Matrices and Linear Algebra",
								"Introductory Real Analysis",
								"Calculus III",
								"Discrete Math"};
	classType infoTechClass =  {"Data Analysis and Visualization",
								"Senior Capstone Project",
								"Networking Fundamentals",
								"Network Architecture" };
	classType compSciClass =   {"Ethics",
								"Senior Capstone Project",
								"Concepts of Programming",
								"Computer Science II" };
	classType chosenClass;
	hourType mathHours = {3,3,3,3 };
	hourType infoTechHours = { 3,3,2,2 };
	hourType compSciHours = { 1,3,3,3 };
	hourType chosenHours = { 0 };

	const float TUITIONHOURCOST = 263.00;
	const float REGFEES = 162.50;
	const string PREMA = " MA";
	const string PRECS = " CS";
	const string PREITE = "ITE";
	const string COURSE1PRE = PRECS;
	const string COURSE2PRE = PREITE;
	const string COURSE3PRE = PREMA;
	const float SCHOLAMOUNT1 = 500.00;
	const float SCHOLAMOUNT2 = 750.00;
	const string SCHOLTYPETITLE1 = "Academic Scholarship";
	const string SCHOLTYPETITLE2 = "Foundation Scholarship";
	const string SCHEDULEFILE = "Schedule.txt";
	const string BILLFILE = "Bills.txt";
	const string DETAILSFILE = "Details.txt";

	string firstName;
	string lastName;
	int studentID;

	float totalDue;
	int menuChoice;
	int classNumber;
	int totalHours = 0;
	int howManyClasses = 0;
	bool classDone = false;
	bool scholFlag;
	bool scholTypeFlag = false;
	float scholAmount = 0;
	int scholMenu;
	int scholType;
	string scholTitle = "No Scholarship";
	float totalTuition;
	ofstream dataOut;
	ofstream billOut;
	ofstream detailOut;

	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << right << setw(60) << "********** WELCOME TO THE SEMESTER **********" << endl << endl;
	cout << "Please enter your first name, followed by your last name, and your student ID number." << endl;
	cout << "Do not include the A or leading 0s in your ID." << endl << endl;
	cin >> firstName >> lastName >> studentID;
	cin.ignore(10, '\n');

	do
	{
// Menu Start
		displayMenu(menuChoice);

		
		switch (menuChoice)
		{
			case 1: // Select Classes
				selectClasses(courseNo, mathClass, infoTechClass, compSciClass, chosenClass, mathHours, 
					infoTechHours, compSciHours, chosenHours, howManyClasses);
				break;

			case 2: // Scholarship
				selectScholarship(scholType, scholAmount, SCHOLAMOUNT1, SCHOLAMOUNT2, SCHOLTYPETITLE1, 
					SCHOLTYPETITLE2, scholTitle);
				break;

			case 3: // View Schedule
				if (howManyClasses)
				{

					viewSchedule(firstName, lastName, studentID, chosenClass, chosenHours, howManyClasses);
				}
				else
				{
					
					cout << "***********************************************************" << endl;
					cout << "You must select your classes before you can view a schedule" << endl;
					cout << "***********************************************************" << endl << endl;

					cout << "Press enter to return to the main menu" << endl;
					cin.ignore(10, '\n');
					cin.get();
				}

				break;
			case 4: // Save Schedule
				if (howManyClasses)
				{


					dataOut.open(SCHEDULEFILE);
					if (dataOut)
					{
						dataOut << endl << "Dear " << firstName << " " << lastName << " (" << studentID << ")" << endl;
						dataOut << "Below is your class listing for the Fall 2023 semester." << endl << endl;

						saveSchedule(firstName, lastName, studentID, chosenClass, chosenHours, howManyClasses, dataOut);

						cout << "Schedule written to the file " << SCHEDULEFILE << " successfully." << endl;
						cout << endl << endl << endl;
						cout << "Press enter to continue" << endl;
						cin.ignore(10, '\n');
						cin.get();
					}
					else
					{
						cout << "Unable to open the file." << endl;
						cout << endl << endl;
						cout << "Press enter to continue" << endl;
						cin.ignore(10, '\n');
						cin.get();
					}
					dataOut.close();
				}
				else
				{

					cout << "***********************************************************" << endl;
					cout << "You must select your classes before you can save a schedule" << endl;
					cout << "***********************************************************" << endl << endl;

					cout << "Press enter to return to the main menu" << endl;
					cin.ignore(10, '\n');
					cin.get();
				}

				break;
			case 5: // View Bill
				
				if ((howManyClasses) || (scholAmount))
				{

					viewBill(firstName, lastName, studentID, chosenClass, chosenHours, TUITIONHOURCOST, REGFEES, howManyClasses, scholType, scholTitle, scholAmount);
						break;
				}
				else
				{

					cout << "***********************************************************" << endl;
					cout << "*   You do not have a bill to view or print because you   *" << endl;
					cout << "*   have not selected classes or selected a scholarship   *" << endl;
					cout << "***********************************************************" << endl << endl;

					cout << "Press enter to return to the main menu" << endl;
					cin.ignore(10, '\n');
					cin.get();
				}
				break;
			case 6: // Save Bill				
				
				if ((howManyClasses) || (scholAmount))
				{
					dataOut.open(BILLFILE);
					if (dataOut)
					{
						dataOut << endl << "Dear " << firstName << " " << lastName << " (" << studentID << ")" << endl;
						dataOut << "Below is your billing information for the Fall 2023 semester." << endl << endl;

						saveBill(firstName, lastName, studentID, chosenClass, chosenHours, TUITIONHOURCOST, REGFEES, howManyClasses, scholType, scholTitle, scholAmount, dataOut);

						cout << "Bill written to the file " << BILLFILE << " successfully." << endl;
						cout << endl << endl << endl;
						cout << "Press enter to continue" << endl;
						cin.ignore(10, '\n');
						cin.get();
					}

					else
					{
						cout << "Unable to open the file." << endl;
						cout << endl << endl;
						cout << "Press enter to continue" << endl;
						cin.ignore(10, '\n');
						cin.get();
					}
					dataOut.close();
				}
				else
				{

					cout << "***********************************************************" << endl;
					cout << "*   You do not have a bill to view or print because you   *" << endl;
					cout << "*   have not selected classes or selected a scholarship   *" << endl;
					cout << "***********************************************************" << endl << endl;

					cout << "Press enter to return to the main menu" << endl;
					cin.ignore(10, '\n');
					cin.get();
				}
				break;

			case 7: // Print Details
				dataOut.open(DETAILSFILE);
				if (dataOut)
				{
					dataOut << endl << "Dear " << firstName << " " << lastName << " (" << studentID << ")" << endl;
					dataOut << "Welcome to the Fall 2023 semester." << endl << endl;
					dataOut << "Your schedule and billing information are listed below." << endl << endl;
					
					printDetails(chosenClass, chosenHours, TUITIONHOURCOST, REGFEES, firstName, lastName, studentID, howManyClasses, scholType, scholTitle, scholAmount, dataOut);

					cout << "Schedule written to the file " << DETAILSFILE << " successfully." << endl;
					cout << endl << endl << endl;

					cout << "Press enter to continue" << endl;
					cin.ignore(10, '\n');
					cin.get();
				}
				else
				{
					cout << "Unable to open the file." << endl;
					cout << endl << endl;

					cout << "Press enter to continue" << endl;
					cin.ignore(10, '\n');
					cin.get();
				}
				dataOut.close();
				break;

			case 8: // Exit
				exitProgram();
				break;

			default:
					cout << "You have entered an invalid selection" << endl;
					cout << "Try again please" << endl;
				break;
		}
	}
	while (menuChoice != 8);

	return 0;
}

//****************************************************************************
//
// Menu Function
//
//****************************************************************************

void displayMenu(int& menuChoice)
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "************* Main Menu **************" << endl << endl;
	cout << "1. Select Classes" << endl;
	cout << "2. Enter Scholarship" << endl;
	cout << "3. View Schedule" << endl;
	cout << "4. Save Schedule" << endl;
	cout << "5. View Bill" << endl;
	cout << "6. Save Bill" << endl;
	cout << "7. Print Details" << endl;
	cout << "8. Exit" << endl << endl;
	cout << "Select an option from the above menu by entering the appropriate number 1-8" << endl;
	cin >> menuChoice;

}

//****************************************************************************
//
// Classes Function
//
//****************************************************************************

void selectClasses(courseType courseNo, classType mathClass, classType infoTechClass,
	classType compSciClass, classType& chosenClass, hourType mathHours, hourType infoTechHours,
	hourType compSciHours, hourType& chosenHours, int& howManyClasses)
{
	const string PRE1 = " MA";
	const string PRE2 = " CS";
	const string PRE3 = "ITE";
	int classPrefix;
	int chosenCourseNum;
	bool classDone = false;
	bool validCourse = false;
	string chosenPre;
	string chosenCourseNumStr;
	string courseTitle;
	string space = "   ";
	int totalHours = 0;


	//***** how many classes *****
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "************** Classes ***************" << endl << endl;
	cout << "You can register for up to " << CLASS_NUM << " classes" << endl;
	cout << "How many classes do you plan to register for?" << endl;
	cin >> howManyClasses;

	for (int num = 0; num < howManyClasses; num++)
	{
		chosenClass[num] = { 0 };
		chosenHours[num] = { 0 };
	}
	while (howManyClasses < 1 || howManyClasses > CLASS_NUM)
	{
		cout << "*****  Invalid entry  *****" << endl;
		cout << "You can register for up to " << CLASS_NUM << " classes" << endl;
		cout << "How many classes do you plan to register for?" << endl;
		cin >> howManyClasses;		
	}
	//***** select prefix *****
	do
	{

		for (int classCount = 0; classCount < howManyClasses; classCount++)
		{
			classPrefix = 0;
			cout << endl << endl << endl << endl << endl << endl;
			cout << endl << endl << endl << endl << endl << endl;
			cout << endl << endl << endl << endl << endl << endl;
			cout << endl << endl << endl << endl << endl << endl;
			cout << endl << endl << endl << endl << endl << endl;
			cout << endl << endl << endl << endl << endl << endl;
			cout << "You have selected the following classes: " << endl << endl;
			for (int num = 0; num < howManyClasses; num++)
			{
				cout << "Class " << (num + 1) << " : " << setw(48) << left << chosenClass[num] << setw(7) << right << chosenHours[num] << " hrs" << endl;
			}
			cout << endl << endl;
			cout << "*** Course Prefix ***" << endl << endl;
			cout << "1. " << right << PRE1 << endl;
			cout << "2. " << right << PRE2 << endl;
			cout << "3. " << right << PRE3 << endl << endl;
			cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
			cout << "Choose the course prefex of the class you want to take from the menu" << endl;
			cout << "Select 1, 2 or 3: ";
			cin >> classPrefix;

			switch (classPrefix)
			{
				case 1:
					//***** course number *****			
					chosenCourseNum = 0;
					validCourse = false;
					do
					{
				

						cout << "Enter the course number of the class you want to take: ";
						cin >> chosenCourseNum;
						while (!validCourse)
						{

							for (int elementNum = 0; elementNum < COURSE_NUM && validCourse == false; elementNum++)
							{
								if (courseNo[elementNum] == chosenCourseNum)
								{
									validCourse = true;
									cout << "Valid course is true" << endl;
									chosenPre = PRE1;
									cout << "chosenPre = " << chosenPre << endl;
									chosenCourseNumStr = to_string(chosenCourseNum);
									cout << "chosenCourseNumStr converted = " << chosenCourseNumStr << endl;
									chosenHours[classCount] = mathHours[elementNum];
									courseTitle = mathClass[elementNum];
									cout << "course title = " << courseTitle << endl;
									chosenClass[classCount] = space + chosenPre + space + chosenCourseNumStr + space + courseTitle;

										for (int counter = classCount -1; counter >= 0 ; counter--)
										{
											if (chosenClass[classCount] == chosenClass[counter])
											{
		
												cout << endl << endl << endl << endl << endl << endl << endl << endl;
												cout << endl << endl << endl << endl << endl << endl << endl << endl;
												cout << endl << endl << endl << endl << endl << endl << endl << endl;
												cout << endl << endl << endl << endl << endl << endl << endl << endl;


												cout << "*******************************************************************************" << endl;
												cout << "*  You have already selected that course. Please choose a different course.   *" << endl;
												cout << "*******************************************************************************" << endl;
												chosenClass[classCount] = { 0 };
												chosenHours[classCount] = { 0 };
												classCount--;
												cout << endl;
												cout << "Chosen Course = " << chosenClass[classCount] << endl;
												cout << endl << endl << endl;
												cout << "Press enter to continue" << endl;
												cin.ignore(10, '\n');
												cin.get();
											}
										}
								}	
							}
							if (validCourse == 0)
							{
								cout << endl << endl;
								cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
								cout << "***************************************************" << endl;
								cout << "***** You did not enter a valid course number *****" << endl;
								cout << "***************************************************" << endl;
								cout << "Enter the course number of the class you want to take" << endl;
								cin >> chosenCourseNum;
							}
						}

					} while (!validCourse);

					break;
			
				case 2:
					chosenCourseNum = 0;
					validCourse = false;
					do
					{

						cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
						cout << "Enter the course number of the class you want to take: ";
						cin >> chosenCourseNum;
						while (!validCourse)
						{

							for (int elementNum = 0; elementNum < COURSE_NUM && validCourse == false; elementNum++)
							{
								if (courseNo[elementNum] == chosenCourseNum)
								{
									validCourse = true;
									cout << "Valid course is true" << endl;
									chosenPre = PRE2;
									cout << "chosenPre = " << chosenPre << endl;
									chosenCourseNumStr = to_string(chosenCourseNum);
									cout << "chosenCourseNumStr converted = " << chosenCourseNumStr << endl;
							courseTitle = infoTechClass[elementNum];
							cout << "course title = " << courseTitle << endl;
							chosenHours[classCount] = infoTechHours[elementNum];
							chosenClass[classCount] = space + chosenPre + space + chosenCourseNumStr + space + courseTitle;

							for (int counter = classCount - 1; counter >= 0; counter--)
							{
								if (chosenClass[classCount] == chosenClass[counter])
								{

									cout << endl << endl << endl << endl << endl << endl << endl << endl;
									cout << endl << endl << endl << endl << endl << endl << endl << endl;
									cout << endl << endl << endl << endl << endl << endl << endl << endl;
									cout << endl << endl << endl << endl << endl << endl << endl << endl;


									cout << "*******************************************************************************" << endl;
									cout << "*  You have already selected that course. Please choose a different course.   *" << endl;
									cout << "*******************************************************************************" << endl;

									classCount--;
									cout << endl;
									cout << "Chosen Course = " << chosenClass[classCount] << endl;
									cout << endl << endl << endl;
									cout << "Press enter to continue" << endl;
									cin.ignore(10, '\n');
									cin.get();
								}
							}



							cout << endl;
							cout << "chosen Class = " << chosenClass[classCount] << endl;
								}
							}
							if (validCourse == 0)
							{
								cout << endl << endl;
								cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
								cout << "***************************************************" << endl;
								cout << "***** You did not enter a valid course number *****" << endl;
								cout << "***************************************************" << endl;
								cout << "Enter the course number of the class you want to take" << endl;
								cin >> chosenCourseNum;
							}
						}
					} while (!validCourse);

					break;
				case 3:
					chosenCourseNum = 0;
					validCourse = false;
					do
					{

						cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
						cout << "Enter the course number of the class you want to take: ";
						cin >> chosenCourseNum;
						while (!validCourse)
						{

							for (int elementNum = 0; elementNum < COURSE_NUM && validCourse == false; elementNum++)
							{
								if (courseNo[elementNum] == chosenCourseNum)
								{
									validCourse = true;
									cout << "Valid course is true" << endl;
									chosenPre = PRE3;
									cout << "chosenPre = " << chosenPre << endl;
									chosenCourseNumStr = to_string(chosenCourseNum);
									cout << "chosenCourseNumStr converted = " << chosenCourseNumStr << endl;
									courseTitle = compSciClass[elementNum];
									cout << "course title = " << courseTitle << endl;
									chosenHours[classCount] = compSciHours[elementNum];
									chosenClass[classCount] = space + chosenPre + space + chosenCourseNumStr + space + courseTitle;

									for (int counter = classCount - 1; counter >= 0; counter--)
									{
										if (chosenClass[classCount] == chosenClass[counter])
										{
											cout << endl << endl << endl << endl << endl << endl << endl << endl;
											cout << endl << endl << endl << endl << endl << endl << endl << endl;
											cout << endl << endl << endl << endl << endl << endl << endl << endl;
											cout << endl << endl << endl << endl << endl << endl << endl << endl;
											cout << "*******************************************************************************" << endl;
											cout << "*  You have already selected that course. Please choose a different course.   *" << endl;
											cout << "*******************************************************************************" << endl;

											classCount--;
											cout << endl;
											cout << "Chosen Course = " << chosenClass[classCount] << endl;
											cout << endl << endl << endl;
											cout << "Press enter to continue" << endl;
											cin.ignore(10, '\n');
											cin.get();
										}
									}
								}
							}
							if (validCourse == 0)
							{
								cout << endl << endl;
								cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
								cout << "***************************************************" << endl;
								cout << "***** You did not enter a valid course number *****" << endl;
								cout << "***************************************************" << endl;
								cout << "Enter the course number of the class you want to take" << endl;
								cin >> chosenCourseNum;
							}
						}
						if (validCourse == 0)
						{
							cout << "Class " << (classCount + 1) << " of " << howManyClasses << endl;
							cout << "4***** You did not enter a valid course number *****" << endl;
						}
					} while (!validCourse);

					break;
				default:
					cout << "*****************************************" << endl;
					cout << "***** You chose an incorrect option *****" << endl;
					cout << "*****************************************" << endl;

					classCount--;

					cout << endl << endl << endl;
					cout << "Press enter to continue" << endl;
					cin.ignore(10, '\n');
					cin.get();

					break;
			}
		}	
	}
	while (!validCourse);
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "You selected the following classes. If this is incorrect, please select classes again." << endl << endl;
	for (int num = 0; num < howManyClasses; num++)
	{
		cout << "Class " << (num + 1) << " : " << setw(48) << left << chosenClass[num] << setw(7) << right << chosenHours[num] << " hrs" << endl;
	}
	for (int num = 0; num < howManyClasses; num++)
	{
		totalHours += chosenHours[num];
	}
	cout << endl << "Total Hours = " << totalHours << endl;
	cout << endl << endl;
	cout << endl << endl;
	classDone = true;

	cout << endl << endl << endl;
	cout << "Press enter to continue" << endl;
	cin.ignore(10, '\n');
	cin.get();
}



//****************************************************************************
//
// Scholarship Function
//
//****************************************************************************

void selectScholarship(int& scholType, float& scholAmount, float SCHOLAMOUNT1, float SCHOLAMOUNT2, string SCHOLTYPETITLE1, string SCHOLTYPETITLE2, string& scholTitle)

{
	bool scholFlag = false;
	int scholMenu;

	do
	{
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << "********** Scholarship Menu **********" << endl << endl;
		cout << "1. I received an " << SCHOLTYPETITLE1 << endl;
		cout << "2. I received a " << SCHOLTYPETITLE2 << endl;
		cout << "3. I Did Not Receive a Scholarship" << endl;
		cout << "Enter choice from above menu" << endl;
		cin >> scholMenu;

		switch (scholMenu)
		{
			case 1:
				scholType = 1;
				scholTitle = SCHOLTYPETITLE1;
				scholAmount = SCHOLAMOUNT1;
				scholFlag = true;
				break;

			case 2:
				scholType = 2;
				scholTitle = SCHOLTYPETITLE2;
				scholAmount = SCHOLAMOUNT2;
				scholFlag = true;

				break;
			case 3:
				scholType = 0;
				scholTitle = "No Scholarship";
				scholAmount = 0;
				scholFlag = true;
				break;
		default:
			cout << "You have entered an invalid selection" << endl;
			break;

		}
	} while (!scholFlag);

	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "You selected: " << scholTitle << endl;
	cout << "You will receive a $" << scholAmount << " scholarship." << endl;
	cout << endl << endl;
	cout << endl << endl << endl;
	cout << "Press enter to continue" << endl;
	cin.ignore(10, '\n');
	cin.get();
}

//****************************************************************************
//
// View Schedule Function
//
//****************************************************************************
void viewSchedule(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, int howManyClasses)

{
	int totalHours = 0;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << "Dear " << firstName << " " << lastName << " (" << studentID << ")" << endl;
	cout << "Thank you for entering your information." << endl;
	cout << "Below is your class listing for the Fall 2023 semester." << endl << endl;

	cout << "******************** COURSE DETAILS ***********************" << endl;
	cout << setw(9) << left << "Prefix" << setw(6) << left << "No." << setw(33) << "Title" << right << "Credit Hour" << endl;
	cout << "***********************************************************" << endl;

	for (int num = 0; num < howManyClasses; num++)
	{
		cout << setw(48) << left << chosenClass[num] << setw(7) << right << chosenHours[num] << " hrs" << endl;
	}
	for (int num = 0; num < howManyClasses; num++)
	{
		totalHours += chosenHours[num];
	}
	cout << endl << "Total Hours = " << totalHours << endl;
	cout << endl << endl;
	cout << endl << endl;

	cout << endl << endl << endl;
	cout << "Press enter to continue" << endl;
	cin.ignore(10, '\n');
	cin.get();
}


//****************************************************************************
//
// Save Schedule Function
//
//****************************************************************************

void saveSchedule(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, int howManyClasses, ofstream& dataOut)

{
		int totalHours = 0;

		dataOut << endl;

		if (howManyClasses)
		{
			dataOut << "******************** COURSE DETAILS ***********************" << endl;

			dataOut << setw(9) << left << "Prefix" << setw(6) << left << "No." << setw(33) << "Title" << right << "Credit Hour" << endl;
			dataOut << "***********************************************************" << endl;

			for (int num = 0; num < howManyClasses; num++)
			{
				dataOut << setw(48) << left << chosenClass[num] << setw(7) << right << chosenHours[num] << " hrs" << endl;
			}
			for (int num = 0; num < howManyClasses; num++)
			{
				totalHours += chosenHours[num];
			}
		}
		else
		{
			dataOut << "You are not currently registered for any classes." << endl;
		}
		dataOut << endl << "Total Hours = " << totalHours << endl;
		dataOut << endl << endl;
}

//****************************************************************************
//
// View Bill Function
//
//****************************************************************************

void viewBill(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, const float TUITIONHOURCOST, const float REGFEES, int howManyClasses, int scholType, string scholTitle, float scholAmount)

{
	int totalHours = 0;

	for (int num = 0; num < howManyClasses; num++)
	{
		totalHours += chosenHours[num];
	}

	float totalTuition = totalHours * TUITIONHOURCOST;
	float totalDue = (totalHours * TUITIONHOURCOST) + REGFEES - scholAmount;
			
	cout << setprecision(2) << fixed << showpoint;
	cout << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << "********** BILLING INFORMATION **********" << endl;
	if (howManyClasses)
	{
		cout << right << setw(11) << "Tuition" << right << setw(29) << totalTuition << endl;
		cout << right << setw(11) << "Fees" << right << setw(29) << REGFEES << endl;
		cout << right << setw(11) << "Scholarship" << right << setw(29) << (-1 * scholAmount) << endl << endl;
		cout << right << setw(11) << "Total Due:" << right << setw(29) << totalDue << endl << endl << endl;

	}
	else
	{
		cout << endl << endl;
		cout << "You have not selected any classes and do not have any tuition or fees due" << endl;
		cout << "You currently have a credit of $" << scholAmount << endl << endl;
	}
	cout << "Scholarship Information: " << scholTitle << endl;
	cout << "Scholarship Amount: $" << scholAmount << endl;
	cout << endl;

	cout << endl << endl << endl;
	cout << "Press enter to continue" << endl;
	cin.ignore(10, '\n');
	cin.get();
}

//****************************************************************************
//
// Save Bill Function
//
//****************************************************************************

void saveBill(string firstName, string lastName, int studentID, classType chosenClass, hourType chosenHours, const float TUITIONHOURCOST, const float REGFEES, int howManyClasses, int scholType, string scholTitle, float scholAmount, ofstream& dataOut)

{
	int totalHours = 0;

	if (howManyClasses)
	{
		for (int num = 0; num < howManyClasses; num++)
		{
			totalHours += chosenHours[num];
		}
		float totalTuition = totalHours * TUITIONHOURCOST;
		float totalDue = (totalHours * TUITIONHOURCOST) + REGFEES - scholAmount;

		dataOut << setprecision(2) << fixed << showpoint;
		dataOut << endl;
		dataOut << "***************** BILLING INFORMATION *********************" << endl;
		dataOut << right << setw(11) << "Tuition" << right << setw(48) << totalTuition << endl;
		dataOut << right << setw(11) << "Fees" << right << setw(48) << REGFEES << endl;
		dataOut << right << setw(11) << "Scholarship" << right << setw(48) << (-1 * scholAmount) << endl << endl;
		dataOut << right << setw(11) << "Total Due:" << right << setw(48) << totalDue << endl << endl << endl;
	}
	else
	{
		dataOut << "***************** BILLING INFORMATION *********************" << endl;
		dataOut << endl;
		dataOut << "You have not selected any classes and do not have any tuition or fees due" << endl;
		dataOut << "You currently have a credit of $" << scholAmount << endl << endl;
	}
dataOut << "Scholarship Information: " << scholTitle << endl;
dataOut << "Scholarship Amount: $" << scholAmount << endl;
dataOut << endl << endl;
}

//****************************************************************************
//
// Print Details Function
//
//****************************************************************************

void printDetails(classType chosenClass, hourType chosenHours, const float TUITIONHOURCOST, const float REGFEES, string firstName, string lastName, int studentID, int howManyClasses, int scholType, string scholTitle, float scholAmount, ofstream& dataOut)

{
	saveSchedule(firstName, lastName, studentID, chosenClass, chosenHours, howManyClasses, dataOut);
	saveBill(firstName, lastName, studentID, chosenClass, chosenHours, TUITIONHOURCOST, REGFEES, howManyClasses, scholType, scholTitle, scholAmount, dataOut);
}

//****************************************************************************
//
// Exit function
//
//****************************************************************************

void exitProgram()
{
	cout << "Thank-you and have a Wonderful Day!!!" << endl;
}

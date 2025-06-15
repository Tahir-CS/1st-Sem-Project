//Quiz management (Semester-1 Project)

//Included Libraries 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  // For rand() and srand()
#include <vector>
#include <ctime> 
#include <sstream>
#include <algorithm>  // For remove function
#include <iomanip>   // For setw and formatting

using namespace std;

//Structuer for email

struct email
{
	string Email, password;
};

//Structuer for courses

struct courses
{
	string subjname;
};

//Structuer of Student Information

struct  student
{
	string name, father, dob, adress, designation, code;
	string dept;
	email st_email, password;
	string cnic, contact;
	int jyear, fee;
	courses st_course;
};

//Structuer of Teacher Information

struct  teacher
{
	string name, father, dob, adress, designation, code;
	string dept;
	email te_email, password;
	string contact, cnic;
	int jyear, bps;
	courses te_courses;
};

struct Question {
	string statement;
	vector<string> options;  // For 4 options
	int correct_option;
	int marks;
};

struct Quiz
{
	string subject;
	string section;
	int session;
	int time;
	int Imarks;
	int totalMarks;
	vector<Question> questions;
	int quizNum;
};

struct QuizResult
{
	string studentEmail;
	string quizSubject;
	int quizNum;
	string section;
	int session;
	int score;
	int totalMarks;
	float percentage;
	string grade;
	string dateTaken;
};

//Global variables/arrays/pointers

vector <Quiz> quizzes;
vector <teacher> teacherinfo;
vector <student> studentinfo;
vector <QuizResult> quizResults;
string currentUserEmail = "";  // Store current logged in user's email

//Functions Used

//Temporary data input function in place of file handling

void data_read();
void quiz_read();
void   display_logo();
//Verify Email

string verifyemail(string login, string password);

//Admin Interface

void admin();

//Menu for Admin's features

void adminMenu();

//Case:1 Teacher Dashboard(Admin)

int teacherdash();
void showteacher(int index);
int studentdash();
void showstudent(int index);
void updatetecher(int index);
void reg_teacher();
void reg_student();
string gen_email(int length);
void removeteach(int index);
void removestd(int index);
void updatestudent(int i);
void displayQuiz(int index);
int quizindex();

//Teacher

void TeacherMenu();

void Teacher();
void createQuiz();

void editQuiz();

//Student

void StudentMenu();
void Student();
void takeQuiz();
void viewAssignedQuizzes();
void viewQuizResults();
void viewGrades();
int getCurrentStudentIndex(string email);
string calculateGrade(float percentage);
void saveQuizResult(QuizResult result);
void loadQuizResults();

//string* input(string* question, string nextq, int& i);
//Function to count lines in a file


int countLines(const string& filename) {
	ifstream file(filename); // Open the file
	if (!file.is_open()) {   // Check if the file opened successfully
		cerr << "Error: Could not open the file " << filename << endl;
		return 0;
	}

	int count = 0;
	string line;
	while (getline(file, line)) { // Read each line
		count++;                  // Increment the counter
	}
	file.close(); // Close the file
	return count;
}

void loadData()
{
	string teacherFile = "Teacher_Info.txt";
	string studentFile = "Student_Info.txt";
	string quizfile = "Quizzes.txt";

	// Count lines in Teacher_Info.txt
	int teacherLines = countLines(teacherFile);
	cout << "Teachers in file: " << teacherLines << endl;

	// Count lines in Student_Info.txt
	int studentLines = countLines(studentFile);
	cout << "Students in file: " << studentLines << endl;

	// Count lines in Student_Info.txt
	int quizLines = countLines(quizfile);

}

//Main function

int main()
{
	system("cls"); // Clear screen at startup
	display_logo(); // Display logo at program start

	loadData(); // C
	// Resize vectors to hold at least one entry
	teacherinfo.resize(countLines("Teacher_Info.txt"));
	studentinfo.resize(countLines("Student_Info.txt"));
	quizzes.resize(countLines("Quizzes.txt"));

	quizzes.resize(3);
	//Temporary input function

	data_read();
	quiz_read();
	loadQuizResults();

	//Variable declaration

	string login;
	string password;
	string verify;

	//Login 
	cout << "\n===============================================================\n";
	cout << "|                        LOGIN SYSTEM                        |\n";
	cout << "===============================================================\n";
	cout << "Enter your email: "; //Email input
	cin >> login;

	cout << "Enter your Password: "; //Password Input
	cin >> password;

	verify = verifyemail(login, password); //Verifying Login Info

	//Admin Interface

	if (verify == "admin")
	{
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                    ADMIN DASHBOARD                       |\n";
		cout << "===============================================================\n";
		admin();
	}

	//Teacher Interface

	else if (verify == "teacher")
	{
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                   TEACHER DASHBOARD                      |\n";
		cout << "===============================================================\n";
		Teacher();

	}

	//Student Interface

	else if (verify == "student")
	{
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                   STUDENT DASHBOARD                      |\n";
		cout << "===============================================================\n";
		Student();
	}

	//Invalid Input

	else
	{
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                        ERROR!                            |\n";
		cout << "|                   Invalid Email/Password                 |\n";
		cout << "===============================================================\n";
	}

	//End of program

	return 0;

}

//Verify Email

string verifyemail(string login, string password)
{
	//Return values

	string admin = "admin", teacher = "teacher", student = "student", error = "error";

	//Returning admin

	if (login == "aduet@edu.pk" && password == "Admin123")
	{
		currentUserEmail = login;
		return admin;
	}

	//Returning teacher
	for (int i = 0; i < teacherinfo.size(); i++) {

		if (login == teacherinfo[i].te_email.Email && password == teacherinfo[i].te_email.password)
		{
			currentUserEmail = login;
			return teacher;
		}
	}

	//Returning student
	for (int i = 0; i < studentinfo.size(); i++) {
		if (login == studentinfo[i].st_email.Email && password == studentinfo[i].st_email.password)
		{
			currentUserEmail = login;
			return student;
		}
	}

	//Returning error

	return error;

}

void admin()
{

	int choice;
	do {
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                    ADMIN DASHBOARD                       |\n";
		cout << "===============================================================\n";
		adminMenu();

		cin >> choice;

		string key;
		int index;

		switch (choice) {

		case 1:
			if (teacherinfo.empty()) {
				cerr << "Error: No teacher information available." << endl;
				return;
			}
			else {

				index = teacherdash();

				showteacher(index);
			}
			break;

		case 2:

			index = studentdash();

			showstudent(index);

			break;

		case 3:
			int update;

			cout << "Who you want to update." << endl;
			cout << "Press 1 for teacher and 2 for student: ";
			cin >> update;

			if (update == 1)
			{
				index = teacherdash();

				updatetecher(index);
			}
			else if (update == 2)
			{
				index = studentdash();

				updatestudent(index);
			}
			break;

		case 4:

			cout << "Register the user (Students and Teachers)." << endl;

			int reg;

			cout << "Who you wanna register('1' for teacher, '2' for student): ";
			cin >> reg;

			if (reg == 1)
			{
				reg_teacher();
			}

			else if (reg == 2)
			{
				reg_student();
			}

			break;

		case 5:

			cout << "Add, remove." << endl;

			int act;

			cout << "Press '1' to add teacher.\n";
			cout << "Press '2' to add student.\n";
			cout << "Press '3' to remove teacher.\n";
			cout << "Press '4' to remove student.\n";

			cin >> act;

			if (act == 1)
			{
				cout << "Add teacher.";
				reg_teacher();

			}
			else if (act == 2)
			{
				cout << "Add student.";
				reg_student();

			}
			else if (act == 3)
			{
				cout << "Remove teacher.";
				index = teacherdash();
				removeteach(index);

			}
			else if (act == 4)
			{
				cout << "Remove student.";
				index = studentdash();
				removestd(index);
			}
			break;
		case 6:

			cout << "Exiting......" << endl;

			break;

		default:

			cout << "Invalid Choice " << endl;

		}

	} while (choice != 6);

}

void adminMenu()
{
	cout << "\n==================================================================\n";
	cout << "|                         ADMIN MENU                            |\n";
	cout << "|================================================================|\n";
	cout << "|  1. Login to teacher dashboard                                 |\n";
	cout << "|  2. Login to student dashboard                                 |\n";
	cout << "|  3. Update information (password, designation, contact etc.)   |\n";
	cout << "|  4. Register new user (Students and Teachers)                  |\n";
	cout << "|  5. Add, remove, search users                                  |\n";
	cout << "|  6. Exit                                                       |\n";
	cout << "==================================================================\n";
	cout << "Enter your choice: ";
}

int teacherdash()
{
	//Variable declaration

	string find;
	int index = -1;  // Initialize with -1 to indicate no match
	//Input to find teacher

	cin.ignore();

	cout << "Enter teachers Name/Code you want to find: ";
	getline(cin, find);

	for (int i = 0; i < teacherinfo.size(); i++)
	{
		if (find == teacherinfo[i].name || find == teacherinfo[i].code)
		{
			index = i;
			break;
		}
	}

	return index;
}

// Temporary data input function in place of file handeling

void data_read()
{
	ifstream read("Teacher_Info.txt");

	//Teacher info input
	char ch;
	string temp;
	if (!read.is_open()) {
		cout << "Error: Could not open Teacher_Info.txt" << endl;
		return;
	}
	else {
		for (int i = 0; i < teacherinfo.size(); i++)
		{

			getline(read, teacherinfo[i].name, '#');
			getline(read, teacherinfo[i].father, '#');

			getline(read, teacherinfo[i].dob, '#');
			getline(read, teacherinfo[i].adress, '#');
			getline(read, teacherinfo[i].designation, '#');
			getline(read, teacherinfo[i].code, '#');
			getline(read, teacherinfo[i].dept, '#');
			getline(read, teacherinfo[i].te_email.Email, '#');
			getline(read, teacherinfo[i].te_email.password, '#');
			getline(read, teacherinfo[i].cnic, '#');
			getline(read, teacherinfo[i].contact, '#');
			read >> teacherinfo[i].jyear;
			read.ignore(); // Ignore newline
			read >> teacherinfo[i].bps;
			read.ignore(); // Ignore newline
			getline(read, teacherinfo[i].te_courses.subjname);
		}
	}

	read.close();

	//Repeat similar process for student info from Student_Info.txt
	ifstream studentRead("Student_Info.txt");
	if (!studentRead.is_open()) {
		cout << "Error: Could not open Student_Info.txt" << endl;
		return;
	}
	else {
		for (int i = 0; i < studentinfo.size(); i++)
		{
			getline(studentRead, studentinfo[i].name, '#');


			getline(studentRead, studentinfo[i].father, '#');
			getline(studentRead, studentinfo[i].dob, '#');
			getline(studentRead, studentinfo[i].adress, '#');
			getline(studentRead, studentinfo[i].designation, '#');
			getline(studentRead, studentinfo[i].code, '#');
			getline(studentRead, studentinfo[i].dept, '#');
			getline(studentRead, studentinfo[i].st_email.Email, '#');
			getline(studentRead, studentinfo[i].st_email.password, '#');
			getline(studentRead, studentinfo[i].cnic, '#');
			getline(studentRead, studentinfo[i].contact, '#');
			studentRead >> studentinfo[i].jyear;
			studentRead.ignore(); // Ignore newline
			studentRead >> studentinfo[i].fee;
			studentRead.ignore(); // Ignore newline
			getline(studentRead, studentinfo[i].st_course.subjname);
		}
	}

	studentRead.close();


}

void showteacher(int index)
{
	if (index < 0 || index >= teacherinfo.size()) {
		cout << "Invalid teacher index." << endl;
		return;
	}
	system("cls");
	cout << "\n==================================================================\n";
	cout << "|                        TEACHER INFORMATION                    |\n";
	cout << "|================================================================|\n";
	cout << "| Name: " << left << setw(55) << teacherinfo[index].name << "|\n";
	cout << "| Father Name: " << left << setw(50) << teacherinfo[index].father << "|\n";
	cout << "| CNIC: " << left << setw(55) << teacherinfo[index].cnic << "|\n";
	cout << "| Date of Birth: " << left << setw(48) << teacherinfo[index].dob << "|\n";
	cout << "| Code: " << left << setw(55) << teacherinfo[index].code << "|\n";
	cout << "| Joining Year: " << left << setw(49) << teacherinfo[index].jyear << "|\n";
	cout << "| Contact: " << left << setw(52) << teacherinfo[index].contact << "|\n";
	cout << "| Email: " << left << setw(54) << teacherinfo[index].te_email.Email << "|\n";
	cout << "| Address: " << left << setw(52) << teacherinfo[index].adress << "|\n";
	cout << "| Department: " << left << setw(49) << teacherinfo[index].dept << "|\n";
	cout << "| Designation: " << left << setw(48) << teacherinfo[index].designation << "|\n";
	cout << "| Subject Name: " << left << setw(47) << teacherinfo[index].te_courses.subjname << "|\n";
	cout << "| BPS: " << left << setw(56) << teacherinfo[index].bps << "|\n";
	cout << "==================================================================\n";
	cout << "\nPress Enter to continue...";
	cin.ignore();
	cin.get();
}

int studentdash()
{

	string find;
	int index = -1;  // Initialize with -1 to indicate no match
	//Input to find teacher

	cin.ignore();

	cout << "Enter student Name/Code you want to find: ";
	getline(cin, find);

	for (int i = 0; i < studentinfo.size(); i++)
	{
		if (find == studentinfo[i].name || find == studentinfo[i].code)
		{
			index = i;
			break;
		}
	}

	return index;
}

void showstudent(int index)
{
	if (index < 0 || index >= studentinfo.size()) {
		cout << "Invalid student index." << endl;
		return;
	}
	system("cls");
	cout << "\n==================================================================\n";
	cout << "|                        STUDENT INFORMATION                    |\n";
	cout << "|================================================================|\n";
	cout << "| Name: " << left << setw(55) << studentinfo[index].name << "|\n";
	cout << "| Father Name: " << left << setw(50) << studentinfo[index].father << "|\n";
	cout << "| CNIC: " << left << setw(55) << studentinfo[index].cnic << "|\n";
	cout << "| Date of Birth: " << left << setw(48) << studentinfo[index].dob << "|\n";
	cout << "| Code: " << left << setw(55) << studentinfo[index].code << "|\n";
	cout << "| Joining Year: " << left << setw(49) << studentinfo[index].jyear << "|\n";
	cout << "| Contact: " << left << setw(52) << studentinfo[index].contact << "|\n";
	cout << "| Email: " << left << setw(54) << studentinfo[index].st_email.Email << "|\n";
	cout << "| Address: " << left << setw(52) << studentinfo[index].adress << "|\n";
	cout << "| Department: " << left << setw(49) << studentinfo[index].dept << "|\n";
	cout << "| Designation: " << left << setw(48) << studentinfo[index].designation << "|\n";
	cout << "| Subject Name: " << left << setw(47) << studentinfo[index].st_course.subjname << "|\n";
	cout << "| Fee: " << left << setw(56) << studentinfo[index].fee << "|\n";
	cout << "==================================================================\n";
	cout << "\nPress Enter to continue...";
	cin.ignore();
	cin.get();
}

void updatetecher(int i)
{
	if (i < 0 || i >= teacherinfo.size()) {
		cout << "Invalid teacher index." << endl;
		return;
	}

	int update;
	cout << "What you want to update." << endl;

	do {
		cout << "Press '1' to update contact.\n";
		cout << "Press '2' to update Adress.\n";
		cout << "Press '3' to update Designation.\n";
		cout << "Press '4' to update Department.\n";
		cout << "Press '5' to update Courses.\n";
		cout << "Press '6' to Exit.\n";
		cin >> update;

		switch (update)
		{
		case 1:

			cout << "Enter contact: ";
			cin >> teacherinfo[i].contact;
			break;
		case 2:

			cout << "New Adress: ";
			cin >> teacherinfo[i].adress;
			break;
		case 3:

			cout << "New designation: ";
			cin >> teacherinfo[i].designation;
			break;
		case 4:

			cout << "New department: ";
			cin >> teacherinfo[i].dept;
			break;

		case 5:

			cout << "New courses: ";
			getline(cin, teacherinfo[i].te_courses.subjname);
			break;
		case 6:
			cout << "Exiting...";
			break;

		default:
			cout << "Invalid choice.";
		}
	} while (update != 6);
}

void updatestudent(int i)
{
	if (i < 0 || i >= studentinfo.size()) {
		cout << "Invalid student index." << endl;
		return;
	}

	int update;
	cout << "What you want to update." << endl;

	do {
		cout << "Press '1' to update contact.\n";
		cout << "Press '2' to update Adress.\n";
		cout << "Press '3' to update Designation.\n";
		cout << "Press '4' to update Department.\n";
		cout << "Press '5' to update Courses.\n";
		cout << "Press '6' to Exit.\n";
		cin >> update;

		switch (update)
		{

		case 1:

			cout << "Enter contact: ";
			cin >> studentinfo[i].contact;
			break;
		case 2:

			cout << "New Adress: ";
			cin >> studentinfo[i].adress;
			break;
		case 3:

			cout << "New designation: ";
			cin >> studentinfo[i].designation;
			break;
		case 4:

			cout << "New department: ";
			cin >> studentinfo[i].dept;
			break;

		case 5:

			cout << "New courses: ";
			getline(cin, studentinfo[i].st_course.subjname);
			break;
		case 6:
			cout << "Exiting...";
			break;

		default:
			cout << "Invalid choice.";
		}
	} while (update != 6);
}

void reg_teacher()
{
	ofstream write("Teacher_Info.txt", ios::app);  // Append mode

	//Teacher info input

	teacherinfo.resize(teacherinfo.size() + 1);  // Add a new entry
	int i = teacherinfo.size() - 1;  // Index of the new entry

	cout << "Enter teacher " << i + 1 << " info." << endl;

	cin.ignore();

	cout << "Enter Name: ";
	getline(cin, teacherinfo[i].name);

	write << teacherinfo[i].name << "#";

	cin.ignore();
	cout << "Enter Father name: ";
	getline(cin, teacherinfo[i].father);

	write << teacherinfo[i].father << "#";

	cout << "Enter Date of Birth: ";
	getline(cin, teacherinfo[i].dob);

	write << teacherinfo[i].dob << "#";

	cout << "Enter Address: ";
	getline(cin, teacherinfo[i].adress);

	write << teacherinfo[i].adress << "#";

	cout << "Enter the designation: ";
	getline(cin, teacherinfo[i].designation);

	write << teacherinfo[i].designation << "#";

	cout << "Enter the code: ";
	getline(cin, teacherinfo[i].code);

	write << teacherinfo[i].code << "#";

	cout << "Enter the department: ";
	getline(cin, teacherinfo[i].dept);

	write << teacherinfo[i].dept << "#";

	// Remove spaces from department name for email
	string deptNoSpaces = teacherinfo[i].dept;
	deptNoSpaces.erase(remove(deptNoSpaces.begin(), deptNoSpaces.end(), ' '), deptNoSpaces.end());

	teacherinfo[i].te_email.Email = "te" + teacherinfo[i].code + deptNoSpaces + "@uet.edu.pk";
	write << teacherinfo[i].te_email.Email << "#";

	teacherinfo[i].te_email.password = gen_email(5);
	write << teacherinfo[i].te_email.password << "#";

	cout << "Enter the CNIC: ";
	getline(cin, teacherinfo[i].cnic);

	write << teacherinfo[i].cnic << "#";

	cout << "Enter the contact(without dashes): ";
	getline(cin, teacherinfo[i].contact);

	write << teacherinfo[i].contact << "#";

	cout << "Enter the joining year: ";
	cin >> teacherinfo[i].jyear;

	write << teacherinfo[i].jyear << "#";

	cout << "Enter the BPS: ";
	cin >> teacherinfo[i].bps;

	write << teacherinfo[i].bps << "#";

	cin.ignore();

	cout << "Enter the subject name: ";
	getline(cin, teacherinfo[i].te_courses.subjname);

	write << teacherinfo[i].te_courses.subjname << "#" << endl;

	write.close();
}

void reg_student()
{
	ofstream write("Student_Info.txt", ios::app);  // Append mode

	studentinfo.resize(studentinfo.size() + 1);  // Add a new entry
	int i = studentinfo.size() - 1;  // Index of the new entry

	cout << "Enter student " << i + 1 << " info." << endl;

	cin.ignore();

	cout << "Enter Name: ";
	getline(cin, studentinfo[i].name);

	write << studentinfo[i].name << "#";

	cout << "Enter Father name: ";
	getline(cin, studentinfo[i].father);

	write << studentinfo[i].father << "#";

	cout << "Enter Date of Birth: ";
	getline(cin, studentinfo[i].dob);

	write << studentinfo[i].dob << "#";

	cout << "Enter the address: ";
	getline(cin, studentinfo[i].adress);

	write << studentinfo[i].adress << "#";

	cout << "Enter the Semester: ";
	getline(cin, studentinfo[i].designation);

	write << studentinfo[i].designation << "#";

	cout << "Enter the Regd.no: ";
	getline(cin, studentinfo[i].code);

	write << studentinfo[i].code << "#";

	cout << "Enter the department: ";
	getline(cin, studentinfo[i].dept);

	write << studentinfo[i].dept << "#";

	string key1 = "st", key2 = "@uet.edu.pk";
	
	// Remove spaces from department name for email
	string deptNoSpaces = studentinfo[i].dept;
	deptNoSpaces.erase(remove(deptNoSpaces.begin(), deptNoSpaces.end(), ' '), deptNoSpaces.end());
	
	studentinfo[i].st_email.Email = key1 + studentinfo[i].code + deptNoSpaces + key2;
	write << studentinfo[i].st_email.Email << "#";

	studentinfo[i].st_email.password = gen_email(5);
	write << studentinfo[i].st_email.password << "#";

	cout << "Enter the CNIC: ";
	getline(cin, studentinfo[i].cnic);

	write << studentinfo[i].cnic << "#";

	cout << "Enter the contact(without dashes): ";
	getline(cin, studentinfo[i].contact);

	write << studentinfo[i].contact << "#";

	cout << "Enter the joining year: ";
	cin >> studentinfo[i].jyear;

	write << studentinfo[i].jyear << "#";

	cout << "Enter the Fee: ";
	cin >> studentinfo[i].fee;

	write << studentinfo[i].fee << "#";

	cin.ignore();

	cout << "Enter the courses: ";
	getline(cin, studentinfo[i].st_course.subjname);

	write << studentinfo[i].st_course.subjname << "#" << endl;

	write.close();
}

string gen_email(int length)
{
	const string digits = "0123456789";
	string password = "";

	srand(time(0));

	for (int i = 0; i < length; ++i) {
		int randomIndex = rand() % digits.length();
		password += digits[randomIndex];
	}

	return password;
}
void removeteach(int index) {
	if (index >= 0 && index < teacherinfo.size()) {
		teacherinfo.erase(teacherinfo.begin() + index);
		cout << "Student removed successfully.\n";

		ofstream write("Teacher_Info.txt", ios::trunc);
		if (write.is_open()) {
			for (const auto& t : teacherinfo) {
				write << t.name << "#" << t.father << "#" << t.dob << "#" << t.adress << "#"
					<< t.designation << "#" << t.code << "#" << t.dept << "#"
					<< t.te_email.Email << "#" << t.te_email.password << "#" << t.cnic << "#"
					<< t.contact << "#" << t.jyear << "#" << t.bps << "#"
					<< t.te_courses.subjname << endl;
			}
			write.close();
		}
		else {
			cerr << "Error opening Teacher_Info.txt for writing." << endl;
		}
	}
	else {
		cout << "Invalid index. No teacher removed.\n";
	}
}
void removestd(int index) {
	if (index >= 0 && index < studentinfo.size()) {
		studentinfo.erase(studentinfo.begin() + index); // Remove student at the specified index
		cout << "Student removed successfully.\n";

		// Rewrite the Student_Info.txt file with the updated data
		ofstream write("Student_Info.txt", ios::trunc); // Truncate file to clear previous content
		if (write.is_open()) {
			for (const auto& s : studentinfo) {
				write << s.name << "#" << s.father << "#" << s.dob << "#" << s.adress << "#"
					<< s.designation << "#" << s.code << "#" << s.dept << "#"
					<< s.st_email.Email << "#" << s.st_email.password << "#" << s.cnic << "#"
					<< s.contact << "#" << s.jyear << "#" << s.fee << "#"
					<< s.st_course.subjname << endl;
			}
			write.close();
		}
		else {
			cerr << "Error opening Student_Info.txt for writing." << endl;
		}
	}
	else {
		cout << "Invalid index. No student removed.\n";
	}
}



//Teacher atarts here
void createQuiz()
{
	int i = quizzes.size();

	quizzes.resize(i + 1);

	cin.ignore();

	cout << "Enter Quiz Subject: ";
	getline(cin, quizzes[i].subject);

	cout << "Enter the session: ";
	cin >> quizzes[i].session;

	cin.ignore();

	cout << "Enter the Section: ";
	getline(cin, quizzes[i].section);

	cout << "Enter the quiz number: ";
	cin >> quizzes[i].quizNum;

	cout << "Enter Time Limit (in minutes): ";
	cin >> quizzes[i].time;

	cout << "Enter Total Marks: ";
	cin >> quizzes[i].totalMarks;

	cout << "Enter individual question marks: ";
	cin >> quizzes[i].Imarks;

	cin.ignore();


	string input;
	while (true) {
		Question newQuestion;

		cout << "\nEnter question statement (or type 'done' to finish): ";
		getline(cin, input);
		if (input == "done") break;

		newQuestion.statement = input;

		// Get 4 options
		for (int j = 0; j < 4; j++) {
			cout << "Enter option " << j << ": ";
			string option;
			getline(cin, option);
			newQuestion.options.push_back(option);
		}

		cout << "Enter correct option number (1-4): ";
		cin >> newQuestion.correct_option;
		cin.ignore();

		quizzes[i].questions.push_back(newQuestion);
	}

	//	quizzes[i].push_back(quizzes);
	cout << "\nQuiz created successfully!\n";

	ofstream write("Quizzes.txt", ios::app);
	if (write.is_open())
	{
		// Write quiz header information
		write << quizzes[i].subject << "#";
		write << quizzes[i].session << "#";
		write << quizzes[i].section << "#";
		write << quizzes[i].quizNum << "#";
		write << quizzes[i].totalMarks << "#";
		write << quizzes[i].Imarks << "#";
		write << quizzes[i].time << "#";
		write << quizzes[i].questions.size() << "#";  // Write number of questions

		// Write each question's data
		for (int q = 0; q < quizzes[i].questions.size(); q++)
		{
			write << quizzes[i].questions[q].statement << "#";
			for (int j = 0; j < 4; j++)
			{
				write << quizzes[i].questions[q].options[j] << "#";
			}
			write << quizzes[i].questions[q].correct_option << "#";
		}
		write << endl;  // End this quiz entry with a newline
	}
	else
	{
		cout << "Error: Could not open Quizzes.txt\n";
	}
	write.close();

}

void editQuiz() {

	string subject, section;
	int quizNum, session, quizIndex;

	if (quizzes.empty()) {
		cout << "No quizzes available to edit.\n";
		return;
	}
	cin.ignore();

	quizIndex = quizindex();

	if (quizIndex < 0 || quizIndex >= quizzes.size()) {
		cout << "Invalid quiz selection.\n";
		return;
	}

	Quiz& quiz = quizzes[quizIndex];
	int choice;

	do {
		cout << "\nEdit Quiz Menu:\n";
		cout << "1. Add new question\n";
		cout << "2. Delete question\n";
		cout << "3. View current questions\n";
		cout << "4. Edit quiz details\n";
		cout << "5. Return to main menu\n";
		cout << "Enter choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1: { // Add new question
			Question newQuestion;
			cout << "Enter question statement: ";
			getline(cin, newQuestion.statement);

			// Get 4 options
			for (int i = 1; i <= 4; i++) {
				cout << "Enter option " << i << ": ";
				string option;
				getline(cin, option);
				newQuestion.options.push_back(option);
			}

			cout << "Enter correct option number (1-4): ";
			cin >> newQuestion.correct_option;
			cin.ignore();

			quiz.questions.push_back(newQuestion);
			cout << "Question added successfully!\n";
			break;
		}

		case 2: { // Delete question
			if (quiz.questions.empty()) {
				cout << "No questions to delete.\n";
				break;
			}

			cout << "\nCurrent Questions:\n";
			for (int i = 0; i < quiz.questions.size(); i++) {
				cout << i + 1 << ". " << quiz.questions[i].statement << endl;
			}

			int deleteIndex;
			cout << "Enter question number to delete (1-" << quiz.questions.size() << "): ";
			cin >> deleteIndex;
			deleteIndex--; // Convert to 0-based index

			if (deleteIndex >= 0 && deleteIndex < quiz.questions.size()) {
				quiz.questions.erase(quiz.questions.begin() + deleteIndex);
				cout << "Question deleted successfully!\n";
			}
			else {
				cout << "Invalid question number.\n";
			}
			break;
		}

		case 3: { // View current questions
			cout << "\nCurrent Questions:\n";
			for (int i = 0; i < quiz.questions.size(); i++) {
				cout << "\nQuestion " << i + 1 << ": " << quiz.questions[i].statement << endl;
				for (int j = 0; j < quiz.questions[i].options.size(); j++) {
					cout << j + 1 << ") " << quiz.questions[i].options[j] << endl;
				}
				cout << "Correct answer: Option " << quiz.questions[i].correct_option << endl;
			}
			break;
		}

		case 4: { // Edit quiz details
			cout << "\nCurrent quiz details:";
			cout << "\nSubject: " << quiz.subject;
			cout << "\nTitle: " << quiz.section;
			cout << "\nTime limit: " << quiz.time;
			cout << "\nTotal marks: " << quiz.totalMarks;

			cout << "\n\nEnter new details (press Enter to keep current value):";

			string input;
			cout << "\nNew subject: ";
			getline(cin, input);
			if (!input.empty()) quiz.subject = input;

			cout << "New title: ";
			getline(cin, input);
			if (!input.empty()) quiz.section = input;

			cout << "New time limit (minutes): ";
			getline(cin, input);
			if (!input.empty()) quiz.time = stoi(input);

			cout << "New total marks: ";
			getline(cin, input);
			if (!input.empty()) quiz.totalMarks = stoi(input);

			cout << "Quiz details updated successfully!\n";
			break;
		}

		case 5:
			cout << "Returning to main menu...\n";
			break;

		default:
			cout << "Invalid choice. Please try again.\n";
		}



	} while (choice != 5);
}



void TeacherMenu()
{
	cout << "\n==================================================================\n";
	cout << "|                        TEACHER MENU                           |\n";
	cout << "|================================================================|\n";
	cout << "|  1. View your dashboard                                        |\n";
	cout << "|  2. View student dashboard                                     |\n";
	cout << "|  3. Create quiz                                                |\n";
	cout << "|  4. View or edit questions                                     |\n";
	cout << "|  5. Manage users (Add/Remove)                                  |\n";
	cout << "|  6. Exit                                                       |\n";
	cout << "==================================================================\n";
	cout << "Enter your choice: ";
}



void displayQuiz(int index) {

	if (index >= quizzes.size()) {
		cout << "Invalid quiz index!" << endl;
		return;
	}

	Quiz* quiz = &quizzes[index]; // Access the quiz by index
	cout << "\nQuiz Subject: " << quiz->subject << endl;
	cout << "Title: " << quiz->session << endl;
	cout << "Time Limit: " << quiz->time << " minutes" << endl;
	cout << "Total Marks: " << quiz->totalMarks << endl;
	cout << "\nQuestions:\n";

	for (size_t i = 0; i < quiz->questions.size(); i++) {
		cout << "\nQ" << i + 1 << " (" << quiz->questions[i].marks << " marks): "
			<< quiz->questions[i].statement << endl;
		for (size_t j = 0; j < quiz->questions[i].options.size(); j++) {
			cout << j + 1 << ") " << quiz->questions[i].options[j] << endl;
		}
	}
}

void Teacher()
{

	int choice;
	do {
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                   TEACHER DASHBOARD                      |\n";
		cout << "===============================================================\n";
		TeacherMenu();

		cin >> choice;

		int index;

		switch (choice) {

		case 1:
			if (teacherinfo.empty()) {
				cerr << "Error: No teacher information available." << endl;
				return;
			}
			else {
				index = teacherdash();

				showteacher(index);
			}
			break;

		case 2:

			index = studentdash();

			showstudent(index);

			break;


		case 3:
			cout << "Create your quiz " << endl;
			createQuiz();
			break;


		case 4:
			int reg;

			cout << "Press 1 to display or view quiz,2 to  edit quiz .";
			cin >> reg;

			if (reg == 1)
			{
				index = quizindex();

				displayQuiz(index);
			}

			else if (reg == 2)
			{

				editQuiz();
			}

			break;

		case 5:

			cout << "Add, remove." << endl;

			int act;

			cout << "Press '1' to add teacher.\n";
			cout << "Press '2' to add student.\n";
			cout << "Press '3' to remove teacher.\n";
			cout << "Press '4' to remove student.\n";

			cin >> act;

			if (act == 1)
			{
				cout << "Add teacher.";
				reg_teacher();

			}
			else if (act == 2)
			{
				cout << "Add student.";
				reg_student();

			}
			else if (act == 3)
			{
				cout << "Remove teacher.";
				index = teacherdash();
				removeteach(index);

			}
			else if (act == 4)
			{
				cout << "Remove student.";
				index = studentdash();
				removestd(index);
			}
			break;
		case 6:

			cout << "Exiting......" << endl;

			break;

		default:

			cout << "Invalid Choice " << endl;

		}

	} while (choice != 6);
}

int quizindex()
{
	//Variable declaration

	string section, subName;
	int session, quizNum;

	int index = -1;  // Initialize with -1 to indicate no match
	//Input to find teacher

	cin.ignore();

	cout << "Enter the Subject name: ";
	getline(cin, subName);

	cout << "Enter the session";
	cin >> session;

	cout << "Enter the section ";
	cin >> section;

	cout << "Enter Quiz number: ";
	cin >> quizNum;

	for (int i = 0; i < quizzes.size(); i++)
	{
		if (subName == quizzes[i].subject && session == quizzes[i].session && section == quizzes[i].section && quizzes[i].quizNum == quizNum)
		{
			index = i;
			break;
		}
	}

	return index;
}

void quiz_read()
{
	ifstream read("Quizzes.txt");

	if (!read.is_open()) {
		cout << "Error: Could not open Quizzes.txt" << endl;
		return;
	}

	string line;
	int quizIndex = 0;

	while (getline(read, line) && quizIndex < quizzes.size()) {
		stringstream ss(line);
		string item;

		// Read quiz header information
		getline(ss, quizzes[quizIndex].subject, '#');

		string sessionStr;
		getline(ss, sessionStr, '#');
		quizzes[quizIndex].session = stoi(sessionStr);

		getline(ss, quizzes[quizIndex].section, '#');

		string quizNumStr;
		getline(ss, quizNumStr, '#');
		quizzes[quizIndex].quizNum = stoi(quizNumStr);

		string totalMarksStr;
		getline(ss, totalMarksStr, '#');
		quizzes[quizIndex].totalMarks = stoi(totalMarksStr);

		string imarksStr;
		getline(ss, imarksStr, '#');
		quizzes[quizIndex].Imarks = stoi(imarksStr);

		string timeStr;
		getline(ss, timeStr, '#');
		quizzes[quizIndex].time = stoi(timeStr);

		string numQuestionsStr;
		getline(ss, numQuestionsStr, '#');
		int numQuestions = stoi(numQuestionsStr);

		// Read questions
		for (int q = 0; q < numQuestions; q++) {
			Question question;

			getline(ss, question.statement, '#');

			// Read 4 options
			for (int j = 0; j < 4; j++) {
				string option;
				getline(ss, option, '#');
				question.options.push_back(option);
			}

			string correctOptionStr;
			getline(ss, correctOptionStr, '#');
			question.correct_option = stoi(correctOptionStr);

			quizzes[quizIndex].questions.push_back(question);
		}

		quizIndex++;
	}

	read.close();
}
void display_logo()
{
    cout << "\\n";
    cout << "   ____  _   _ _____ ______   __  __          _  ________ _____  \\n";
    cout << "  / __ \\| | | |_   _|___  /  |  \\/  |   /\\   | |/ /  ____|  __ \\ \\n";
    cout << " | |  | | | | | | |    / /   | \\  / |  /  \\  | ' /| |__  | |__) |\\n";
    cout << " | |  | | | | | | |   / /    | |\\/| | / /\\ \\ |  < |  __| |  _  / \\n";
    cout << " | |__| | |_| |_| |_ / /__   | |  | |/ ____ \\| . \\| |____| | \\ \\ \\n";
    cout << "  \\___\\_\\\\\\___/|_____|_____|  |_|  |_/_/    \\_\\_|\\_\\______|_|  \\_\\\\\\n";
    cout << "=================================================================\\n";
    cout << "           Welcome to the Quiz Management System!               \\n";
    cout << "=================================================================\\n";
}

//Student functions start here

void StudentMenu()
{
	cout << "\n==================================================================\n";
	cout << "|                        STUDENT MENU                           |\n";
	cout << "|================================================================|\n";
	cout << "|  1. View your dashboard                                        |\n";
	cout << "|  2. View assigned quizzes                                      |\n";
	cout << "|  3. Take a quiz                                                |\n";
	cout << "|  4. View quiz results                                          |\n";
	cout << "|  5. View grades                                                |\n";
	cout << "|  6. Update your information                                    |\n";
	cout << "|  7. Exit                                                       |\n";
	cout << "==================================================================\n";
	cout << "Enter your choice: ";
}

void Student()
{
	int choice;
	do {
		system("cls");
		cout << "\n===============================================================\n";
		cout << "|                   STUDENT DASHBOARD                      |\n";
		cout << "===============================================================\n";
		StudentMenu();

		cin >> choice;

		switch (choice) {
		case 1:
			// View student dashboard - show current student's info
			{
				int currentIndex = getCurrentStudentIndex(currentUserEmail);
				if (currentIndex != -1) {
					cout << "\n=== Your Dashboard ===" << endl;
					showstudent(currentIndex);
				}
				else {
					cout << "Error: Student information not found." << endl;
				}
			}
			break;

		case 2:
			// View assigned quizzes
			viewAssignedQuizzes();
			break;

		case 3:
			// Take a quiz
			takeQuiz();
			break;

		case 4:
			// View quiz results
			viewQuizResults();
			break;

		case 5:
			// View grades
			viewGrades();
			break;

		case 6:
			// Update student information
			{
				int currentIndex = getCurrentStudentIndex(currentUserEmail);
				if (currentIndex != -1) {
					updatestudent(currentIndex);
				}
				else {
					cout << "Error: Student information not found." << endl;
				}
			}
			break;

		case 7:
			cout << "Exiting Student Dashboard..." << endl;
			break;

		default:
			cout << "Invalid Choice" << endl;
		}

	} while (choice != 7);
}

void takeQuiz()
{
	if (quizzes.empty()) {
		system("cls");
		cout << "\n==================================================================\n";
		cout << "|                          ERROR!                             |\n";
		cout << "|                 No quizzes available at the moment.         |\n";
		cout << "==================================================================\n";
		cout << "\nPress Enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	system("cls");
	// Display available quizzes
	cout << "\n==================================================================\n";
	cout << "|                        AVAILABLE QUIZZES                      |\n";
	cout << "|================================================================|\n";
	for (int i = 0; i < quizzes.size(); i++) {
		cout << "| " << i + 1 << ". Subject: " << left << setw(20) << quizzes[i].subject 
			 << " Section: " << left << setw(10) << quizzes[i].section 
			 << " Quiz #" << quizzes[i].quizNum << " |\n";
	}
	cout << "==================================================================\n";

	int quizChoice;
	cout << "\nSelect quiz number (1-" << quizzes.size() << "): ";
	cin >> quizChoice;
	quizChoice--; // Convert to 0-based index

	if (quizChoice < 0 || quizChoice >= quizzes.size()) {
		cout << "\n==================================================================\n";
		cout << "|                      Invalid Selection!                     |\n";
		cout << "==================================================================\n";
		cout << "\nPress Enter to continue...";
		cin.ignore();
		cin.get();
		return;
	}

	Quiz& selectedQuiz = quizzes[quizChoice];
	int score = 0;
	int totalQuestions = selectedQuiz.questions.size();

	system("cls");
	cout << "\n==================================================================\n";
	cout << "|                        QUIZ STARTING                          |\n";
	cout << "|================================================================|\n";
	cout << "| Subject: " << left << setw(54) << selectedQuiz.subject << "|\n";
	cout << "| Time Limit: " << left << setw(49) << (to_string(selectedQuiz.time) + " minutes") << "|\n";
	cout << "| Total Questions: " << left << setw(44) << totalQuestions << "|\n";
	cout << "==================================================================\n";
	cout << "\nPress Enter to start...";
	cin.ignore();
	cin.get();

	// Present each question
	for (int i = 0; i < totalQuestions; i++) {
		system("cls");
		cout << "\n==================================================================\n";
		cout << "| Question " << left << setw(3) << (i + 1) << " of " << left << setw(47) << totalQuestions << "|\n";
		cout << "|================================================================|\n";
		cout << "| " << left << setw(64) << selectedQuiz.questions[i].statement << "|\n";
		cout << "|================================================================|\n";
		
		for (int j = 0; j < selectedQuiz.questions[i].options.size(); j++) {
			cout << "| " << (j + 1) << ") " << left << setw(61) << selectedQuiz.questions[i].options[j] << "|\n";
		}
		cout << "==================================================================\n";

		int userAnswer;
		cout << "\nYour answer (1-4): ";
		cin >> userAnswer;

		if (userAnswer == selectedQuiz.questions[i].correct_option) {
			cout << "\n* Correct!\n";
			score += selectedQuiz.Imarks;
		}
		else {
			cout << "\nX Incorrect. The correct answer was: " 
				 << selectedQuiz.questions[i].correct_option << "\n";
		}
		cout << "\nPress Enter to continue...";
		cin.ignore();
		cin.get();
	}

	// Display final score and save result
	system("cls");
	cout << "\n==================================================================\n";
	cout << "|                        QUIZ COMPLETED                         |\n";
	cout << "|================================================================|\n";
	float percentage = (float)score / selectedQuiz.totalMarks * 100;
	cout << "| Your Score: " << left << setw(51) << (to_string(score) + "/" + to_string(selectedQuiz.totalMarks)) << "|\n";
	cout << "| Percentage: " << left << setw(51) << (to_string((int)percentage) + "%") << "|\n";
	
	// Save quiz result
	QuizResult result;
	result.studentEmail = currentUserEmail;
	result.quizSubject = selectedQuiz.subject;
	result.quizNum = selectedQuiz.quizNum;
	result.section = selectedQuiz.section;
	result.session = selectedQuiz.session;
	result.score = score;
	result.totalMarks = selectedQuiz.totalMarks;
	result.percentage = percentage;
	result.grade = calculateGrade(percentage);
	
	// Get current date (simplified)
	time_t now = time(0);
	char* timeStr = ctime(&now);
	result.dateTaken = string(timeStr);
	result.dateTaken.pop_back(); // Remove newline character
	
	saveQuizResult(result);
	cout << "| Grade: " << left << setw(56) << result.grade << "|\n";
	cout << "==================================================================\n";
	cout << "\nQuiz result saved successfully!";
	cout << "\nPress Enter to continue...";
	cin.ignore();
	cin.get();
}

// Get current student index by email
int getCurrentStudentIndex(string email) {
	for (int i = 0; i < studentinfo.size(); i++) {
		if (studentinfo[i].st_email.Email == email) {
			return i;
		}
	}
	return -1; // Not found
}

// View assigned quizzes for current student
void viewAssignedQuizzes() {
	int currentIndex = getCurrentStudentIndex(currentUserEmail);
	if (currentIndex == -1) {
		cout << "Error: Student information not found." << endl;
		return;
	}
	
	string studentDept = studentinfo[currentIndex].dept;
	string studentSection = studentinfo[currentIndex].designation; // Using designation as section/semester
	
	cout << "\n=== Assigned Quizzes ===" << endl;
	cout << "Department: " << studentDept << endl;
	cout << "Section/Semester: " << studentSection << endl << endl;
	
	bool hasQuizzes = false;
	
	for (int i = 0; i < quizzes.size(); i++) {
		// Show quizzes for student's department or general quizzes
		if (quizzes[i].section == studentSection || quizzes[i].section == "All") {
			hasQuizzes = true;
			cout << "Quiz " << i + 1 << ":" << endl;
			cout << "  Subject: " << quizzes[i].subject << endl;
			cout << "  Section: " << quizzes[i].section << endl;
			cout << "  Quiz Number: " << quizzes[i].quizNum << endl;
			cout << "  Session: " << quizzes[i].session << endl;
			cout << "  Time Limit: " << quizzes[i].time << " minutes" << endl;
			cout << "  Total Marks: " << quizzes[i].totalMarks << endl;
			cout << "  Total Questions: " << quizzes[i].questions.size() << endl;
			cout << "  ---------------------------" << endl;
		}
	}
	
	if (!hasQuizzes) {
		cout << "No quizzes assigned for your section." << endl;
	}
}

// View quiz results for current student
void viewQuizResults() {
	cout << "\n=== Your Quiz Results ===" << endl;
	
	bool hasResults = false;
	
	for (int i = 0; i < quizResults.size(); i++) {
		if (quizResults[i].studentEmail == currentUserEmail) {
			hasResults = true;
			cout << "\nQuiz Result " << i + 1 << ":" << endl;
			cout << "  Subject: " << quizResults[i].quizSubject << endl;
			cout << "  Quiz Number: " << quizResults[i].quizNum << endl;
			cout << "  Section: " << quizResults[i].section << endl;
			cout << "  Session: " << quizResults[i].session << endl;
			cout << "  Score: " << quizResults[i].score << "/" << quizResults[i].totalMarks << endl;
			cout << "  Percentage: " << quizResults[i].percentage << "%" << endl;
			cout << "  Grade: " << quizResults[i].grade << endl;
			cout << "  Date Taken: " << quizResults[i].dateTaken << endl;
			cout << "  ---------------------------" << endl;
		}
	}
	
	if (!hasResults) {
		cout << "No quiz results found. Take some quizzes first!" << endl;
	}
}

// View grades summary for current student
void viewGrades() {
	cout << "\n=== Your Grades Summary ===" << endl;
	
	bool hasResults = false;
	float totalPercentage = 0;
	int totalQuizzes = 0;
	
	for (int i = 0; i < quizResults.size(); i++) {
		if (quizResults[i].studentEmail == currentUserEmail) {
			hasResults = true;
			totalQuizzes++;
			totalPercentage += quizResults[i].percentage;
			
			cout << quizResults[i].quizSubject << " (Quiz #" << quizResults[i].quizNum << "): " 
				 << quizResults[i].grade << " (" << quizResults[i].percentage << "%)" << endl;
		}
	}
	
	if (hasResults) {
		float averagePercentage = totalPercentage / totalQuizzes;
		cout << "\n--- Summary ---" << endl;
		cout << "Total Quizzes Taken: " << totalQuizzes << endl;
		cout << "Average Percentage: " << averagePercentage << "%" << endl;
		cout << "Overall Grade: " << calculateGrade(averagePercentage) << endl;
	} else {
		cout << "No grades found. Take some quizzes first!" << endl;
	}
}

// Calculate grade based on percentage
string calculateGrade(float percentage) {
	if (percentage >= 90) return "A+";
	else if (percentage >= 85) return "A";
	else if (percentage >= 80) return "A-";
	else if (percentage >= 75) return "B+";
	else if (percentage >= 70) return "B";
	else if (percentage >= 65) return "B-";
	else if (percentage >= 60) return "C+";
	else if (percentage >= 55) return "C";
	else if (percentage >= 50) return "C-";
	else if (percentage >= 45) return "D";
	else return "F";
}

// Save quiz result to file and memory
void saveQuizResult(QuizResult result) {
	// Add to memory vector
	quizResults.push_back(result);
	
	// Save to file
	ofstream file("QuizResults.txt", ios::app);
	if (file.is_open()) {
		file << result.studentEmail << "#" 
			 << result.quizSubject << "#" 
			 << result.quizNum << "#" 
			 << result.section << "#" 
			 << result.session << "#" 
			 << result.score << "#" 
			 << result.totalMarks << "#" 
			 << result.percentage << "#" 
			 << result.grade << "#" 
			 << result.dateTaken << endl;
		file.close();
	} else {
		cout << "Error: Could not save quiz result to file." << endl;
	}
}

// Load quiz results from file
void loadQuizResults() {
	ifstream file("QuizResults.txt");
	if (!file.is_open()) {
		// File doesn't exist yet, that's okay
		return;
	}
	
	string line;
	while (getline(file, line)) {
		if (line.empty()) continue;
		
		stringstream ss(line);
		QuizResult result;
		
		getline(ss, result.studentEmail, '#');
		getline(ss, result.quizSubject, '#');
		
		string temp;
		getline(ss, temp, '#');
		result.quizNum = stoi(temp);
		
		getline(ss, result.section, '#');
		
		getline(ss, temp, '#');
		result.session = stoi(temp);
		
		getline(ss, temp, '#');
		result.score = stoi(temp);
		
		getline(ss, temp, '#');
		result.totalMarks = stoi(temp);
		
		getline(ss, temp, '#');
		result.percentage = stof(temp);
		
		getline(ss, result.grade, '#');
		getline(ss, result.dateTaken);
		
		quizResults.push_back(result);
	}
	
	file.close();
}

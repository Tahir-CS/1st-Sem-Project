✅ Source.cpp
✅ Project1.vcxproj
✅ Project1.vcxproj.filters
✅ README.md
✅ Teacher_Info.txt
✅ Student_Info.txt
✅ Quizzes.txt
✅ Login page.png
✅ ADmin dashbaord.png
✅ Teacher dashboard.png
✅ student dashboard.png
# Quiz Management System

A comprehensive C++ console-based Quiz Management System developed as a 1st Semester Programming Fundamentals project. This system provides role-based access for administrators, teachers, and students with full quiz creation, management, and evaluation capabilities.

## 📋 Table of Contents
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Default Login Credentials](#default-login-credentials)
- [Screenshots](#screenshots)
- [Project Structure](#project-structure)
- [Contributing](#contributing)

## ✨ Features

### 🔐 Authentication System
- **Role-based login** (Admin, Teacher, Student)
- **Secure email/password verification**
- **Session management** for current user tracking

### 👨‍💼 Admin Dashboard
- **User Management**
  - Register new teachers and students
  - View, update, and remove user accounts
  - Access teacher and student dashboards
- **System Administration**
  - Manage user information (password, designation, contact details)
  - Full CRUD operations on user accounts

### 👩‍🏫 Teacher Dashboard
- **Quiz Management**
  - Create new quizzes with multiple-choice questions
  - Set quiz parameters (subject, section, session, time limits)
  - Edit existing quiz questions and answers
  - Assign marks to individual questions
- **Student Management**
  - View student information
  - Monitor quiz performance
  - Access student dashboards

### 👨‍🎓 Student Dashboard
- **Quiz Taking**
  - View assigned quizzes
  - Take quizzes with timed sessions
  - Submit answers and get instant results
- **Performance Tracking**
  - View quiz results and scores
  - Check grades and percentages
  - Track academic progress
- **Profile Management**
  - Update personal information
  - View dashboard with academic details



## 🚀 Installation

1. **Clone or Download** the project files to your local machine
2. **Open the project** in Visual Studio:
   - Open `Project1.vcxproj` file
   - Or open `Source.cpp` in your preferred C++ IDE
3. **Build the project**:
   - In Visual Studio: Build → Build Solution (Ctrl+Shift+B)
   - Or compile using command line: `g++ Source.cpp -o QuizSystem.exe`
4. **Run the executable**:
   - Double-click `QuizSystem.exe` or run from IDE

## 📖 Usage

### Starting the Application
1. Run the compiled executable
2. The system will display the logo and load existing data
3. Enter your login credentials when prompted
**Note**
Only admin credentials are hardcoded in code  
The credentials of teacher and students are generated automatically in file after you register their details
### Administrator Credentials:
- **Email**: `aduet@edu.pk`
- **Password**: `Admin123`

### Navigation
- Follow the numbered menu options
- Enter your choice and press Enter
- Use the back/exit options to navigate between menus

### Taking a Quiz (Student)
1. Log in with student credentials
2. Select "View assigned quizzes" to see available quizzes
3. Choose "Take a quiz" and select the quiz number
4. Answer all questions within the time limit
5. Submit to view your results instantly

### Creating a Quiz (Teacher)
1. Log in with teacher credentials
2. Select "Create quiz" from the menu
3. Enter quiz details (subject, section, time limit, etc.)
4. Add questions with multiple-choice options
5. Set correct answers and mark allocations
6. Save the quiz for student access

## 📁 File Structure

```
1st-Sem-Project/
├── Source.cpp              # Main source code file
├── Project1.vcxproj         # Visual Studio project file
├── Project1.vcxproj.filters # Project filters
├── Project1.vcxproj.user    # User-specific settings
├── Teacher_Info.txt         # Teacher data storage
├── Student_Info.txt         # Student data storage
├── Quizzes.txt             # Quiz data storage
├── QuizSystem.exe          # Compiled executable
├── x64/Debug/              # Build output directory
├── *.png                   # UI mockup screenshots
└── README.md               # This file
```

## 🔑 Default Login Credentials

### Administrator
- **Email**: `aduet@edu.pk`
- **Password**: `Admin123`

### Sample Teacher
- **Email**: `te1122CSdepartment@uet.edu.pk`
- **Password**: `90675`

### Sample Student
- **Email**: `st2025-SE-53CSdepartment@uet.edu.pk`
- **Password**: `68145`

## 📸 Screenshots

The project includes UI mockups for:
- **Login Page** (`Login page.png`)
- **Admin Dashboard** (`ADmin dashbaord.png`)
- **Teacher Dashboard** (`Teacher dashboard.png`)
- **Student Dashboard** (`student dashboard.png`)

## 🏗️ Project Structure

### Core Components

#### Data Structures
- **Student**: Name, father's name, DOB, address, department, email, CNIC, contact, fees
- **Teacher**: Name, father's name, DOB, address, department, email, CNIC, contact, BPS
- **Quiz**: Subject, section, session, time limit, questions, marks
- **Question**: Statement, options (4 choices), correct answer, marks
- **QuizResult**: Student email, quiz details, score, percentage, grade

#### Key Functions
- **Authentication**: `verifyemail()` - Role-based login verification
- **Admin Functions**: User management, registration, updates
- **Teacher Functions**: Quiz creation, editing, student management
- **Student Functions**: Quiz taking, result viewing, grade tracking
- **File Handling**: Data persistence through text files

#### Features Implemented
- ✅ Role-based authentication system
- ✅ Dynamic user registration and management
- ✅ Interactive quiz creation with multiple-choice questions
- ✅ Real-time quiz taking with timer functionality
- ✅ Automatic grading and result calculation
- ✅ Grade tracking and performance analytics
- ✅ File-based data persistence
- ✅ User-friendly console interface
- ✅ Data validation and error handling

## 🎯 Key Programming Concepts Demonstrated

- **Object-Oriented Programming**: Structures and data encapsulation
- **File I/O Operations**: Reading from and writing to text files
- **Dynamic Memory Management**: Vectors for dynamic data storage
- **String Manipulation**: Text processing and parsing
- **Control Structures**: Loops, conditionals, and switch statements
- **Function Modularity**: Well-organized function-based architecture
- **Data Validation**: Input validation and error handling
- **Algorithm Implementation**: Sorting, searching, and calculation algorithms

## 🤝 Contributing

This is an academic project for Programming Fundamentals course. While it's primarily for educational purposes, suggestions and improvements are welcome.

### Development Team: Group-1
- **Course**: Programming Fundamentals (1st Semester)
- **Institution**: University of Engineering and Technology (UET)
- **Academic Session**: 2024-2025

## 📝 Notes

- The system uses text files for data persistence
- All data is stored in a structured format with delimiters
- The application is designed for Windows console environment
- Grade calculation is based on percentage with standard grading scale
- Quiz timing is implemented for realistic exam simulation

## 🔮 Future Enhancements

Potential improvements for future versions:
- Database integration (MySQL/SQLite)
- Graphical User Interface (GUI)
- Network connectivity for multi-user access
- Advanced reporting and analytics
- Question bank management
- Randomized question selection
- Export functionality for results

---

**Note**: This project demonstrates fundamental programming concepts and serves as a comprehensive example of a console-based management system in C++.

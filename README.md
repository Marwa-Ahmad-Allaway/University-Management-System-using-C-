# 🎓 University Management System in C++

This is a C++ console-based **University Management System** designed using **Object-Oriented Programming (OOP)** principles. It simulates real-life operations for managing students, professors, teaching assistants (TAs), and courses.

## 📌 Features

### 👨‍🎓 Student Management
- Add new students.
- Enroll students in courses.
- Automatically checks:
  - Prerequisite completion.
  - GPA-based credit hour limits.
- Display student details and enrolled courses.
- Unenroll students from courses.

### 👨‍🏫 Professor Management
- Add new professors.
- Assign professors to teach courses.
- Track supervised theses count per professor.

### 👨‍🔬 Teaching Assistant Management
- Add TAs with:
  - Department
  - Supervisor (Professor)
  - Research Area
  - Number of Publications
  - List of Projects
- Assign TAs to courses.

### 📚 Course Management
- Create new courses.
- Set prerequisites and required credits.
- Assign professors and TAs.
- View course details with instructors and enrolled students.

### 💾 Data Persistence
- All data is stored in CSV files:
  - `students.csv`
  - `professors.csv`
  - `courses.csv`
  - `tas.csv`
- Data is loaded at startup and saved automatically on exit.

## 🔐 User Roles

- **Student**
  - View personal info
  - Enroll in courses
- **Professor**
  - View personal info and supervised theses
- **Teaching Assistant**
  - View profile and projects
- **Administrator**
  - Full access to add/view/assign entities (requires access code)

## ⚙️ Technologies Used

- **Language:** C++
- **Paradigm:** Object-Oriented Programming
- **Libraries:** STL (`vector`, `string`, `fstream`, etc.)
- **File Handling:** CSV input/output

## 🏁 Getting Started

1. Compile the source code with a C++ compiler (e.g., `g++`).
2. Run the program from the terminal.
3. Interact with the system based on your role.

## ✍️ Author

Developed as a university project for learning and demonstrating OOP concepts in C++.


## 👩‍💻 Developed By

- Marwa Ahmad
- Alaa Mohmoud


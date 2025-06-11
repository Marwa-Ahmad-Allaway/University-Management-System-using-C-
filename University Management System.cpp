#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore();
            return value;
        }
    }
}
// Function to get string input
string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}
// Forward declarations
class Course;
class University;

// Person class (base class)
class Person {
protected:
    int id;
    string name;

public:
    Person(int id, const string& name) : id(id), name(name) {}
    virtual ~Person() = default;

    int getId() const { return id; }
    string getName() const { return name; }
};

// Helper function for finding by ID
template <class T>
T* findById(vector<T>& people, int id) {
    for (auto& person : people) {
        if (person.getId() == id) {
            return &person;
        }
    }
    return nullptr;
}

// TeachingAssistant class
class TeachingAssistant : public Person {
private:
    string department;
    int supervisorId;
    string researchArea;
    int numberOfPublications;
    vector<string> supervisedProjects;
    friend class University;

public:
    TeachingAssistant(int id, const string& name, const string& department,
                     int supervisorId = -1, const string& researchArea = "", 
                     int numberOfPublications = 0)
        : Person(id, name), department(department), supervisorId(supervisorId),
          researchArea(researchArea), numberOfPublications(numberOfPublications) {}
	string getDepartment() const {return department;}

    int getSupervisorId() const {return supervisorId;}

    string getResearchArea() const {    return researchArea;}

    int getNumberOfPublications() const {return numberOfPublications;}
    vector<string> getSupervisedProjects() const {return supervisedProjects;}
	
    void addProject(const string& project) {
        supervisedProjects.push_back(project);
    }

    void display() const {
        cout << "TA ID: " << id << ", Name: " << name << ", Dept: " << department
             << ", Supervisor Prof ID: " << supervisorId << endl;
        cout << "Research Area: " << researchArea << endl;
        cout << "Publications: " << numberOfPublications << endl;
        if (!supervisedProjects.empty()) {
            cout << "Supervised Projects:\n";
            for (const auto& p : supervisedProjects) {
                cout << "  - " << p << endl;
            }
        }
        cout << endl;
    }
};

// Professor class
class Professor : public Person {
private:
    string department;
    int supervisedThesisCount;
    friend class University;

public:
    Professor(int id, const string& name, const string& department) 
        : Person(id, name), department(department), supervisedThesisCount(0) {}

    int getSupervisedThesisCount() const { return supervisedThesisCount; }
    string getDepartment() const { return department; }
	int setSupervisedThesisCount(int supcoun){ supervisedThesisCount = supcoun; }
    void incrementThesisCount() {
        supervisedThesisCount++;
    }

    void displayStudentsFor(int courseId, const University& uni);

    void displayTAsOfProfessor(const vector<TeachingAssistant>& allTAs) const {
        cout << "Teaching Assistants supervised by Professor " << name << ":\n";
        bool found = false;
        for (const auto& ta : allTAs) {
            if (ta.getSupervisorId() == id) {
                ta.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No TAs found for this professor.\n";
        }
    }

    void display() const {
        cout << "Professor ID: " << id << ", Name: " << name
             << ", Dept: " << department
             << ", Supervised Theses: " << supervisedThesisCount << endl;
    }
};

// Course class
class Course {
private:
    int id;
    string name;
    int credits;
    vector<int> prerequisiteCourseIds;
    int requiredCredits;
    vector<int> teachingAssistantIds;
    friend class University;

public:
	int professorId;
    Course(int id, const string& name, int credits)
        : id(id), name(name), credits(credits), professorId(-1), requiredCredits(0) {}

int getId() const {
        return id;
    }
	string getName() const {
        return name;
    }
    int getCredits() const {
        return credits;
    }
    int getProfessorId() const {
        return professorId;
    }
    vector<int> getPrerequisiteCourseIds() const {
        return prerequisiteCourseIds;
    }
    int getRequiredCredits() const {
        return requiredCredits;
    }
    vector<int> getTeachingAssistantIds() const {
        return teachingAssistantIds;
    }
    void setId(int newId) {
        id = newId;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setCredits(int newCredits) {
        credits = newCredits;
    }

    void setProfessorId(int newProfessorId) {
        professorId = newProfessorId;
    }

    void setPrerequisiteCourseIds(int newPrerequisites) {
        prerequisiteCourseIds.push_back(newPrerequisites);
    }

    void setRequiredCredits(int newRequiredCredits) {
        requiredCredits = newRequiredCredits;
    }

    void setTeachingAssistantIds(int newAssistantIds) {
        teachingAssistantIds.push_back(newAssistantIds);
    }
void display(const Professor* professor = nullptr,
                const vector<TeachingAssistant>* allTAs = nullptr) const {
        cout << "ID: " << id << ", Name: " << name << ", Credits: " << credits;
        if (professor) {
            cout << ", Taught by: " << professor->getName();
        }
        cout << endl;

        if (allTAs && !teachingAssistantIds.empty()) {
            cout << "  Teaching Assistants:\n";
            for (int taId : teachingAssistantIds) {
                for (const auto& ta : *allTAs) {
                    if (ta.getId() == taId) {
                        cout << "    - " << ta.getName() << endl;
                    }
                }
            }
        }
    }
};

// Student class
class Student : public Person {
private:
    string major;
    double GPA;
    vector<int> enrolledCourseIds;
    friend class University;

public:
    Student(int id, const string& name, const string& major, double gpa = 0.0)
        : Person(id, name), major(major), GPA(gpa) {}

    string getMajor() const { return major; }
    double getGPA() const { return GPA; }
	const vector<int> & getEnrolledCourseIds() const {return enrolledCourseIds;}
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Major: " << major << endl;
        cout << "Enrolled in courses: ";
        if (enrolledCourseIds.empty()) {
            cout << "None";
        } else {
            for (int cid : enrolledCourseIds) {
                cout << cid << " | ";
            }
        }
        cout << endl;
    }

    int getMaxAllowedCredits() const {
        if (GPA >= 3.5) return 21;
        else if (GPA >= 3.0) return 18;
        else if (GPA >= 2.0) return 14;
        else return 12;
    }

    int totalCompletedCredits(const vector<Course>& allCourses) const {
        int total = 0;
        for (int cid : enrolledCourseIds) {
            for (const Course& c : allCourses) {
                if (c.getId() == cid) {
                    total += c.getCredits();
                    break;
                }
            }
        }
        return total;
    }

    bool enrollStudentInCourse(int courseId, const vector<Course>& allCourses) {
        const Course* targetCourse = nullptr;
        for (const auto& c : allCourses) {
            if (c.getId() == courseId) {
                targetCourse = &c;
                break;
            }
        }

        if (!targetCourse) {
            cout << "Course not found.\n";
            return false;
        }

        if (find(enrolledCourseIds.begin(), enrolledCourseIds.end(), courseId) != enrolledCourseIds.end()) {
            cout << "Already enrolled in course: " << targetCourse->getName() << endl;
            return false;
        }

        for (int prereqId : targetCourse->getPrerequisiteCourseIds()) {
            if (find(enrolledCourseIds.begin(), enrolledCourseIds.end(), prereqId) == enrolledCourseIds.end()) {
                cout << "Missing prerequisite course ID: " << prereqId << " for " << targetCourse->getName() << endl;
                return false;
            }
        }

        int totalCredits = totalCompletedCredits(allCourses);
        int maxAllowedCredits = getMaxAllowedCredits();

        if (totalCredits + targetCourse->getCredits() > maxAllowedCredits) {
            cout << "Cannot enroll in " << targetCourse->getName()
                 << ". Total credits would exceed allowed limit (" << maxAllowedCredits << ").\n";
            return false;
        }

        enrolledCourseIds.push_back(courseId);
        cout << "Enrolled in course: " << targetCourse->getName() << endl;
        return true;
    }
};

// University class
class University {
private:
	vector<Student> students;
    vector<Course> courses;
    vector<Professor> professors;
    vector<TeachingAssistant> teachingAssistants;
    void saveStudentsToCSV(const string& filename = "students.csv");
    void loadStudentsFromCSV(const string& filename = "students.csv");
    void saveProfessorsToCSV(const string& filename = "professors.csv");
    void loadProfessorsFromCSV(const string& filename = "professors.csv");
    void saveCoursesToCSV(const string& filename = "courses.csv");
    void loadCoursesFromCSV(const string& filename = "courses.csv");
    void saveTAsToCSV(const string& filename = "tas.csv");
    void loadTAsFromCSV(const string& filename = "tas.csv");

public:

    University() {
        loadStudentsFromCSV();
        loadProfessorsFromCSV();
        loadCoursesFromCSV();
        loadTAsFromCSV();
    }

	const vector<Student>& getStudents() const {
	    return students;
	}
	
	const vector<Course>& getCourses() const {
	    return courses;
	}
	
	const vector<Professor>& getProfessors() const {
	    return professors;
	}
	
	const vector<TeachingAssistant>& getTeachingAssistants() const {
	    return teachingAssistants;
	}


    ~University() {
        saveStudentsToCSV();
        saveProfessorsToCSV();
        saveCoursesToCSV();
        saveTAsToCSV();
    }

    // Student operations
    Student* findStudent(int id) { return findById(students, id); }
    void addStudent(const Student& s) {
        students.push_back(s);
        saveStudentsToCSV();
    }
    void displayStudentCourses(int studentId);
    void unenrollStudentFromCourse(int studentId, int courseId);
    void displayCourseStudents(int courseId);

    // Professor operations
    Professor* findProfessor(int id) { return findById(professors, id); }
    void addProfessor(const Professor& p) {
        professors.push_back(p);
        saveProfessorsToCSV();
    }
    void assignThesisToProfessor(int profId);

    // Course operations
    Course* findCourse(int id) { return findById(courses, id); }
    void addCourse(const Course& c) {
        courses.push_back(c);
        saveCoursesToCSV();
    }
    void assignProfessorToCourse(int courseId, int professorId);
    void assignTAtoCourse(int courseId, int taId);

    // Teaching Assistant operations
    TeachingAssistant* findTeachingAssistant(int id) { return findById(teachingAssistants, id); }
    void addTeachingAssistant(const TeachingAssistant& ta) {
        teachingAssistants.push_back(ta);
        saveTAsToCSV();
    }
};

// University member functions implementation
void University::saveStudentsToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    file << "ID,Name,Major,GPA,EnrolledCourses\n";
    for (const auto& student : students) {
        file << student.getId() << "," << student.getName() << "," 
             << student.getMajor() << "," << student.getGPA() << ",";

        const auto& enrolled = student.getEnrolledCourseIds();
        for (size_t i = 0; i < enrolled.size(); ++i) {
            file << enrolled[i];
            if (i < enrolled.size() - 1) file << "|";
        }
        file << "\n";
    }
    file.close();
}

void University::loadStudentsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, major, gpaStr, enrolledStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, major, ',');
        getline(ss, gpaStr, ',');
        getline(ss, enrolledStr);

        Student s(stoi(idStr), name, major, stod(gpaStr));

        stringstream coursesStream(enrolledStr);
        string courseId;
        while (getline(coursesStream, courseId, '|')) {
            s.enrolledCourseIds.push_back(stoi(courseId));
        }

        students.push_back(s);
    }
    file.close();
}

void University::saveProfessorsToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }
file << "ID,Name,Department,SupervisedTheses\n";
    for (const auto& prof : professors) {
        file << prof.getId() << "," << prof.getName() << "," 
             << prof.getDepartment() << "," << prof.getSupervisedThesisCount() << "\n";
    }
    file.close();
}

void University::loadProfessorsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, dept, thesisStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, dept, ',');
        getline(ss, thesisStr);

        Professor prof(stoi(idStr), name, dept);
        prof.setSupervisedThesisCount(stoi(thesisStr));
        professors.push_back(prof);
    }
    file.close();
}

void University::saveCoursesToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    file << "ID,Name,Credits,ProfessorId,RequiredCredits,Prerequisites,TeachingAssistants\n";
    for (const auto& course : courses) {
        file << course.getId() << "," << course.getName() << "," << course.getCredits() << ","
             << course.getProfessorId() << "," << course.getRequiredCredits() << ",";

        // Prerequisite IDs
        for (size_t i = 0; i < course.prerequisiteCourseIds.size(); ++i) {
            file << course.getPrerequisiteCourseIds()[i];
            if (i < course.getPrerequisiteCourseIds().size() - 1) file << "|";
        }

        file << ",";

        // TA IDs
        for (size_t i = 0; i < course.teachingAssistantIds.size(); ++i) {
            file << course.getTeachingAssistantIds()[i];
            if (i < course.getTeachingAssistantIds().size() - 1) file << "|";
        }

        file << "\n";
    }
    file.close();
}

void University::loadCoursesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, creditsStr, profIdStr, reqCreditsStr, prereqStr, tasStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, creditsStr, ',');
        getline(ss, profIdStr, ',');
        getline(ss, reqCreditsStr, ',');
        getline(ss, prereqStr, ',');
        getline(ss, tasStr);

        Course c(stoi(idStr), name, stoi(creditsStr));
        c.setProfessorId(stoi(profIdStr));
        c.setRequiredCredits(stoi(reqCreditsStr));

        stringstream prereqStream(prereqStr);
        string prereq;
        while (getline(prereqStream, prereq, '|')) {
            if (!prereq.empty())
                c.setPrerequisiteCourseIds(stoi(prereq));
        }

        stringstream taStream(tasStr);
        string taId;
        while (getline(taStream, taId, '|')) {
            if (!taId.empty())
                c.setTeachingAssistantIds(stoi(taId));
        }

        courses.push_back(c);
    }
    file.close();
}

void University::saveTAsToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return;
    }

    file << "ID,Name,Department,SupervisorId,ResearchArea,Publications,Projects\n";
    for (const auto& ta : teachingAssistants) {
        file << ta.getId() << "," << ta.getName() << "," << ta.department << ","
             << ta.supervisorId << "," << ta.researchArea << "," << ta.numberOfPublications << ",";

        for (size_t i = 0; i < ta.getSupervisedProjects().size(); ++i) {
            file << ta.getSupervisedProjects()[i];
            if (i < ta.getSupervisedProjects().size() - 1) file << "|";
        }

        file << "\n";
    }
    file.close();
}
void University::loadTAsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, dept, supervisorIdStr, research, pubsStr, projectsStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, dept, ',');
        getline(ss, supervisorIdStr, ',');
        getline(ss, research, ',');
        getline(ss, pubsStr, ',');
        getline(ss, projectsStr);

        TeachingAssistant ta(stoi(idStr), name, dept, stoi(supervisorIdStr), research, stoi(pubsStr));

        stringstream projStream(projectsStr);
        string proj;
        while (getline(projStream, proj, '|')) {
            if (!proj.empty())
                ta.supervisedProjects.push_back(proj);
        }

        teachingAssistants.push_back(ta);
    }
    file.close();
}

void University::displayStudentCourses(int studentId) {
    Student* student = findStudent(studentId);
    if (!student) {
        cout << "Student not found." << endl;
        return;
    }

    cout << "Courses enrolled by " << student->getName() << ":" << endl;
    for (int cid : student->getEnrolledCourseIds()) {
        Course* course = findCourse(cid);
        if (course) {
            Professor* prof = findProfessor(course->getProfessorId());
            course->display(prof);
        }
    }
}

void University::unenrollStudentFromCourse(int studentId, int courseId) {
    Student* student = findStudent(studentId);
    if (!student) {
        cout << "Student not found." << endl;
        return;
    }

    auto& enrolled = student->enrolledCourseIds;
    auto it = find(enrolled.begin(), enrolled.end(), courseId);
    if (it != enrolled.end()) {
        enrolled.erase(it);
        saveStudentsToCSV();
        cout << "Student " << student->getName() << " has been unenrolled from course ID " << courseId << endl;
    } else {
        cout << "Student " << student->getName() << " is not enrolled in course ID " << courseId << endl;
    }
}

void University::displayCourseStudents(int courseId) {
    Course* course = findCourse(courseId);
    if (!course) {
        cout << "Course not found." << endl;
        return;
    }

    cout << "Students enrolled in course: " << course->name << endl;
    bool hasStudents = false;
    for (const Student& student : students) {
        if (find(student.enrolledCourseIds.begin(), student.enrolledCourseIds.end(), courseId) != student.enrolledCourseIds.end()) {
            cout << "- " << student.getName() << " (ID: " << student.getId() << ")" << endl;
            hasStudents = true;
        }
    }

    if (!hasStudents) {
        cout << "No students are currently enrolled in this course." << endl;
    }
}

void University::assignThesisToProfessor(int profId) {
    for (auto& prof : professors) {
        if (prof.getId() == profId) {
            prof.incrementThesisCount();
            cout << "Added one thesis supervision to Professor " << prof.getName() << endl;
            return;
        }
    }
    cout << "Professor with ID " << profId << " not found." << endl;
}

void University::assignProfessorToCourse(int courseId, int professorId) {
    Course* course = findCourse(courseId);
    Professor* professor = findProfessor(professorId);
    if (course && professor) {
        course->setProfessorId(professorId);
        cout << "Professor " << professor->getName() << " assigned to course " << course->name << endl;
    } else {
        cout << "Course or professor not found." << endl;
    }
}

void University::assignTAtoCourse(int courseId, int taId) {
    Course* course = findCourse(courseId);
    if (!course) {
        cout << "Course not found.\n";
        return;
    }
    if (find(course->teachingAssistantIds.begin(), course->teachingAssistantIds.end(), taId) != course->teachingAssistantIds.end()) {
        cout << "TA already assigned to this course.\n";
        return;
    }

    course->teachingAssistantIds.push_back(taId);
    cout << "TA with ID " << taId << " assigned to course ID " << courseId << endl;
}


// Main function with sample usage
int main() {
    University university;
    int choice;

    do {
	    cout << "\nUniversity Management System\n";
	    cout << "1. Student \n";
	    cout << "2. Professor\n";
	    cout << "3. Teaching Assistant\n";
	    cout << "4. Administrator\n";
	    cout << "0. Exit\n";
	    cout << "Enter your choice: ";
        choice = getIntInput("");
	int id ;
    switch (choice) {
        case 1: { // Student
            id = getIntInput("Enter your Student ID: ");
            Student* student = university.findStudent(id);
            if (student) {
                cout << "\nWelcome " << student->getName() << "!\n";
			    cout << "1. Student information \n";
			    cout << "2. Enroll In Course\n";
			    cout << "3. Get Enrolled Course Ids\n";
			    cout << "0. Exit\n";
			    cout << "Enter your choice: ";
		        int c = getIntInput("");
                switch (c) {
        			case 1: {
						student->display();
				        break;
        					}
        			case 2:{
        				cout << "Enter course id ";
		       			int cid = getIntInput("");
        				student->enrollStudentInCourse(cid,university.getCourses());
				        break;
						}
					case 3:{
						student->getEnrolledCourseIds();}
					case 0:{
						cout << "Exiting program.\n";
	                	break;}
					default: {
				                cout << "Invalid choice. Please try again.\n";
				                break;
				              }		
  
            } }
			else {
                cout << "Student not found.\n";
            }
            break;
            }
            case 2: { // Professor
	            id = getIntInput("Enter your Professor ID: ");
	            const Professor* prof = university.findProfessor(id);
	            if (prof) {
	                cout << "\nWelcome Dr. " << prof->getName() << "!\n";
        			prof->display();
	            } else {
	                cout << "Professor not found.\n";
	            }
	            break;
	        }
            case 3: { // Teaching Assistant
	            id = getIntInput("Enter your TA ID: ");
	            const TeachingAssistant* ta = university.findTeachingAssistant(id);
	            if (ta) {
	                cout << "\nWelcome " << ta->getName() << "!\n";
        			ta->display();			
	                
	            } else {
	                cout << "Teaching Assistant not found.\n";
	            }
	            break;
	        }
            case 4: { // Administrator
            string code = getStringInput("Enter the university admin code: ");
		            if (code == "admin123") {
		                cout << "Administrator access granted.\n";
		                // full control menu
		                cout << "1. Add Student\n";
					    cout << "2. Add Professor\n";
					    cout << "3. Add Teaching Assistant\n";
					    cout << "4. Add Course\n";
					    cout << "5. Assign Professor to Course\n";
					    cout << "6. Assign TA to Course\n";
					    cout << "7. Display Student Information\n";
					    cout << "8. Display Course Information\n";
					    cout << "9. Display Professor Information\n";
					    cout << "10. Display TA Information\n";
					    cout << "Enter your choice: ";
						int c  = getIntInput("");
						switch (c) {
        					case 1: {//Add Student
        						int id = getIntInput("Enter student ID: ");
				                string name = getStringInput("Enter student name: ");
				                string major = getStringInput("Enter student major: ");
				                university.addStudent(Student(id, name, major));
				                break;
        					}
        					case 2:{//Add Professor
        						int id = getIntInput("Enter professor ID: ");
				                string name = getStringInput("Enter professor name: ");
				                string dept = getStringInput("Enter department: ");
				                university.addProfessor(Professor(id, name, dept));
				               	break;
							}
							case 3:{// Add Teaching Assistant
				                int id = getIntInput("Enter TA ID: ");
				                string name = getStringInput("Enter TA name: ");
				                string dept = getStringInput("Enter department: ");
				                int supervisorId = getIntInput("Enter supervisor professor ID (-1 if none): ");
				                string research = getStringInput("Enter research area: ");
				                int pubs = getIntInput("Enter number of publications: ");
				
				                TeachingAssistant ta(id, name, dept, supervisorId, research, pubs);
				
				                // Add projects if any
				                while (true) {
				                    string project = getStringInput("Add project (or 'done' to finish): ");
				                    if (project == "done") break;
				                    ta.addProject(project);
				                }
				
				                university.addTeachingAssistant(ta);
								break;
							}
							case 4:{// Add Course
				                int id = getIntInput("Enter course ID: ");
				                string name = getStringInput("Enter course name: ");
				                int credits = getIntInput("Enter credit hours: ");
				                int reqCredits = getIntInput("Enter required credits to take this course: ");
				
				                Course course(id, name, credits);
				                course.setRequiredCredits(reqCredits) ;
				
				                // Add prerequisites if any
				                while (true) {
				                    int prereq = getIntInput("Add prerequisite course ID (-1 to finish): ");
				                    if (prereq == -1) break;
				                       course.setPrerequisiteCourseIds(prereq);
				                }
				
				                university.addCourse(course);
								break;
							}
							case 5:{// Assign Professor to Course
				                int courseId = getIntInput("Enter course ID: ");
				                int profId = getIntInput("Enter professor ID: ");
				                university.assignProfessorToCourse(courseId, profId);
				                break;
							}
							case 6:{// Assign TA to Course
				                int courseId = getIntInput("Enter course ID: ");
				                int taId = getIntInput("Enter TA ID: ");
				                university.assignTAtoCourse(courseId, taId);
				                break;
							}
							case 7:{// Display Student Information
				                int studentId = getIntInput("Enter student ID: ");
				                const Student* student = university.findStudent(studentId);
				                if (student) {
				                    student->display();
				                    university.displayStudentCourses(studentId);
				                } else {
				                    cout << "Student not found.\n";
				                }
				                break;
				            }
				            case 8: { // Display Course Information
				                int courseId = getIntInput("Enter course ID: ");
				                const Course* course = university.findCourse(courseId);
				                if (course) {
				                    const Professor* prof = university.findProfessor(course->professorId);
				                    course->display(prof, &university.getTeachingAssistants());
				                    university.displayCourseStudents(courseId);
				                } else {
				                    cout << "Course not found.\n";
				                }
				                break;
				            }
				            case 9: { // Display Professor Information
				                int profId = getIntInput("Enter professor ID: ");
				                const Professor* prof = university.findProfessor(profId);
				                if (prof) {
				                    prof->display();
				                } else {
				                    cout << "Professor not found.\n";
				                }
				                break;
				            }
				            case 10: { // Display TA Information
				                int taId = getIntInput("Enter TA ID: ");
				                const TeachingAssistant* ta = university.findTeachingAssistant(taId);
				                if (ta) {
				                    ta->display();
				                } else {
				                    cout << "TA not found.\n";
				                }
				                break;
							}
							default: {
				                cout << "Invalid choice. Please try again.\n";
				                break;
				              }
							}
						
		            } else {
		                cout << "Invalid admin code.\n";
		            }
		            break;
		        }
            
           case 0: { // Exit
                cout << "Exiting program.\n";
                break;
              }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
              }
        }
		    
    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

class Student
{
private:
    string name;
    int id;
    int age;
    int Level;
    string department;
public:
    Student(string NAME, int ID, int AGE, int LE, string DT)
    {
        name = NAME;
        id = ID;
        age = AGE;
        Level = LE;
        department = DT;
    }
    string getname() { return name; }
    int getID() { return id; }
    int getAge() { return age; }
    int getLevel1() { return Level; }
    string getDept() { return department; }

    void setname(string NAME) { name = NAME; }
    void setAge(int AGE) { age = AGE; }
    void setLevel1(int LE) { Level = LE; }
    void setDept(string DT) { department = DT; }
};

class Course
{
private:
    string name_course;
    int credit_hours;
    int level_course;
    string instructor_name;
    string departname_course;
public:
    Course(string n, int c_hour, int LE_course, string ins_name, string dept_name)
    {
        name_course = n;
        credit_hours = c_hour;
        level_course = LE_course;
        instructor_name = ins_name;
        departname_course = dept_name;
    }
    string getname() { return name_course; }
    int getcredit_hours() { return credit_hours; }
    int getlevel_Course() { return level_course; }
    string getInsName() { return instructor_name; }
    string getDeptName() { return departname_course; }

    void SetName(string n) { name_course = n; }
    void SetCredit_Hours(int c_hour) { credit_hours = c_hour; }
    void Setlevel_Course(int LE_course) { level_course = LE_course; }
    void SetInsName(string ins_name) { instructor_name = ins_name; }
    void SetDeptName(string dept_name) { departname_course = dept_name; }
};

class DataManger
{
public:
    void SaveStudentsToFile(vector<Student>& Students)
    {
        ofstream File("students.txt");
        for (auto& save : Students)
        {
            File << save.getID() << ","
                
                << save.getname() << ","
                << save.getAge() << ","
                <<save.getLevel1() << ","
                
                << save.getDept() << "\n";
        }
        File.close();
    }
    void LoadStudentsToFile(vector<Student>& Students)
    {
        ifstream File("students.txt");
        Students.clear();
        string line;
        while (getline(File, line))
        {
            stringstream ss(line);
            string name, department, temp;
            int id, age, Level;
            getline(ss, temp, ',');
            id = stoi(temp);
            getline(ss, name, ',');
            getline(ss, temp, ',');
            age = stoi(temp);
            getline(ss, temp, ',');
            Level = stoi(temp);
            getline(ss, department);
            Student std(name, id, age, Level, department);
            Students.push_back(std);
        }
        File.close();
    }

    void SaveCoursesToFile(vector<Course>& Courses)
    {
        ofstream file("Courses.txt");
        for (auto& Csave : Courses)
        {
            file << Csave.getname() << "," << Csave.getDeptName() << "," << Csave.getcredit_hours() << "," << Csave.getlevel_Course() << "," << Csave.getInsName() << "\n";
        }
        file.close();
    }

    void LoadCoursesToFile(vector<Course>& Courses)
    {
        ifstream file("Courses.txt");
        Courses.clear();
        string Line;
        while (getline(file, Line))
        {
            stringstream cc(Line);
            string name_course, instructor_name, departname_course, temp;
            int credit_hours, level_course;
            getline(cc, name_course, ',');
            getline(cc, departname_course, ',');
            getline(cc, temp, ',');
            credit_hours = stoi(temp);
            getline(cc, temp, ',');
            level_course = stoi(temp);
            getline(cc, instructor_name, ',');
            Course C(name_course, credit_hours, level_course, instructor_name, departname_course);
            Courses.push_back(C);
        }
        file.close();
    }
};

bool IDFaild(vector<Student>& Students, int id)
{
    for (auto& check : Students)
    {
        if (check.getID() == id)
            return true;
    }
    return false;
}

class student_manger
{
public:
    vector<Student>Students;

    void AddStudent(vector<Student>& Students)
    {
        cin.ignore();
        string name, department;
        int id, age, Level;
        cout << "Enter your name: ";
        getline(cin, name);

        bool idExists;
        do {
            idExists = false;
            cout << "Enter ID: ";
            cin >> id;
            if (IDFaild(Students, id)) {
                cout << "This ID already exists! Try again.\n";
                idExists = true;
            }
        } while (idExists);

        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your level: ";
        cin >> Level;
        cin.ignore();
        cout << "Enter your department: ";
        getline(cin, department);

        Student std(name, id, age, Level, department);
        Students.push_back(std);

        cout << "Student added successfully!\n";
        system("pause");
    }

    void UpdateStudent(vector<Student>& Students)
    {

        DataManger update;
        int check_id;
        cout << "Enter student ID: ";
        cin >> check_id;

        bool found = false;
        for (auto& check : Students)
        {
            if (check_id == check.getID())
            {
                found = true;
                cout << "1. Edit Name\n2. Edit Age\n3. Edit Level\n4. Edit Department\nEnter choice: ";
                int choice;
                cin >> choice;
                cin.ignore();
                if (choice == 1)
                { 
                    string newName;
                  cout << "Enter new name: ";
                  getline(cin, newName); check.setname(newName);
                }
                else if (choice == 2)
                {
                    int newAge;
                    cout << "Enter new age: ";
                    cin >> newAge; check.setAge(newAge);
                }
                else if (choice == 3) 
                {
                    int newLevel;
                    cout << "Enter new level: ";
                    cin >> newLevel;
                    check.setLevel1(newLevel); 
                }
                else if (choice == 4) 
                {
                    string newDept; 
                    cout << "Enter new department: ";
                    getline(cin >> ws, newDept); 
                    check.setDept(newDept);
                }
                  update.SaveStudentsToFile(Students);
                  system("pause");
                  cout << "Student Updated Successfully!\n";
                break;
            }
        }
        if (!found) cout << "ID Not Found!\n";
    }

    void DeleteStudent(vector<Student>& Students, DataManger& dataManager)
    {
        int check_id;
        cout << "Enter student ID to delete: ";
        cin >> check_id;

        bool found = false;
        for (auto it = Students.begin(); it != Students.end(); ++it)
        {
            if (it->getID() == check_id)
            {
                Students.erase(it);
                dataManager.SaveStudentsToFile(Students);
                cout << "Student Deleted Successfully!\n";
                found = true;  
                break;
            }
        }
        if (!found) cout << "ID Not Found!\n";
        system("pause");
    }

    void DisplayAllStudent(vector<Student>& Students)
    {
        if (Students.empty()) {
            cout << "No students to display!\n";
            return;
        }

        cout << "-------------------------------------------------------------\n";
        cout << "Name                     | ID      | Age | Level | Dept\n";
        cout << "-------------------------------------------------------------\n";

        for (auto& s : Students)
        {
            cout << setw(25) << left << s.getname()
                << "| " << setw(8) << left << s.getID()
                << "| " << setw(3) << left << s.getAge()
                << "| " << setw(5) << left << s.getLevel1()
                << "| " << s.getDept() << "\n";
        }
        cout << "-------------------------------------------------------------\n";
    }
    void SearchStudent(vector<Student>& Students, vector<Course>& Courses)
    {
        int check_id;
        cout << "Enter student ID to search: ";
        cin >> check_id;

        bool found = false;
        for (auto& check : Students)
        {
            if (check.getID() == check_id)
            {
                found = true;
                cout << "Name: " << check.getname() << " | ID: " << check.getID() << " | Age: " << check.getAge() << " | Level: " << check.getLevel1() << " | Dept: " << check.getDept() << "\n";
                cout << "Courses Enrolled:\n";
                for (auto& C : Courses)
                {
                    if (C.getlevel_Course() == check.getLevel1() && C.getDeptName() == check.getDept())
                    {
                        cout << "  Course Name: " << C.getname() << " | Instructor: " << C.getInsName() << " | Credit Hours: " << C.getcredit_hours() << "\n";
                    }
                }
            }
        }
        if (!found) cout << "ID Not Found!\n";
    }
};

class CourseManager
{
public:
    vector<Course> Courses;

    void DisplayAllCourses(vector<Course>& Courses)
    {
        if (Courses.empty()) { cout << "No courses to display!\n"; return; }
        for (auto& C : Courses)
        {
            cout << "Course Name: " << C.getname() << " | Instructor: " << C.getInsName() << " | Dept: " << C.getDeptName() << " | Credit Hours: " << C.getcredit_hours() << " | Level: " << C.getlevel_Course() << "\n";
        }
    }
};

enum MainMenu { STUDENTS = 1, COURSES, EXIT };
enum StudentMenu
{ Add_student = 1, 
    Update_student,
    Delete_student, 
    Display_student,
    Search_Student,
    BackTo_Main
};
enum CourseMenu { DISPLAY_COURSE = 4, BACK_TO_MAIN = 6 };

void ShowMainMenu(student_manger& studentManager, CourseManager& courseManager, DataManger& dataManager)
{
    dataManager.LoadStudentsToFile(studentManager.Students);
    dataManager.LoadCoursesToFile(courseManager.Courses);

    int mainChoice;
    do {
        system("cls");
        
        cout << "\n\n";
        cout << "\t=============================================\n";
        cout << "\t     STUDENTS AND COURSES MANAGEMENT  MENU           \n";
        cout << "\t=============================================\n";
        cout << "\t   [1] Students Menu\n";
        cout << "\t   [2] Courses Menu\n";
        cout << "\t   [3] Exit\n";
        cout << "\n  Enter choice: ";
        cin >> mainChoice;

        switch (mainChoice)
        {
        case STUDENTS:
            int studentChoice;
            do {
                system("cls");
                cout << "\n\n";
                cout << "\t=============================================\n";
                cout << "\t           STUDENT MANAGEMENT MENU           \n";
                cout << "\t=============================================\n";
                cout << "\t   [1] Add New Student\n";
                cout << "\t   [2] Update Student Details\n";
                cout << "\t   [3] Delete Student\n";
                cout << "\t   [4] Display All Students\n";
                cout << "\t   [5] Search for a Student\n";
                cout << "\t   -----------------------------------------\n";
                cout << "\t   [6] Back to Main Menu\n";
                cout << "\t=============================================\n";
                cout << "\t   Enter your choice: ";
                cin >> studentChoice;
                switch (studentChoice)
                {
                case Add_student: studentManager.AddStudent(studentManager.Students);
                    dataManager.SaveStudentsToFile(studentManager.Students);
                    break;
                case Update_student: studentManager.UpdateStudent(studentManager.Students);
                    dataManager.SaveStudentsToFile(studentManager.Students);
                    break;
                case Delete_student: studentManager.DeleteStudent(studentManager.Students, dataManager);
                    dataManager.SaveStudentsToFile(studentManager.Students);
                    break;
                case Display_student: studentManager.DisplayAllStudent(studentManager.Students);
                    dataManager.SaveStudentsToFile(studentManager.Students);
                    system("pause");
                    break;
                case Search_Student: studentManager.SearchStudent(studentManager.Students, courseManager.Courses);
                    dataManager.SaveStudentsToFile(studentManager.Students);
                    system("pause");
                    break;
                }
            } while (studentChoice != BackTo_Main);
            break;
        case COURSES:
            int courseChoice;
            do {
                system("cls");
                cout << "1. Display All Courses\n6. Back to Main Menu\nEnter choice: ";
                cin >> courseChoice;
                switch (courseChoice)
                {
                case DISPLAY_COURSE: courseManager.DisplayAllCourses(courseManager.Courses); system("pause"); break;
                }
            } while (courseChoice != BACK_TO_MAIN);
            break;
        case EXIT: cout << "Exiting program...\n"; break;
        }
    } while (mainChoice != EXIT);
}

int main()
{
    student_manger studentManager;
    CourseManager courseManager;
    DataManger dataManager;
    ShowMainMenu(studentManager, courseManager, dataManager);
    return 0;
}
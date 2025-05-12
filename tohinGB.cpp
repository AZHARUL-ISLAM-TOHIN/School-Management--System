#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct User
{
    string username;
    string password;
    string role;
};

struct Student
{
    int id;
    string name;
    string studentClass;
};

struct Teacher
{
    int id;
    string name;
    string subject;
};

void pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

User signIn()
{
    User input, stored;
    cout << "\n--- Sign In ---\n";
    cout << "Username: ";
    cin >> input.username;
    cout << "Password: ";
    cin >> input.password;

    ifstream file("users.txt");
    while (file >> stored.username >> stored.password >> stored.role)
    {
        if (input.username == stored.username && input.password == stored.password)
        {
            cout << "Login successful as " << stored.role << "!\n";
            pause();
            return stored;
        }
    }
    file.close();
    cout << "Invalid credentials!\n";
    pause();
    input.role = "none";
    return input;
}

void signUp()
{
    User user;
    cout << "\n--- Sign Up ---\n";
    cout << "Username: ";
    cin >> user.username;
    cout << "Password: ";
    cin >> user.password;
    cout << "Role (admin/teacher/student): ";
    cin >> user.role;

    ofstream file("users.txt", ios::app);
    file << user.username << " " << user.password << " " << user.role << endl;
    file.close();

    cout << "User registered successfully!\n";
    pause();
}

void addStudent()
{
    Student s;
    cout << "\n--- Add Student ---\n";
    cout << "ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, s.name);
    cout << "Class: ";
    getline(cin, s.studentClass);

    ofstream file("students.txt", ios::app);
    file << s.id << "|" << s.name << "|" << s.studentClass << endl;
    file.close();
    cout << "Student added.\n";
    pause();
}

void viewStudents()
{
    ifstream file("students.txt");
    string line;
    cout << "\n--- Students List ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Class" << endl;
    cout << "------------------------------------------\n";

    while (getline(file, line))
    {
        size_t p1 = line.find("|"), p2 = line.rfind("|");
        int id = stoi(line.substr(0, p1));
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string cls = line.substr(p2 + 1);
        cout << left << setw(10) << id << setw(20) << name << setw(10) << cls << endl;
    }
    file.close();
    pause();
}

void searchStudent()
{
    int id;
    cout << "\nEnter Student ID to search: ";
    cin >> id;

    ifstream file("students.txt");
    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find("|"), p2 = line.rfind("|");
        int sid = stoi(line.substr(0, p1));
        if (sid == id)
        {
            string name = line.substr(p1 + 1, p2 - p1 - 1);
            string cls = line.substr(p2 + 1);
            cout << "ID: " << sid << "\nName: " << name << "\nClass: " << cls << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Student not found.\n";
    pause();
}

void deleteStudent()
{
    int id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;

    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(file, line))
    {
        size_t p1 = line.find("|");
        int sid = stoi(line.substr(0, p1));
        if (sid != id)
            temp << line << endl;
        else
            deleted = true;
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << (deleted ? "Student deleted.\n" : "Student not found.\n");
    pause();
}

void addTeacher()
{
    Teacher t;
    cout << "\n--- Add Teacher ---\n";
    cout << "ID: ";
    cin >> t.id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, t.name);
    cout << "Subject: ";
    getline(cin, t.subject);

    ofstream file("teachers.txt", ios::app);
    file << t.id << "|" << t.name << "|" << t.subject << endl;
    file.close();
    cout << "Teacher added.\n";
    pause();
}

void viewTeachers()
{
    ifstream file("teachers.txt");
    string line;
    cout << "\n--- Teachers List ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Subject" << endl;
    cout << "------------------------------------------------\n";

    while (getline(file, line))
    {
        size_t p1 = line.find("|"), p2 = line.rfind("|");
        int id = stoi(line.substr(0, p1));
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string subj = line.substr(p2 + 1);
        cout << left << setw(10) << id << setw(20) << name << setw(15) << subj << endl;
    }
    file.close();
    pause();
}

void searchTeacher()
{
    int id;
    cout << "\nEnter Teacher ID to search: ";
    cin >> id;

    ifstream file("teachers.txt");
    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find("|"), p2 = line.rfind("|");
        int tid = stoi(line.substr(0, p1));
        if (tid == id)
        {
            string name = line.substr(p1 + 1, p2 - p1 - 1);
            string subj = line.substr(p2 + 1);
            cout << "ID: " << tid << "\nName: " << name << "\nSubject: " << subj << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Teacher not found.\n";
    pause();
}

void deleteTeacher()
{
    int id;
    cout << "\nEnter Teacher ID to delete: ";
    cin >> id;

    ifstream file("teachers.txt");
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(file, line))
    {
        size_t p1 = line.find("|");
        int tid = stoi(line.substr(0, p1));
        if (tid != id)
            temp << line << endl;
        else
            deleted = true;
    }
    file.close();
    temp.close();
    remove("teachers.txt");
    rename("temp.txt", "teachers.txt");

    cout << (deleted ? "Teacher deleted.\n" : "Teacher not found.\n");
    pause();
}

void adminMenu()
{
    int choice;
    do
    {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Student\n2. View Students\n3. Search Student\n4. Delete Student\n";
        cout << "5. Add Teacher\n6. View Teachers\n7. Search Teacher\n8. Delete Teacher\n9. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            addTeacher();
            break;
        case 6:
            viewTeachers();
            break;
        case 7:
            searchTeacher();
            break;
        case 8:
            deleteTeacher();
            break;
        case 9:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid option\n";
            pause();
        }
    } while (choice != 9);
}

int main()
{
    int choice;
    User user;
    do
    {
        cout << "\n=== School Management System ===\n";
        cout << "1. Sign In\n2. Sign Up\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            user = signIn();
            if (user.role == "admin")
                adminMenu();
            else
                cout << "Access only for admin in this demo.\n", pause();
            break;
        case 2:
            signUp();
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice\n";
            pause();
        }
    } while (choice != 3);
    return 0;
}

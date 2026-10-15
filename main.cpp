#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Class representing an individual student
class Student {
private:
    string id;
    string name;
    double gpa;

public:
    // Constructor
    Student(string s_id, string s_name, double s_gpa) {
        id = s_id;
        name = s_name;
        gpa = s_gpa;
    }

    // Getters to access data
    string getId() { return id; }
    string getName() { return name; }
    double getGpa() { return gpa; }

    // Display student details
    void display() {
        cout << "ID: " << id << " | Name: " << name << " | GPA: " << gpa << endl;
    }
};

// Main System Class to manage students
class RecordSystem {
private:
    vector<Student> students;
    string filename = "students_database.txt";

public:
    // Load existing records from a file when the program starts
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) return;

        string id, name;
        double gpa;
        while (file >> id >> ws && getline(file, name, ',') && file >> gpa) {
            students.push_back(Student(id, name, gpa));
        }
        file.close();
    }

    // Save records to a file
    void saveToFile() {
        ofstream file(filename);
        for (size_t i = 0; i < students.size(); ++i) {
            file << students[i].getId() << " " << students[i].getName() << "," << students[i].getGpa() << "\n";
        }
        file.close();
    }

    // Add a new student
    void addStudent() {
        string id, name;
        double gpa;

        cout << "\nEnter Student ID (e.g., EITM/123/15): ";
        cin >> id;
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Cumulative GPA: ";
        cin >> gpa;

        students.push_back(Student(id, name, gpa));
        saveToFile(); // Save immediately
        cout << "\n🎉 Student successfully added and saved to database!\n";
    }

    // Display all students
    void viewAllStudents() {
        if (students.empty()) {
            cout << "\n⚠️ No records found in the database.\n";
            return;
        }
        cout << "\n--- Student Records Directory ---\n";
        for (size_t i = 0; i < students.size(); ++i) {
            students[i].display();
        }
        cout << "---------------------------------\n";
    }
};

int main() {
    RecordSystem system;
    system.loadFromFile(); // Initial load
    int choice;

    do {
        cout << "\n===============================";
        cout << "\n  EiT-M STUDENT RECORD SYSTEM  ";
        cout << "\n===============================";
        cout << "\n1. Add New Student";
        cout << "\n2. View All Records";
        cout << "\n3. Exit Program";
        cout << "\nEnter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addStudent();
                break;
            case 2:
                system.viewAllStudents();
                break;
            case 3:
                cout << "\nThank you for using the system. Goodbye!\n";
                break;
            default:
                cout << "\n⚠️ Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

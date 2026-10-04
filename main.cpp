#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

struct Student {
    int id;
    string name;
    string department;
    float gpa;
    Student* next;
};

Student* head = nullptr;

Student* createStudent(int id, string name, string department, float gpa) {
    Student* newStudent = new Student();
    newStudent->id = id;
    newStudent->name = name;
    newStudent->department = department;
    newStudent->gpa = gpa;
    newStudent->next = nullptr;
    return newStudent;
}

void addStudent(int id, string name, string department, float gpa) {
    Student* newStudent = createStudent(id, name, department, gpa);
    if (head == nullptr) { head = newStudent; return; }
    Student* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = newStudent;
    cout << "Student added successfully.\n";
}

bool removeStudent(int id) {
    if (head == nullptr) return false;
    if (head->id == id) {
        Student* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    Student* curr = head->next;
    Student* prev = head;
    while (curr != nullptr) {
        if (curr->id == id) {
            prev->next = curr->next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

Student* searchStudent(int id) {
    Student* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void displayAll() {
    if (head == nullptr) { cout << "No student records found.\n"; return; }
    cout << "\nID\tName\t\tDepartment\t\tGPA\n";
    cout << "-------------------------------------------------------------\n";
    Student* temp = head;
    while (temp != nullptr) {
        cout << temp->id << "\t" << temp->name << "\t\t" << temp->department << "\t\t" << temp->gpa << "\n";
        temp = temp->next;
    }
    cout << "\n";
}

int countStudents() {
    int count = 0;
    Student* temp = head;
    while (temp != nullptr) { count++; temp = temp->next; }
    return count;
}

// Algorithm 1: class average GPA
float averageGPA() {
    if (head == nullptr) return 0.0f;
    float sum = 0.0f;
    int count = 0;
    Student* temp = head;
    while (temp != nullptr) {
        sum += temp->gpa;
        count++;
        temp = temp->next;
    }
    return sum / count;
}

// Algorithm 2: bubble sort by GPA, highest first
// Swaps node DATA 
void sortByGPA() {
    if (head == nullptr || head->next == nullptr) return;
    bool swapped;
    do {
        swapped = false;
        Student* curr = head;
        while (curr->next != nullptr) {
            if (curr->gpa < curr->next->gpa) {
                swap(curr->id, curr->next->id);
                swap(curr->name, curr->next->name);
                swap(curr->department, curr->next->department);
                swap(curr->gpa, curr->next->gpa);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
    cout << "List sorted by GPA, highest first.\n";
}

void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file) { cout << "Error: could not open file for writing.\n"; return; }
    Student* temp = head;
    while (temp != nullptr) {
        file << temp->id << "," << temp->name << "," << temp->department << "," << temp->gpa << "\n";
        temp = temp->next;
    }
    file.close();
    cout << "Records saved to " << filename << "\n";
}

void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) { cout << "No existing file found, starting with an empty list.\n"; return; }
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
    string line;
    int loaded = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, department, gpaStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, department, ',');
        getline(ss, gpaStr, ',');
        if (idStr.empty()) continue;
        addStudent(stoi(idStr), name, department, stof(gpaStr));
        loaded++;
    }
    file.close();
    cout << "Loaded " << loaded << " records from " << filename << "\n";
}

void printMenu() {
    cout << "\n===== Student Record Manager =====\n";
    cout << "1. Add student\n";
    cout << "2. Remove student\n";
    cout << "3. Search student\n";
    cout << "4. Display all students\n";
    cout << "5. Save to file\n";
    cout << "6. Load from file\n";
    cout << "7. Show class average GPA\n";
    cout << "8. Sort students by GPA (highest first)\n";
    cout << "9. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    const string filename = "students.txt";
    loadFromFile(filename);

    int choice;
    while (true) {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            int id; string name, department; float gpa;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter name: "; cin.ignore(); getline(cin, name);
            cout << "Enter department: "; getline(cin, department);
            cout << "Enter GPA: "; cin >> gpa;
            addStudent(id, name, department, gpa);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter ID to remove: "; cin >> id;
            if (removeStudent(id)) cout << "Student removed.\n";
            else cout << "Student not found.\n";
        }
        else if (choice == 3) {
            int id;
            cout << "Enter ID to search: "; cin >> id;
            Student* result = searchStudent(id);
            if (result != nullptr)
                cout << "Found: " << result->name << ", " << result->department << ", GPA " << result->gpa << "\n";
            else
                cout << "Student not found.\n";
        }
        else if (choice == 4) {
            displayAll();
            cout << "Total students: " << countStudents() << "\n";
        }
        else if (choice == 5) saveToFile(filename);
        else if (choice == 6) loadFromFile(filename);
        else if (choice == 7) {
            if (countStudents() == 0) cout << "No students to average.\n";
            else cout << "Class average GPA: " << averageGPA() << "\n";
        }
        else if (choice == 8) {
            sortByGPA();
            displayAll();
        }
        else if (choice == 9) { cout << "Goodbye!\n"; break; }
        else cout << "Invalid option, try again.\n";
    }
    return 0;
}
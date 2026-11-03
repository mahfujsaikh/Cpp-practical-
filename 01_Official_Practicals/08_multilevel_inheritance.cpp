// EXPERIMENT 8 — Multilevel Inheritance
// Question:
// Design three classes: Student, Exam and Result. Student stores
// roll number and name. Exam inherits Student and stores marks in
// six subjects. Result inherits Exam and calculates total marks,
// percentage and grade. Identify the type of inheritance.

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Base class
class Student {
protected:
    int rollNo;
    string name;

public:
    void getStudentData() {
        cout << "Enter Roll No: ";
        cin >> rollNo;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
    }

    void showStudentData() {
        cout << "Roll No : " << rollNo << endl;
        cout << "Name    : " << name << endl;
    }
};

// Derived class (Level 1)
class Exam : public Student {
protected:
    float marks[6];

public:
    void getExamData() {
        cout << "\nEnter marks in 6 subjects:\n";

        for (int i = 0; i < 6; i++) {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
        }
    }

    void showExamData() {
        cout << "\nMarks Obtained:\n";

        for (int i = 0; i < 6; i++) {
            cout << "Subject " << i + 1
                 << ": " << marks[i] << endl;
        }
    }
};

// Derived class (Level 2)
class Result : public Exam {
private:
    float totalMarks;
    float percentage;
    char grade;

    void calculateResult() {
        totalMarks = 0;

        for (int i = 0; i < 6; i++) {
            totalMarks += marks[i];
        }

        percentage = totalMarks / 6.0f;

        if (percentage >= 90)
            grade = 'A';
        else if (percentage >= 75)
            grade = 'B';
        else if (percentage >= 60)
            grade = 'C';
        else if (percentage >= 40)
            grade = 'D';
        else
            grade = 'F';
    }

public:
    void processResult() {
        getStudentData();
        getExamData();
        calculateResult();
    }

    void displayResult() {
        cout << "\n========== RESULT SHEET ==========\n";

        showStudentData();
        showExamData();

        cout << fixed << setprecision(2);
        cout << "\nTotal Marks : " << totalMarks << " / 600" << endl;
        cout << "Percentage : " << percentage << "%" << endl;
        cout << "Grade       : " << grade << endl;
        cout << "==================================\n";
    }
};

int main() {
    int n;

    cout << "Enter number of students: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of students.";
        return 0;
    }

    Result *res = new Result[n];

    for (int i = 0; i < n; i++) {
        cout << "\n--- Student " << i + 1 << " ---\n";
        res[i].processResult();
    }

    cout << "\n========== FINAL RESULTS ==========\n";

    for (int i = 0; i < n; i++) {
        res[i].displayResult();
    }

    delete[] res;
    return 0;
}

// Inheritance type: Multilevel inheritance
// Student -> Exam -> Result

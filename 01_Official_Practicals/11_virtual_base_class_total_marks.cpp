// EXPERIMENT 11 — Virtual Base Class
// Question:
// Write a program to calculate the total marks of a student using
// the concept of virtual base class.
//
// Student is the common virtual base class. Exam and Sports inherit
// virtually from Student. Result inherits from both Exam and Sports.

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Base class
class Student
{
protected:
    int rollNo;
    string name;

public:
    void getStudentData()
    {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cout << "Enter Student Name: ";
        cin >> ws;
        getline(cin, name);
    }

    void showStudentData()
    {
        cout << "\nRoll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
    }
};

// Virtual base class
class Exam : virtual public Student
{
protected:
    float marks[5];

public:
    void getMarks()
    {
        cout << "\nEnter marks in five subjects:\n";

        for (int i = 0; i < 5; i++)
        {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
        }
    }

    float totalExamMarks()
    {
        float total = 0;

        for (int i = 0; i < 5; i++)
        {
            total += marks[i];
        }

        return total;
    }

    void showMarks()
    {
        cout << "\nSubject Marks:\n";

        for (int i = 0; i < 5; i++)
        {
            cout << "Subject " << i + 1 << ": " << marks[i] << endl;
        }
    }
};

// Virtual base class
class Sports : virtual public Student
{
protected:
    float sportsMarks;

public:
    void getSportsMarks()
    {
        cout << "\nEnter Sports Marks: ";
        cin >> sportsMarks;
    }
};

// Derived class
class Result : public Exam, public Sports
{
public:
    void displayResult()
    {
        float total = totalExamMarks() + sportsMarks;

        cout << "\n========== STUDENT RESULT ==========\n";

        showStudentData();
        showMarks();

        cout << "Sports Marks: " << sportsMarks << endl;

        cout << fixed << setprecision(2);
        cout << "\nTotal Marks: " << total << " / 600";
        cout << "\nPercentage: " << (total / 6) << "%" << endl;

        cout << "====================================\n";
    }
};

int main()
{
    Result r;

    r.getStudentData();
    r.getMarks();
    r.getSportsMarks();

    r.displayResult();

    return 0;
}

// Virtual inheritance ensures Result contains only one shared
// Student base-class subobject through Exam and Sports.

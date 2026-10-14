
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class Person
{
    char name[64];
    int age;
    char address[64];
    double salary;

public:
    // Constructor
    Person()
    {
        strcpy(name, "");
        age = 0;
        strcpy(address, "");
        salary = 0;
    }

    void input()
    {
        cout << "Enter name: ";
        cin >> ws;
        cin.getline(name, 64);

        cout << "Enter age: ";
        cin >> age;

        cout << "Enter address: ";
        cin >> ws;
        cin.getline(address, 64);

        cout << "Enter monthly salary: ";
        cin >> salary;
    }

    inline int getAge()
    {
        return age;
    }

    void displaySalarySlip()
    {
        cout << "\n----- SALARY SLIP -----\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Address: " << address << endl;
        cout << fixed << setprecision(2);
        cout << "Monthly Salary: Rs. " << salary << endl;
        cout << "Annual Salary: Rs. " << salary * 12 << endl;
    }

    void displayAgeDetails()
    {
        cout << name << " - Age: " << age << endl;
    }
};

int main()
{
    Person p[10];
    int youngest = 0, eldest = 0;

    cout << "Enter details of 10 persons:\n";

    for (int i = 0; i < 10; i++)
    {
        cout << "\nPerson " << i + 1 << ":\n";
        p[i].input();

        if (i == 0)
        {
            youngest = eldest = i;
        }
        else
        {
            if (p[i].getAge() < p[youngest].getAge())
                youngest = i;

            if (p[i].getAge() > p[eldest].getAge())
                eldest = i;
        }
    }

    cout << "\n--- YOUNGEST PERSON ---\n";
    p[youngest].displayAgeDetails();

    cout << "\n--- ELDEST PERSON ---\n";
    p[eldest].displayAgeDetails();

    cout << "\n--- SALARY SLIPS ---\n";
    for (int i = 0; i < 10; i++)
    {
        p[i].displaySalarySlip();
    }

    return 0;
}

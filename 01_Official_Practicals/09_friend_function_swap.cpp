// EXPERIMENT 9 — Friend Function
// Question:
// Write a program to swap two numbers (create two classes)
// using a friend function.

#include <iostream>
using namespace std;

class ClassB;     // Forward declaration

class ClassA {
private:
    int num;

public:
    ClassA(int n) : num(n) {}

    void display() const {
        cout << "ClassA number = " << num << endl;
    }

    friend void swapNumbers(ClassA &a, ClassB &b);
};

class ClassB {
private:
    int num;

public:
    ClassB(int n) : num(n) {}

    void display() const {
        cout << "ClassB number = " << num << endl;
    }

    friend void swapNumbers(ClassA &a, ClassB &b);
};

void swapNumbers(ClassA &a, ClassB &b) {
    int temp = a.num;
    a.num = b.num;
    b.num = temp;
}

int main() {
    int x, y;

    cout << "Enter first number (ClassA): ";
    cin >> x;

    cout << "Enter second number (ClassB): ";
    cin >> y;

    ClassA a(x);
    ClassB b(y);

    cout << "\nBefore swapping:\n";
    a.display();
    b.display();

    swapNumbers(a, b);

    cout << "\nAfter swapping:\n";
    a.display();
    b.display();

    return 0;
}

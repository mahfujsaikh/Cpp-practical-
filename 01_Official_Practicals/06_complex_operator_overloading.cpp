// EXPERIMENT 6 — Operator Overloading with Complex Numbers
// Question:
// Create a class called Complex. Overload increment and decrement
// operators (unary) and + and - operators (binary).

#include <iostream>
using namespace std;

class Complex {
    int real, imag;

public:
    Complex(int r = 0, int i = 0) {
        real = r;
        imag = i;
    }

    // Unary increment operator (prefix)
    void operator++() {
        real++;
        imag++;
    }

    // Unary decrement operator (prefix)
    void operator--() {
        real--;
        imag--;
    }

    // Binary addition operator
    Complex operator+(Complex c) {
        Complex temp;
        temp.real = real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }

    // Binary subtraction operator
    Complex operator-(Complex c) {
        Complex temp;
        temp.real = real - c.real;
        temp.imag = imag - c.imag;
        return temp;
    }

    void display() {
        cout << real;
        if (imag >= 0)
            cout << " + " << imag << "i";
        else
            cout << " - " << -imag << "i";
        cout << endl;
    }
};

int main() {
    int r, i;

    cout << "Enter real and imaginary part of Complex Number 1: ";
    cin >> r >> i;
    Complex c1(r, i);

    cout << "Enter real and imaginary part of Complex Number 2: ";
    cin >> r >> i;
    Complex c2(r, i);

    cout << "\nComplex Number 1: ";
    c1.display();
    cout << "Complex Number 2: ";
    c2.display();

    Complex c3 = c1 + c2;
    cout << "\nAddition: ";
    c3.display();

    Complex c4 = c1 - c2;
    cout << "Subtraction: ";
    c4.display();

    ++c1;
    cout << "\nAfter incrementing Complex Number 1: ";
    c1.display();

    --c2;
    cout << "After decrementing Complex Number 2: ";
    c2.display();

    return 0;
}

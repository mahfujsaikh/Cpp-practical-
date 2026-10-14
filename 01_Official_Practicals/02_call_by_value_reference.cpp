
#include <iostream>
using namespace std;

// Call by value
void swapByValue(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "Inside call by value: a = " << a
         << ", b = " << b << endl;
}

// Call by reference
void swapByReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 10, y = 20;

    cout << "Before call by value: x = " << x
         << ", y = " << y << endl;

    swapByValue(x, y);

    cout << "After call by value: x = " << x
         << ", y = " << y << endl;

    cout << "\nBefore call by reference: x = " << x
         << ", y = " << y << endl;

    swapByReference(x, y);

    cout << "After call by reference: x = " << x
         << ", y = " << y << endl;

    return 0;
}

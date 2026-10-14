
#include <iostream>
using namespace std;

const double PI = 3.14159;

// Area of a circle
double AREA(double radius)
{
    return PI * radius * radius;
}

// Area of a rectangle
double AREA(double length, double breadth)
{
    return length * breadth;
}

// Area of a triangle
double AREA(double base, double height, int)
{
    return 0.5 * base * height;
}

int main()
{
    double radius, length, breadth, base, height;

    cout << "Enter radius of circle: ";
    cin >> radius;
    cout << "Area of circle = " << AREA(radius) << endl;

    cout << "\nEnter length and breadth of rectangle: ";
    cin >> length >> breadth;
    cout << "Area of rectangle = "
         << AREA(length, breadth) << endl;

    cout << "\nEnter base and height of triangle: ";
    cin >> base >> height;
    cout << "Area of triangle = "
         << AREA(base, height, 0) << endl;

    return 0;
}

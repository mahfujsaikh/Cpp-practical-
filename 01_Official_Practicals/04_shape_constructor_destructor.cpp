
#include <iostream>
using namespace std;

class Shape
{
    double radius, length, width;

public:
    // Constructor
    Shape(double r, double l, double w)
    {
        radius = r;
        length = l;
        width = w;
        cout << "Shape object created." << endl;
    }

    void circlePerimeter()
    {
        cout << "Perimeter of circle = "
             << 2 * 3.14159 * radius << endl;
    }

    void rectanglePerimeter()
    {
        cout << "Perimeter of rectangle = "
             << 2 * (length + width) << endl;
    }

    // Destructor
    ~Shape()
    {
        cout << "Shape object destroyed." << endl;
    }
};

int main()
{
    double r, l, w;

    cout << "Enter radius of circle: ";
    cin >> r;

    cout << "Enter length of rectangle: ";
    cin >> l;

    cout << "Enter width of rectangle: ";
    cin >> w;

    if (r < 0 || l < 0 || w < 0)
    {
        cout << "Dimensions cannot be negative." << endl;
        return 1;
    }

    Shape s(r, l, w);

    s.circlePerimeter();
    s.rectanglePerimeter();

    return 0;
}

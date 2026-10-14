#include <iostream>
using namespace std;

int main()
{
    int n;
    unsigned long long fact = 1;

    cout << "Enter a non-negative integer: ";
    cin >> n;

    if (n < 0)
    {
        cout << "Factorial is not defined for negative numbers";
    }
    else if (n > 20)
    {
        cout << "Number is too large";
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            fact = fact * i;
        }

        cout << "Factorial = " << fact;
    }

    return 0;
}

#include <iostream>
using namespace std;

int main()
{
    int n;
    int first = 0, second = 1;

    cout << "Enter the number of terms: ";
    cin >> n;

    if (n < 1 || n > 94)
    {
        cout << "Enter a number between 1 and 94";
        return 0;
    }

    cout << "Fibonacci Series: ";

    for (int i = 1; i <= n; i++)
    {
        cout << first << " ";

        int next = first + second;
        first = second;
        second = next;
    }

    return 0;
}

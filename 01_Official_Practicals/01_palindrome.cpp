
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int num, original, digit, reversed = 0;

    cout << "Enter an integer: ";
    cin >> num;

    original = num;
    int temp = (num < 0) ? -num : num;

    while (temp > 0)
    {
        digit = temp % 10;
        reversed = reversed * 10 + digit;
        temp /= 10;
    }

    if (num >= 0 && original == reversed)
        cout << "Number is a palindrome." << endl;
    else
        cout << "Number is not a palindrome." << endl;

    string str;
    cout << "Enter a string (without spaces): ";
    cin >> str;

    string reverseStr = "";
    for (int i = (int)str.length() - 1; i >= 0; i--)
        reverseStr += str[i];

    if (str == reverseStr)
        cout << "String is a palindrome." << endl;
    else
        cout << "String is not a palindrome." << endl;

    return 0;
}

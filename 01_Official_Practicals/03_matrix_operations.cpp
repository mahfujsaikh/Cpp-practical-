
#include <iostream>
using namespace std;

const int MAX = 10;

void inputMatrix(int a[MAX][MAX], int r, int c)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> a[i][j];
}

void displayMatrix(int a[MAX][MAX], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void addMatrix(int a[MAX][MAX], int b[MAX][MAX],
               int r, int c)
{
    int result[MAX][MAX];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[i][j] = a[i][j] + b[i][j];

    displayMatrix(result, r, c);
}

void subtractMatrix(int a[MAX][MAX], int b[MAX][MAX],
                    int r, int c)
{
    int result[MAX][MAX];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[i][j] = a[i][j] - b[i][j];

    displayMatrix(result, r, c);
}

void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX],
                    int r1, int c1, int c2)
{
    int result[MAX][MAX] = {};

    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                result[i][j] += a[i][k] * b[k][j];

    displayMatrix(result, r1, c2);
}

void transposeMatrix(int a[MAX][MAX], int r, int c)
{
    int result[MAX][MAX];

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[j][i] = a[i][j];

    displayMatrix(result, c, r);
}

int main()
{
    int a[MAX][MAX], b[MAX][MAX];
    int r1, c1, r2, c2, choice;

    cout << "1. Addition\n2. Subtraction\n";
    cout << "3. Multiplication\n4. Transpose\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    case 2:
        cout << "Enter rows and columns: ";
        cin >> r1 >> c1;

        if (r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX)
        {
            cout << "Invalid dimensions";
            return 0;
        }

        cout << "Enter first matrix:\n";
        inputMatrix(a, r1, c1);
        cout << "Enter second matrix:\n";
        inputMatrix(b, r1, c1);

        if (choice == 1)
            addMatrix(a, b, r1, c1);
        else
            subtractMatrix(a, b, r1, c1);
        break;

    case 3:
        cout << "Enter rows and columns of first matrix: ";
        cin >> r1 >> c1;
        cout << "Enter rows and columns of second matrix: ";
        cin >> r2 >> c2;

        if (r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX ||
            r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX ||
            c1 != r2)
        {
            cout << "Invalid dimensions for multiplication";
            return 0;
        }

        cout << "Enter first matrix:\n";
        inputMatrix(a, r1, c1);
        cout << "Enter second matrix:\n";
        inputMatrix(b, r2, c2);

        multiplyMatrix(a, b, r1, c1, c2);
        break;

    case 4:
        cout << "Enter rows and columns: ";
        cin >> r1 >> c1;

        if (r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX)
        {
            cout << "Invalid dimensions";
            return 0;
        }

        cout << "Enter matrix:\n";
        inputMatrix(a, r1, c1);
        transposeMatrix(a, r1, c1);
        break;

    default:
        cout << "Invalid choice";
    }

    return 0;
}

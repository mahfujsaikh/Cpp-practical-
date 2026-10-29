#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

// abstract class for crop advice
class Advisory
{
public:
    virtual void giveAdvice() const = 0;
    virtual ~Advisory() {}
};

// base class
class Crop : public Advisory
{
protected:
    string name;
    float area;
    string season;
    float yieldPerAcre;
    static int cropCount;

public:
    Crop()
    {
        name = "Unknown";
        area = 0;
        season = "Unknown";
        yieldPerAcre = 0;
        cropCount++;
    }

    Crop(string n, float a, string s, float y)
    {
        if (a <= 0)
            throw invalid_argument("Area cannot be zero or negative");

        if (y < 0)
            throw invalid_argument("Yield cannot be negative");

        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        cropCount++;
    }

    // overloaded constructor
    Crop(string n, float a)
    {
        if (a <= 0)
            throw invalid_argument("Area cannot be zero or negative");

        name = n;
        area = a;
        season = "Not given";
        yieldPerAcre = 0;
        cropCount++;
    }

    virtual float calculateYield() const
    {
        return area * yieldPerAcre;
    }

    virtual void display() const
    {
        cout << "Name            : " << name << endl;
        cout << "Area            : " << area << " acres" << endl;
        cout << "Season          : " << season << endl;
        cout << "Yield per acre  : " << yieldPerAcre << endl;
        cout << "Total yield     : " << calculateYield() << endl;
    }

    // operator overloading to compare total yield
    bool operator>(const Crop &c) const
    {
        return calculateYield() > c.calculateYield();
    }

    virtual void saveToFile(ofstream &file) const = 0;

    string getName() const
    {
        return name;
    }

    static int getCropCount()
    {
        return cropCount;
    }

    virtual ~Crop()
    {
        cropCount--;
    }
};

int Crop::cropCount = 0;

class CerealCrop : public Crop
{
    string fertilizerType;

public:
    CerealCrop(string n, float a, string s, float y, string f)
        : Crop(n, a, s, y)
    {
        fertilizerType = f;
    }

    void display() const override
    {
        cout << "\n--- Cereal Crop ---\n";
        Crop::display();
        cout << "Fertilizer      : " << fertilizerType << endl;
    }

    void giveAdvice() const override
    {
        cout << "For " << name << ", use " << fertilizerType
             << " properly and maintain regular irrigation.\n";
    }

    void saveToFile(ofstream &file) const override
    {
        file << "Cereal, " << name << ", " << area << ", " << season
             << ", " << yieldPerAcre << ", " << fertilizerType << endl;
    }
};

class VegetableCrop : public Crop
{
    int irrigationFrequency;

public:
    VegetableCrop(string n, float a, string s, float y, int i)
        : Crop(n, a, s, y)
    {
        if (i <= 0)
            throw invalid_argument("Irrigation frequency must be positive");

        irrigationFrequency = i;
    }

    void display() const override
    {
        cout << "\n--- Vegetable Crop ---\n";
        Crop::display();
        cout << "Irrigation      : Every " << irrigationFrequency << " day(s)" << endl;
    }

    void giveAdvice() const override
    {
        cout << "For " << name << ", irrigate every " << irrigationFrequency
             << " day(s) and check for pests.\n";
    }

    void saveToFile(ofstream &file) const override
    {
        file << "Vegetable, " << name << ", " << area << ", " << season
             << ", " << yieldPerAcre << ", " << irrigationFrequency << endl;
    }
};

void showSavedData()
{
    ifstream file("crop_data.txt");
    string line;

    if (!file)
    {
        cout << "No saved file found.\n";
        return;
    }

    cout << "\n--- Data from file ---\n";
    while (getline(file, line))
        cout << line << endl;

    file.close();
}

int main()
{
    Crop *crops[10];
    int count = 0;
    int choice;

    cout << fixed << setprecision(2);

    do
    {
        cout << "\n==============================\n";
        cout << " SMART FARM MANAGEMENT SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Add Cereal Crop\n";
        cout << "2. Add Vegetable Crop\n";
        cout << "3. Display Crops\n";
        cout << "4. Farming Advice\n";
        cout << "5. Compare Two Crops\n";
        cout << "6. Save Data\n";
        cout << "7. Read Saved Data\n";
        cout << "8. Crop Count\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        try
        {
            if (choice == 1)
            {
                if (count == 10)
                {
                    cout << "Maximum crop limit reached.\n";
                    continue;
                }

                string name, season, fertilizer;
                float area, cropYield;

                cout << "Crop name: ";
                cin >> ws;
                getline(cin, name);

                cout << "Area in acres: ";
                cin >> area;

                cout << "Season: ";
                cin >> ws;
                getline(cin, season);

                cout << "Yield per acre: ";
                cin >> cropYield;

                cout << "Fertilizer type: ";
                cin >> ws;
                getline(cin, fertilizer);

                crops[count] = new CerealCrop(name, area, season, cropYield, fertilizer);
                count++;
                cout << "Cereal crop added.\n";
            }

            else if (choice == 2)
            {
                if (count == 10)
                {
                    cout << "Maximum crop limit reached.\n";
                    continue;
                }

                string name, season;
                float area, cropYield;
                int irrigation;

                cout << "Crop name: ";
                cin >> ws;
                getline(cin, name);

                cout << "Area in acres: ";
                cin >> area;

                cout << "Season: ";
                cin >> ws;
                getline(cin, season);

                cout << "Yield per acre: ";
                cin >> cropYield;

                cout << "Irrigation frequency in days: ";
                cin >> irrigation;

                crops[count] = new VegetableCrop(name, area, season, cropYield, irrigation);
                count++;
                cout << "Vegetable crop added.\n";
            }

            else if (choice == 3)
            {
                if (count == 0)
                    cout << "No crop records available.\n";
                else
                {
                    for (int i = 0; i < count; i++)
                        crops[i]->display();
                }
            }

            else if (choice == 4)
            {
                if (count == 0)
                    cout << "No crops available.\n";
                else
                {
                    for (int i = 0; i < count; i++)
                        crops[i]->giveAdvice();
                }
            }

            else if (choice == 5)
            {
                if (count < 2)
                {
                    cout << "Add at least two crops first.\n";
                    continue;
                }

                int a, b;

                for (int i = 0; i < count; i++)
                    cout << i + 1 << ". " << crops[i]->getName() << endl;

                cout << "Choose first crop: ";
                cin >> a;
                cout << "Choose second crop: ";
                cin >> b;

                if (a < 1 || a > count || b < 1 || b > count)
                    throw out_of_range("Invalid crop number");

                if (*crops[a - 1] > *crops[b - 1])
                    cout << crops[a - 1]->getName() << " has higher total yield.\n";
                else if (*crops[b - 1] > *crops[a - 1])
                    cout << crops[b - 1]->getName() << " has higher total yield.\n";
                else
                    cout << "Both crops have the same total yield.\n";
            }

            else if (choice == 6)
            {
                ofstream file("crop_data.txt");

                if (!file)
                    throw runtime_error("File could not be opened");

                for (int i = 0; i < count; i++)
                    crops[i]->saveToFile(file);

                file.close();
                cout << "Data saved to crop_data.txt\n";
            }

            else if (choice == 7)
            {
                showSavedData();
            }

            else if (choice == 8)
            {
                cout << "Total crop objects: " << Crop::getCropCount() << endl;
            }

            else if (choice == 0)
            {
                cout << "Program ended.\n";
            }

            else
            {
                cout << "Invalid menu choice.\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    for (int i = 0; i < count; i++)
        delete crops[i];

    return 0;
}

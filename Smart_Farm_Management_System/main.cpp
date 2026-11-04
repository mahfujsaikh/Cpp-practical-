#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <limits>
using namespace std;

// Abstract class for farming advice
class Advisory
{
public:
    virtual void giveAdvice() const = 0;
    virtual ~Advisory() {}
};

// Base class for all crops
class Crop : public Advisory
{
protected:
    string name, season;
    float area, yieldPerAcre;
    static int cropCount;

public:
    Crop()
    {
        name = "Unknown";
        season = "Unknown";
        area = 0;
        yieldPerAcre = 0;
        cropCount++;
    }

    Crop(string n, float a, string s, float y)
    {
        if (a <= 0)
            throw invalid_argument("Area must be greater than zero.");
        if (y < 0)
            throw invalid_argument("Yield cannot be negative.");

        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        cropCount++;
    }

    // Another constructor with fewer arguments
    Crop(string n, float a)
    {
        if (a <= 0)
            throw invalid_argument("Area must be greater than zero.");

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
        cout << "Name           : " << name << endl;
        cout << "Area           : " << area << " acres" << endl;
        cout << "Season         : " << season << endl;
        cout << "Yield per acre : " << yieldPerAcre << endl;
        cout << "Total yield    : " << calculateYield() << endl;
    }

    // Compare the total yields of two crop objects
    bool operator>(const Crop &other) const
    {
        return calculateYield() > other.calculateYield();
    }

    virtual void saveToFile(ofstream &file) const = 0;

    string getName() const { return name; }
    static int getCropCount() { return cropCount; }

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

    float calculateYield() const override
    {
        return area * yieldPerAcre;
    }

    void display() const override
    {
        cout << "\n--- Cereal Crop ---\n";
        Crop::display();
        cout << "Fertilizer     : " << fertilizerType << endl;
    }

    void giveAdvice() const override
    {
        cout << "For " << name << ", use " << fertilizerType
             << " as needed and maintain regular irrigation.\n";
    }

    void saveToFile(ofstream &file) const override
    {
        file << "Cereal," << name << "," << area << "," << season << ","
             << yieldPerAcre << "," << fertilizerType << endl;
    }
};

class VegetableCrop : public Crop
{
    int irrigationFrequency;

public:
    VegetableCrop(string n, float a, string s, float y, int days)
        : Crop(n, a, s, y)
    {
        if (days <= 0)
            throw invalid_argument("Irrigation frequency must be positive.");
        irrigationFrequency = days;
    }

    float calculateYield() const override
    {
        return area * yieldPerAcre;
    }

    void display() const override
    {
        cout << "\n--- Vegetable Crop ---\n";
        Crop::display();
        cout << "Irrigation     : Every " << irrigationFrequency << " day(s)" << endl;
    }

    void giveAdvice() const override
    {
        cout << "For " << name << ", irrigate about every " << irrigationFrequency
             << " day(s) and check regularly for pests.\n";
    }

    void saveToFile(ofstream &file) const override
    {
        file << "Vegetable," << name << "," << area << "," << season << ","
             << yieldPerAcre << "," << irrigationFrequency << endl;
    }
};

// Read the records previously saved in the text file
void readSavedData()
{
    ifstream file("crop_data.txt");
    if (!file)
    {
        cout << "No saved file found.\n";
        return;
    }

    cout << "\n--- Saved crop data ---\n";
    string line;
    while (getline(file, line))
        cout << line << endl;
    file.close();
}

int main()
{
    Crop *crops[10] = {nullptr};
    int count = 0;
    int choice = -1;
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

        if (!(cin >> choice))
        {
            if (cin.eof())
                break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from the menu.\n";
            choice = -1;
            continue;
        }

        try
        {
            if (choice == 1 || choice == 2)
            {
                if (count == 10)
                {
                    cout << "Maximum crop limit reached.\n";
                    continue;
                }

                string cropName, cropSeason;
                float cropArea, cropYield;
                cout << "Crop name: ";
                cin >> ws;
                getline(cin, cropName);
                cout << "Area in acres: ";
                if (!(cin >> cropArea))
                    throw invalid_argument("Enter a valid number for area.");
                cout << "Season: ";
                cin >> ws;
                getline(cin, cropSeason);
                cout << "Yield per acre (kg): ";
                if (!(cin >> cropYield))
                    throw invalid_argument("Enter a valid number for yield.");

                if (choice == 1)
                {
                    string fertilizer;
                    cout << "Fertilizer type: ";
                    cin >> ws;
                    getline(cin, fertilizer);
                    crops[count] = new CerealCrop(cropName, cropArea, cropSeason,
                                                  cropYield, fertilizer);
                    cout << "Cereal crop added.\n";
                }
                else
                {
                    int days;
                    cout << "Irrigation frequency in days: ";
                    if (!(cin >> days))
                        throw invalid_argument("Enter a valid number of days.");
                    crops[count] = new VegetableCrop(cropName, cropArea, cropSeason,
                                                     cropYield, days);
                    cout << "Vegetable crop added.\n";
                }
                count++;
            }
            else if (choice == 3)
            {
                if (count == 0)
                    cout << "No crop records available.\n";
                else
                    for (int i = 0; i < count; i++)
                        crops[i]->display();
            }
            else if (choice == 4)
            {
                if (count == 0)
                    cout << "No crops available.\n";
                else
                    for (int i = 0; i < count; i++)
                        crops[i]->giveAdvice();
            }
            else if (choice == 5)
            {
                if (count < 2)
                {
                    cout << "Add at least two crops first.\n";
                    continue;
                }
                for (int i = 0; i < count; i++)
                    cout << i + 1 << ". " << crops[i]->getName() << endl;

                int a, b;
                cout << "Choose first crop: ";
                if (!(cin >> a))
                    throw invalid_argument("Enter a valid crop number.");
                cout << "Choose second crop: ";
                if (!(cin >> b))
                    throw invalid_argument("Enter a valid crop number.");
                if (a < 1 || a > count || b < 1 || b > count || a == b)
                    throw out_of_range("Choose two different valid crop numbers.");

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
                    throw runtime_error("File could not be opened.");
                for (int i = 0; i < count; i++)
                    crops[i]->saveToFile(file);
                if (!file.good())
                    throw runtime_error("Error while saving crop data.");
                file.close();
                cout << "Data saved to crop_data.txt\n";
            }
            else if (choice == 7)
                readSavedData();
            else if (choice == 8)
                cout << "Total crop objects: " << Crop::getCropCount() << endl;
            else if (choice == 0)
                cout << "Program ended.\n";
            else
                cout << "Invalid menu choice.\n";
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
            if (cin.fail())
            {
                if (cin.eof())
                    choice = 0;
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
    } while (choice != 0);

    for (int i = 0; i < count; i++)
        delete crops[i];
    return 0;
}

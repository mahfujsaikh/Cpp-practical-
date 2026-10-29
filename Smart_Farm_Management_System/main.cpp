#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

class Advisory
{
public:
    virtual void giveAdvice() const = 0;
    virtual ~Advisory() {}
};

class Crop
{
protected:
    string name;
    double area;
    string season;
    double yieldPerAcre;
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

    Crop(string n, double a, string s, double y)
    {
        if (a <= 0)
            throw invalid_argument("Area must be greater than zero.");
        if (y < 0)
            throw invalid_argument("Yield per acre cannot be negative.");

        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        cropCount++;
    }

    Crop(string n, double a)
    {
        if (a <= 0)
            throw invalid_argument("Area must be greater than zero.");

        name = n;
        area = a;
        season = "Not specified";
        yieldPerAcre = 0;
        cropCount++;
    }

    virtual double calculateYield() const
    {
        return area * yieldPerAcre;
    }

    virtual void display() const
    {
        cout << "Crop Name       : " << name << endl;
        cout << "Area            : " << area << " acres" << endl;
        cout << "Season          : " << season << endl;
        cout << "Yield per Acre  : " << yieldPerAcre << endl;
        cout << "Total Yield     : " << calculateYield() << endl;
    }

    bool operator>(const Crop &other) const
    {
        return calculateYield() > other.calculateYield();
    }

    virtual void saveToFile(ofstream &file) const = 0;

    static int getCropCount()
    {
        return cropCount;
    }

    string getName() const
    {
        return name;
    }

    virtual ~Crop()
    {
        cropCount--;
    }
};

int Crop::cropCount = 0;

class CerealCrop : public Crop, public Advisory
{
private:
    string fertilizerType;

public:
    CerealCrop(string n, double a, string s, double y, string fertilizer)
        : Crop(n, a, s, y)
    {
        fertilizerType = fertilizer;
    }

    void display() const override
    {
        cout << "\n----- Cereal Crop Details -----\n";
        Crop::display();
        cout << "Fertilizer Type : " << fertilizerType << endl;
    }

    void giveAdvice() const override
    {
        cout << "Advice for " << name << ": Use " << fertilizerType
             << " as required and maintain proper irrigation.\n";
    }

    void saveToFile(ofstream &file) const override
    {
        file << "Cereal|" << name << "|" << area << "|" << season << "|"
             << yieldPerAcre << "|" << fertilizerType << endl;
    }
};

class VegetableCrop : public Crop, public Advisory
{
private:
    int irrigationFrequency;

public:
    VegetableCrop(string n, double a, string s, double y, int irrigation)
        : Crop(n, a, s, y)
    {
        if (irrigation <= 0)
            throw invalid_argument("Irrigation frequency must be positive.");

        irrigationFrequency = irrigation;
    }

    void display() const override
    {
        cout << "\n----- Vegetable Crop Details -----\n";
        Crop::display();
        cout << "Irrigation      : Every " << irrigationFrequency << " day(s)" << endl;
    }

    void giveAdvice() const override
    {
        cout << "Advice for " << name << ": Irrigate about every "
             << irrigationFrequency << " day(s) and check regularly for pests.\n";
    }

    void saveToFile(ofstream &file) const override
    {
        file << "Vegetable|" << name << "|" << area << "|" << season << "|"
             << yieldPerAcre << "|" << irrigationFrequency << endl;
    }
};

void saveAllCrops(Crop *crops[], int numberOfCrops)
{
    ofstream file("crop_data.txt");

    if (!file)
        throw runtime_error("Could not open crop_data.txt for writing.");

    for (int i = 0; i < numberOfCrops; i++)
        crops[i]->saveToFile(file);

    file.close();
    cout << "\nCrop data saved successfully.\n";
}

void loadCropsFromFile(Crop *crops[], int &numberOfCrops)
{
    ifstream file("crop_data.txt");

    if (!file)
    {
        cout << "\nNo saved crop data found.\n";
        return;
    }

    for (int i = 0; i < numberOfCrops; i++)
        delete crops[i];
    numberOfCrops = 0;

    string line;

    while (getline(file, line) && numberOfCrops < 10)
    {
        stringstream ss(line);
        string type, name, areaText, season, yieldText, extra;

        getline(ss, type, '|');
        getline(ss, name, '|');
        getline(ss, areaText, '|');
        getline(ss, season, '|');
        getline(ss, yieldText, '|');
        getline(ss, extra);

        if (type.empty() || name.empty() || areaText.empty() || yieldText.empty() || extra.empty())
            continue;

        try
        {
            double area = stod(areaText);
            double cropYield = stod(yieldText);

            if (type == "Cereal")
            {
                crops[numberOfCrops] = new CerealCrop(name, area, season, cropYield, extra);
                numberOfCrops++;
            }
            else if (type == "Vegetable")
            {
                int irrigation = stoi(extra);
                crops[numberOfCrops] = new VegetableCrop(name, area, season, cropYield, irrigation);
                numberOfCrops++;
            }
        }
        catch (...)
        {
            cout << "One invalid record was skipped while loading.\n";
        }
    }

    file.close();
    cout << "\nSaved crop data loaded successfully.\n";
}

int main()
{
    cout << fixed << setprecision(2);

    Crop *crops[10] = {nullptr};
    int numberOfCrops = 0;
    int choice = -1;

    do
    {
        cout << "\n=====================================\n";
        cout << "     SMART FARM MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Add Cereal Crop\n";
        cout << "2. Add Vegetable Crop\n";
        cout << "3. Display All Crops\n";
        cout << "4. Get Farming Advice\n";
        cout << "5. Compare Two Crops\n";
        cout << "6. Save Crop Data\n";
        cout << "7. Load Saved Crop Data\n";
        cout << "8. Show Number of Crops\n";
        cout << "0. Exit\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number from the menu.\n";
            continue;
        }

        try
        {
            if (choice == 1)
            {
                if (numberOfCrops >= 10)
                {
                    cout << "Crop storage is full.\n";
                    continue;
                }

                string name, season, fertilizer;
                double area, cropYield;

                cout << "Enter cereal name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter cultivation area (acres): ";
                cin >> area;
                cout << "Enter season: ";
                cin >> ws;
                getline(cin, season);
                cout << "Enter expected yield per acre: ";
                cin >> cropYield;
                cout << "Enter fertilizer type: ";
                cin >> ws;
                getline(cin, fertilizer);

                crops[numberOfCrops] = new CerealCrop(name, area, season, cropYield, fertilizer);
                numberOfCrops++;
                cout << "Cereal crop added successfully.\n";
            }
            else if (choice == 2)
            {
                if (numberOfCrops >= 10)
                {
                    cout << "Crop storage is full.\n";
                    continue;
                }

                string name, season;
                double area, cropYield;
                int irrigation;

                cout << "Enter vegetable name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter cultivation area (acres): ";
                cin >> area;
                cout << "Enter season: ";
                cin >> ws;
                getline(cin, season);
                cout << "Enter expected yield per acre: ";
                cin >> cropYield;
                cout << "Irrigation frequency (in days): ";
                cin >> irrigation;

                crops[numberOfCrops] = new VegetableCrop(name, area, season, cropYield, irrigation);
                numberOfCrops++;
                cout << "Vegetable crop added successfully.\n";
            }
            else if (choice == 3)
            {
                if (numberOfCrops == 0)
                    cout << "\nNo crops have been added yet.\n";
                else
                {
                    cout << "\n========== CROP RECORDS ==========\n";
                    for (int i = 0; i < numberOfCrops; i++)
                        crops[i]->display();
                }
            }
            else if (choice == 4)
            {
                if (numberOfCrops == 0)
                    cout << "\nNo crops available for advice.\n";
                else
                {
                    cout << "\n========== FARMING ADVICE ==========\n";
                    for (int i = 0; i < numberOfCrops; i++)
                    {
                        Advisory *advice = dynamic_cast<Advisory *>(crops[i]);
                        if (advice != nullptr)
                            advice->giveAdvice();
                    }
                }
            }
            else if (choice == 5)
            {
                if (numberOfCrops < 2)
                {
                    cout << "\nAt least two crops are needed for comparison.\n";
                    continue;
                }

                cout << "\nAvailable crops:\n";
                for (int i = 0; i < numberOfCrops; i++)
                    cout << i + 1 << ". " << crops[i]->getName() << endl;

                int first, second;
                cout << "Select first crop: ";
                cin >> first;
                cout << "Select second crop: ";
                cin >> second;

                if (first < 1 || first > numberOfCrops || second < 1 || second > numberOfCrops)
                    throw out_of_range("Invalid crop number selected.");

                Crop &crop1 = *crops[first - 1];
                Crop &crop2 = *crops[second - 1];

                if (crop1 > crop2)
                    cout << crop1.getName() << " has a higher total yield than " << crop2.getName() << ".\n";
                else if (crop2 > crop1)
                    cout << crop2.getName() << " has a higher total yield than " << crop1.getName() << ".\n";
                else
                    cout << "Both crops have equal total yield.\n";
            }
            else if (choice == 6)
            {
                saveAllCrops(crops, numberOfCrops);
            }
            else if (choice == 7)
            {
                loadCropsFromFile(crops, numberOfCrops);
            }
            else if (choice == 8)
            {
                cout << "\nCurrent number of crop objects: " << Crop::getCropCount() << endl;
            }
            else if (choice == 0)
            {
                cout << "\nExiting Smart Farm Management System...\n";
            }
            else
            {
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
        catch (const exception &e)
        {
            cout << "\nError: " << e.what() << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

    } while (choice != 0);

    for (int i = 0; i < numberOfCrops; i++)
        delete crops[i];

    return 0;
}

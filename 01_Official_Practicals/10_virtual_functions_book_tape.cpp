// EXPERIMENT 10 — Virtual Functions
// Question:
// Model a bookshop that sells books and video tapes. Create a base
// class Media with title and publication. Derive Book (number of pages)
// and Tape (playing time). Define read() and show() as virtual functions
// in the base class and process the objects using base class pointers.
// Also refer to the practical write-up for the rules of virtual functions.

#include <iostream>
#include <string>
using namespace std;

// Base class
class Media
{
protected:
    string title, publication;

public:
    virtual void read()
    {
        cout << "Enter title: ";
        getline(cin >> ws, title);

        cout << "Enter publication: ";
        getline(cin >> ws, publication);
    }

    virtual void show() const
    {
        cout << "Title: " << title << endl;
        cout << "Publication: " << publication << endl;
    }

    virtual ~Media()
    {
    }
};

// Derived class Book
class Book : public Media
{
    int pages;

public:
    void read() override
    {
        cout << "\nEnter Book Details:\n";
        Media::read();

        cout << "Enter number of pages: ";
        cin >> pages;
    }

    void show() const override
    {
        cout << "\n--- BOOK DETAILS ---\n";
        Media::show();
        cout << "Number of Pages: " << pages << endl;
    }
};

// Derived class Tape
class Tape : public Media
{
    float playingTime;

public:
    void read() override
    {
        cout << "\nEnter Tape Details:\n";
        Media::read();

        cout << "Enter playing time (minutes): ";
        cin >> playingTime;
    }

    void show() const override
    {
        cout << "\n--- TAPE DETAILS ---\n";
        Media::show();
        cout << "Playing Time: " << playingTime << " minutes" << endl;
    }
};

int main()
{
    Book b;
    Tape t;

    // Base class pointers
    Media *ptr[2];

    ptr[0] = &b;
    ptr[1] = &t;

    // Read details through base class pointers
    for (int i = 0; i < 2; i++)
    {
        ptr[i]->read();
    }

    // Display details through base class pointers
    for (int i = 0; i < 2; i++)
    {
        ptr[i]->show();
    }

    return 0;
}

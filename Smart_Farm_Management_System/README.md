# Smart Farm Management System

This is a simple C++ console project made for our OOP assignment. The program stores crop details and demonstrates the main concepts asked in the assignment.

## What the program can do

- Add cereal crops and vegetable crops
- Store crop name, area, season and yield per acre
- Calculate total yield
- Display crop details
- Give simple farming advice
- Compare two crops by total yield
- Save crop data to a text file
- Load saved crop data again
- Count how many crop objects are currently present
- Handle invalid area, yield and menu input

## OOP concepts used

- Class and object
- Inheritance
- Constructor overloading
- Runtime polymorphism using virtual functions
- Virtual destructor
- Operator overloading
- Abstract class and pure virtual function
- Static data member
- File handling
- Exception handling

## Main class structure

`Crop` is the base class. It stores the common information for all crops:

- name
- area
- season
- yield per acre

`CerealCrop` and `VegetableCrop` inherit from `Crop`.

`CerealCrop` has an extra data member for fertilizer type, while `VegetableCrop` stores irrigation frequency.

The `Advisory` class is abstract and contains the pure virtual function `giveAdvice()`. Both derived crop classes implement this function differently.

## Yield calculation

Total yield is calculated by:

`Total Yield = Area x Yield per Acre`

## Files in this folder

- `main.cpp` - main source code
- `crop_data.txt` - sample saved crop records
- `sample_output.txt` - a sample run of the program

## Compile and run

Using g++:

```bash
g++ main.cpp -o smartfarm
./smartfarm
```

On Windows, after compilation, run:

```bash
smartfarm.exe
```

## Note

The program currently stores up to 10 crop records at a time. Option 6 saves them to `crop_data.txt`, and option 7 loads the saved records back into the program.

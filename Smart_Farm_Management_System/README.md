# Smart Farm Management System

This is my C++ OOP assignment based on a simple farm management system.

The program can store cereal and vegetable crop details, calculate total yield, compare two crops, give basic farming advice and save crop records in a text file.

## Concepts used

- Classes and objects
- Inheritance
- Constructor overloading
- Runtime polymorphism
- Virtual destructor
- Operator overloading
- Abstract class and pure virtual function
- Static member
- File handling
- Exception handling

## Classes

`Crop` is the base class and stores common details like crop name, area, season and yield per acre.

`CerealCrop` stores fertilizer type.

`VegetableCrop` stores irrigation frequency.

`Advisory` is an abstract class containing `giveAdvice()`.

## Total yield

Total Yield = Area x Yield per Acre

## Files

- `main.cpp` - program code
- `crop_data.txt` - sample crop data
- `sample_output.txt` - sample program output

## Compile

```bash
g++ main.cpp -o smartfarm
```

Then run the program and use the menu options.

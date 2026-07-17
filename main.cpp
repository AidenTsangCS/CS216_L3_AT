// CS216 Lab: Fraction Class with Exceptions
// Aiden
// Lab 3

#include <iostream>
#include <limits>
#include <string>

using namespace std;

const string ERR_ZERO_DENOMINATOR = "Denominator cannot be zero (division by zero is undefined)";
const string ERR_ZERO_NUMERATOR = "Numerator cannot be zero (0/n is not a legal fraction)";
const string ERR_NEGATIVE =
    "Whole, numerator, and denominator must not be negative (only positive fractions are allowed)";
const string ERR_IMPROPER_MIXED =
    "Numerator cannot be greater than the denominator when the whole part is greater than zero";
const string ERR_UNKNOWN = "An unknown error occurred while working with a fraction";

class FractionException {
   private:
    string message = ERR_UNKNOWN;

   public:
    FractionException();
    explicit FractionException(const string& errorMessage);
    void setMessage(const string& errorMessage);
    string what() const;
};

class Fraction {
   private:
    static const int DEFAULT_NUMERATOR = 1;
    static const int DEFAULT_DENOMINATOR = 1;
    static int objectCount;

    int numerator = DEFAULT_NUMERATOR;
    int denominator = DEFAULT_DENOMINATOR;

   public:
    Fraction();
    Fraction(const Fraction& other);
    Fraction(int newNumerator);
    Fraction(int newNumerator, int newDenominator);
    Fraction(int newWhole, int newNumerator, int newDenominator);
    ~Fraction();

    void setNumerator(int newNumerator);
    void setDenominator(int newDenominator);
    void setFraction(int newNumerator);
    void setFraction(int newNumerator, int newDenominator);
    void setFraction(int newWhole, int newNumerator, int newDenominator);

    string toString() const;
    void print() const;
    static int getCount();
};

enum MenuOption { DEMO = 1, QUIT };

void clearCin(const string& errorMessage);
void printObjectCount(const string& label);
void demo();

int main() {
    int menuChoice = 0;
    do {
        cout << "\n\nFraction Class Menu:\n"
                "1. Demo\n"
                "2. Quit\n"
                "Enter your choice: ";
        cin >> menuChoice;
        switch (menuChoice) {
            case DEMO:
                demo();
                break;
            case QUIT:
                cout << "\nGoodbye!\n";
                break;
            default:
                clearCin("Invalid menu choice");
        }
    } while (menuChoice != QUIT);
    return 0;
}

int Fraction::objectCount = 0;

FractionException::FractionException() {}

FractionException::FractionException(const string& errorMessage) {
    setMessage(errorMessage);
}

void FractionException::setMessage(const string& errorMessage) {
    message = errorMessage;
}

string FractionException::what() const {
    return message;
}

Fraction::Fraction() {
    objectCount++;
}

Fraction::Fraction(const Fraction& other) {
    setFraction(0, other.numerator, other.denominator);
    objectCount++;
}

Fraction::Fraction(int newNumerator) {
    setFraction(0, newNumerator, DEFAULT_DENOMINATOR);
    objectCount++;
}

Fraction::Fraction(int newNumerator, int newDenominator) {
    setFraction(0, newNumerator, newDenominator);
    objectCount++;
}

Fraction::Fraction(int newWhole, int newNumerator, int newDenominator) {
    setFraction(newWhole, newNumerator, newDenominator);
    objectCount++;
}

Fraction::~Fraction() {
    numerator = 0;
    denominator = 1;
    objectCount--;
}

void Fraction::setNumerator(int newNumerator) {
    setFraction(numerator / denominator, newNumerator, denominator);
}

void Fraction::setDenominator(int newDenominator) {
    setFraction(0, numerator, newDenominator);
}

void Fraction::setFraction(int newNumerator) {
    setFraction(0, newNumerator, DEFAULT_DENOMINATOR);
}

void Fraction::setFraction(int newNumerator, int newDenominator) {
    setFraction(0, newNumerator, newDenominator);
}

void Fraction::setFraction(int newWhole, int newNumerator, int newDenominator) {
    try {
        if (newWhole < 0 || newNumerator < 0 || newDenominator < 0) {
            throw FractionException(ERR_NEGATIVE);
        }
        if (newDenominator == 0) {
            throw FractionException(ERR_ZERO_DENOMINATOR);
        }
        if (newNumerator == 0) {
            throw FractionException(ERR_ZERO_NUMERATOR);
        }
        if (newWhole > 0 && newNumerator > newDenominator) {
            throw FractionException(ERR_IMPROPER_MIXED);
        }
        numerator = newWhole * newDenominator + newNumerator;
        denominator = newDenominator;
    } catch (const FractionException& error) {
        cout << '\n' << error.what() << '\n';
    } catch (...) {
        cout << '\n' << ERR_UNKNOWN << '\n';
    }
}

string Fraction::toString() const {
    string result;
    int whole = numerator / denominator;
    int remainder = numerator % denominator;
    if (whole > 0 && remainder > 0) {
        result = to_string(whole) + " " + to_string(remainder) + "/" + to_string(denominator);
    } else if (whole > 0) {
        result = to_string(whole);
    } else {
        result = to_string(numerator) + "/" + to_string(denominator);
    }
    return result;
}

void Fraction::print() const {
    cout << toString() << '\n';
}

int Fraction::getCount() {
    return objectCount;
}

void clearCin(const string& errorMessage) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << '\n' << errorMessage << '\n';
}

void printObjectCount(const string& label) {
    cout << "Fraction objects in memory (" << label << "): " << Fraction::getCount() << '\n';
}

void demo() {
    cout << "\n--- Fraction Class Demo ---\n";
    printObjectCount("start of demo");
    {
        cout << "\nCreating testFraction(2, 3, 4)\n";
        Fraction testFraction(2, 3, 4);
        cout << "testFraction: ";
        testFraction.print();

        cout << '\n';
        printObjectCount("before zero denominator demo");
        cout << "Attempting testFraction.setDenominator(0)";
        testFraction.setDenominator(0);
        cout << "testFraction unchanged: ";
        testFraction.print();
        printObjectCount("after zero denominator demo");

        cout << '\n';
        printObjectCount("before zero numerator demo");
        cout << "Attempting testFraction.setNumerator(0)";
        testFraction.setNumerator(0);
        cout << "testFraction unchanged: ";
        testFraction.print();
        printObjectCount("after zero numerator demo");

        cout << '\n';
        printObjectCount("before negative value demo");
        cout << "Attempting testFraction.setFraction(3, -4)";
        testFraction.setFraction(3, -4);
        cout << "testFraction unchanged: ";
        testFraction.print();
        printObjectCount("after negative value demo");

        cout << '\n';
        printObjectCount("before invalid mixed number demo");
        cout << "Attempting testFraction.setFraction(5, 7, 3)";
        testFraction.setFraction(5, 7, 3);
        cout << "testFraction unchanged: ";
        testFraction.print();
        printObjectCount("after invalid mixed number demo");

        cout << '\n';
        printObjectCount("before constructor failure demo");
        {
            cout << "Attempting Fraction badFraction(-3, 6, 7)";
            Fraction badFraction(-3, 6, 7);
            cout << "badFraction set to default values: ";
            badFraction.print();
            printObjectCount("badFraction alive");
        }
        printObjectCount("after constructor failure demo, badFraction destroyed");

        cout << "\nCreating copyFraction as a copy of testFraction\n";
        Fraction copyFraction(testFraction);
        cout << "copyFraction: ";
        copyFraction.print();
        printObjectCount("copyFraction alive");
    }
    printObjectCount("end of demo, destructors have run");
}
/*aidentsang@Aidens-MacBook-Pro src % "/Users/aidentsang/Pierce college Labs
C++/CS216_L3_AT/build/main"


Fraction Class Menu:
1. Demo
2. Quit
Enter your choice: 1

--- Fraction Class Demo ---
Fraction objects in memory (start of demo): 0

Creating testFraction(2, 3, 4)
testFraction: 2 3/4

Fraction objects in memory (before zero denominator demo): 1
Attempting testFraction.setDenominator(0)
Denominator cannot be zero (division by zero is undefined)
testFraction unchanged: 2 3/4
Fraction objects in memory (after zero denominator demo): 1

Fraction objects in memory (before zero numerator demo): 1
Attempting testFraction.setNumerator(0)
Numerator cannot be zero (0/n is not a legal fraction)
testFraction unchanged: 2 3/4
Fraction objects in memory (after zero numerator demo): 1

Fraction objects in memory (before negative value demo): 1
Attempting testFraction.setFraction(3, -4)
Whole, numerator, and denominator must not be negative (only positive fractions are allowed)
testFraction unchanged: 2 3/4
Fraction objects in memory (after negative value demo): 1

Fraction objects in memory (before invalid mixed number demo): 1
Attempting testFraction.setFraction(5, 7, 3)
Numerator cannot be greater than the denominator when the whole part is greater than zero
testFraction unchanged: 2 3/4
Fraction objects in memory (after invalid mixed number demo): 1

Fraction objects in memory (before constructor failure demo): 1
Attempting Fraction badFraction(-3, 6, 7)
Whole, numerator, and denominator must not be negative (only positive fractions are allowed)
badFraction set to default values: 1
Fraction objects in memory (badFraction alive): 2
Fraction objects in memory (after constructor failure demo, badFraction destroyed): 1

Creating copyFraction as a copy of testFraction
copyFraction: 2 3/4
Fraction objects in memory (copyFraction alive): 2
Fraction objects in memory (end of demo, destructors have run): 0


Fraction Class Menu:
1. Demo
2. Quit
Enter your choice: 3

Invalid menu choice


Fraction Class Menu:
1. Demo
2. Quit
Enter your choice: i!

Invalid menu choice


Fraction Class Menu:
1. Demo
2. Quit
Enter your choice: 2

Goodbye!
aidentsang@Aidens-MacBook-Pro src % "/Users/aidentsang/Pierce college Labs
C++/CS216_L3_AT/build/main"*/

// CS216 Lab: Fraction Class with Exceptions
// Aiden
// Lab 3

#include <iostream>
#include <limits>
#include <string>

using namespace std;

const string ERR_ZERO_DENOMINATOR = "Denominator cannot be zero (division by zero is undefined).";
const string ERR_ZERO_NUMERATOR = "Numerator cannot be zero (0/n is not a legal fraction).";
const string ERR_NEGATIVE =
    "Whole, numerator, and denominator must not be negative (only positive fractions are allowed).";
const string ERR_IMPROPER_MIXED =
    "Numerator cannot be greater than the denominator when the whole part is greater than zero "
    "(e.g., 5 7/3 is not a legal fraction).";
const string ERR_UNKNOWN = "An unknown error occurred while working with a fraction.";

class FractionException {
   public:
    FractionException();
    FractionException(const string& errorMessage);

    string getMessage() const;

   private:
    string message = ERR_UNKNOWN;
};

class Fraction {
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

   private:
    static const int DEFAULT_NUMERATOR = 1;
    static const int DEFAULT_DENOMINATOR = 1;
    static int objectCount;

    int numerator = DEFAULT_NUMERATOR;
    int denominator = DEFAULT_DENOMINATOR;
};

enum MenuOption {
    INVALID,
    DEMO_ZERO_DENOMINATOR,
    DEMO_ZERO_NUMERATOR,
    DEMO_NEGATIVE,
    DEMO_IMPROPER_MIXED,
    DEMO_CONSTRUCTOR_AND_COUNT,
    QUIT
};

void displayMenu();
MenuOption getMenuChoice();
void printObjectCount(const string& label);
void demoZeroDenominator();
void demoZeroNumerator();
void demoNegative();
void demoImproperMixed();
void demoConstructorAndCount();
void quitMenuOption();
void invalidMenuOption();

int main() {
    bool isDone = false;
    do {
        displayMenu();
        MenuOption userChoice = getMenuChoice();
        switch (userChoice) {
            case DEMO_ZERO_DENOMINATOR:
                demoZeroDenominator();
                break;
            case DEMO_ZERO_NUMERATOR:
                demoZeroNumerator();
                break;
            case DEMO_NEGATIVE:
                demoNegative();
                break;
            case DEMO_IMPROPER_MIXED:
                demoImproperMixed();
                break;
            case DEMO_CONSTRUCTOR_AND_COUNT:
                demoConstructorAndCount();
                break;
            case QUIT:
                quitMenuOption();
                isDone = true;
                break;
            default:
                invalidMenuOption();
                break;
        }
    } while (!isDone);
    return 0;
}

// ---------- static member definition ----------
int Fraction::objectCount = 0;

// ---------- FractionException member functions ----------
FractionException::FractionException() {
    message = ERR_UNKNOWN;
}

FractionException::FractionException(const string& errorMessage) {
    message = errorMessage;
}

string FractionException::getMessage() const {
    return message;
}

// ---------- Fraction member functions ----------
Fraction::Fraction() {
    setFraction(0, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
    objectCount++;
}

Fraction::Fraction(const Fraction& other) {
    setFraction(0, other.numerator, other.denominator);
    objectCount++;
}

Fraction::Fraction(int newNumerator) {
    try {
        setFraction(0, newNumerator, DEFAULT_DENOMINATOR);
    } catch (const FractionException& error) {
        cout << error.getMessage() << " The fraction was set to default values." << endl;
        setFraction(0, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
    }
    objectCount++;
}

Fraction::Fraction(int newNumerator, int newDenominator) {
    try {
        setFraction(0, newNumerator, newDenominator);
    } catch (const FractionException& error) {
        cout << error.getMessage() << " The fraction was set to default values." << endl;
        setFraction(0, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
    }
    objectCount++;
}

Fraction::Fraction(int newWhole, int newNumerator, int newDenominator) {
    try {
        setFraction(newWhole, newNumerator, newDenominator);
    } catch (const FractionException& error) {
        cout << error.getMessage() << " The fraction was set to default values." << endl;
        setFraction(0, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
    }
    objectCount++;
}

Fraction::~Fraction() {
    numerator = 0;
    denominator = 1;
    objectCount--;
}

void Fraction::setNumerator(int newNumerator) {
    setFraction(0, newNumerator, denominator);
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
    cout << toString() << endl;
}

int Fraction::getCount() {
    return objectCount;
}

// ---------- free functions ----------
void displayMenu() {
    cout << endl;
    cout << "===== Fraction Class Test Menu =====" << endl;
    cout << "1. Demo: setting the denominator to zero" << endl;
    cout << "2. Demo: setting the numerator to zero" << endl;
    cout << "3. Demo: setting a negative value" << endl;
    cout << "4. Demo: invalid mixed number (numerator > denominator with a whole part)" << endl;
    cout << "5. Demo: constructor failure, copy constructor, and object count" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter your choice: ";
}

MenuOption getMenuChoice() {
    int userInput = 0;
    cin >> userInput;
    if (cin.fail()) {
        cin.clear();
        userInput = 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int validatedInput =
        (userInput >= DEMO_ZERO_DENOMINATOR && userInput <= QUIT) ? userInput : INVALID;
    MenuOption menuChoice = static_cast<MenuOption>(validatedInput);
    return menuChoice;
}

void printObjectCount(const string& label) {
    cout << "Fraction objects currently in memory (" << label << "): " << Fraction::getCount()
         << endl;
}

void demoZeroDenominator() {
    cout << endl;
    cout << "--- Demo: setting the denominator to zero ---" << endl;
    printObjectCount("before demo");
    {
        Fraction testFraction(2, 3);
        cout << "Starting fraction: ";
        testFraction.print();
        printObjectCount("during demo");
        cout << "Attempting testFraction.setDenominator(0)..." << endl;
        try {
            testFraction.setDenominator(0);
        } catch (const FractionException& error) {
            cout << "Exception caught: " << error.getMessage() << endl;
        } catch (...) {
            cout << "Exception caught: " << ERR_UNKNOWN << endl;
        }
        cout << "Fraction after the failed attempt (unchanged): ";
        testFraction.print();
    }
    printObjectCount("after demo");
}

void demoZeroNumerator() {
    cout << endl;
    cout << "--- Demo: setting the numerator to zero ---" << endl;
    printObjectCount("before demo");
    {
        Fraction testFraction(3, 4);
        cout << "Starting fraction: ";
        testFraction.print();
        printObjectCount("during demo");
        cout << "Attempting testFraction.setNumerator(0)..." << endl;
        try {
            testFraction.setNumerator(0);
        } catch (const FractionException& error) {
            cout << "Exception caught: " << error.getMessage() << endl;
        } catch (...) {
            cout << "Exception caught: " << ERR_UNKNOWN << endl;
        }
        cout << "Fraction after the failed attempt (unchanged): ";
        testFraction.print();
    }
    printObjectCount("after demo");
}

void demoNegative() {
    cout << endl;
    cout << "--- Demo: setting a negative value ---" << endl;
    printObjectCount("before demo");
    {
        Fraction testFraction(1, 2);
        cout << "Starting fraction: ";
        testFraction.print();
        printObjectCount("during demo");
        cout << "Attempting testFraction.setFraction(3, -4)..." << endl;
        try {
            testFraction.setFraction(3, -4);
        } catch (const FractionException& error) {
            cout << "Exception caught: " << error.getMessage() << endl;
        } catch (...) {
            cout << "Exception caught: " << ERR_UNKNOWN << endl;
        }
        cout << "Fraction after the failed attempt (unchanged): ";
        testFraction.print();
    }
    printObjectCount("after demo");
}

void demoImproperMixed() {
    cout << endl;
    cout << "--- Demo: invalid mixed number ---" << endl;
    printObjectCount("before demo");
    {
        Fraction testFraction(2, 3, 4);
        cout << "Starting fraction: ";
        testFraction.print();
        printObjectCount("during demo");
        cout << "Attempting testFraction.setFraction(5, 7, 3)..." << endl;
        try {
            testFraction.setFraction(5, 7, 3);
        } catch (const FractionException& error) {
            cout << "Exception caught: " << error.getMessage() << endl;
        } catch (...) {
            cout << "Exception caught: " << ERR_UNKNOWN << endl;
        }
        cout << "Fraction after the failed attempt (unchanged): ";
        testFraction.print();
    }
    printObjectCount("after demo");
}

void demoConstructorAndCount() {
    cout << endl;
    cout << "--- Demo: constructor failure, copy constructor, and object count ---" << endl;
    printObjectCount("before demo");
    {
        cout << "Attempting Fraction badFraction(-3, 6, 7)..." << endl;
        Fraction badFraction(-3, 6, 7);
        cout << "badFraction after construction: ";
        badFraction.print();
        cout << "Creating goodFraction(2, 3, 4)..." << endl;
        Fraction goodFraction(2, 3, 4);
        cout << "goodFraction: ";
        goodFraction.print();
        cout << "Creating copyFraction as a copy of goodFraction..." << endl;
        Fraction copyFraction(goodFraction);
        cout << "copyFraction: ";
        copyFraction.print();
        printObjectCount("during demo, three objects alive");
    }
    printObjectCount("after demo, destructors have run");
}

void quitMenuOption() {
    cout << endl;
    cout << "Goodbye!" << endl;
}

void invalidMenuOption() {
    cout << endl;
    cout << "Invalid menu choice. Please enter a number between 1 and 6." << endl;
}

/*Output
aidentsang@Aidens-MacBook-Pro src % "/Users/aidentsang/Pierce college Labs C++/CS216_L3_AT/build/main"

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 1

--- Demo: setting the denominator to zero ---
Fraction objects currently in memory (before demo): 0
Starting fraction: 2/3
Fraction objects currently in memory (during demo): 1
Attempting testFraction.setDenominator(0)...
Exception caught: Denominator cannot be zero (division by zero is undefined).
Fraction after the failed attempt (unchanged): 2/3
Fraction objects currently in memory (after demo): 0

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 2

--- Demo: setting the numerator to zero ---
Fraction objects currently in memory (before demo): 0
Starting fraction: 3/4
Fraction objects currently in memory (during demo): 1
Attempting testFraction.setNumerator(0)...
Exception caught: Numerator cannot be zero (0/n is not a legal fraction).
Fraction after the failed attempt (unchanged): 3/4
Fraction objects currently in memory (after demo): 0

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 3

--- Demo: setting a negative value ---
Fraction objects currently in memory (before demo): 0
Starting fraction: 1/2
Fraction objects currently in memory (during demo): 1
Attempting testFraction.setFraction(3, -4)...
Exception caught: Whole, numerator, and denominator must not be negative (only positive fractions are allowed).
Fraction after the failed attempt (unchanged): 1/2
Fraction objects currently in memory (after demo): 0

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 4

--- Demo: invalid mixed number ---
Fraction objects currently in memory (before demo): 0
Starting fraction: 2 3/4
Fraction objects currently in memory (during demo): 1
Attempting testFraction.setFraction(5, 7, 3)...
Exception caught: Numerator cannot be greater than the denominator when the whole part is greater than zero (e.g., 5 7/3 is not a legal fraction).
Fraction after the failed attempt (unchanged): 2 3/4
Fraction objects currently in memory (after demo): 0

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 5

--- Demo: constructor failure, copy constructor, and object count ---
Fraction objects currently in memory (before demo): 0
Attempting Fraction badFraction(-3, 6, 7)...
Whole, numerator, and denominator must not be negative (only positive fractions are allowed). The fraction was set to default values.
badFraction after construction: 1
Creating goodFraction(2, 3, 4)...
goodFraction: 2 3/4
Creating copyFraction as a copy of goodFraction...
copyFraction: 2 3/4
Fraction objects currently in memory (during demo, three objects alive): 3
Fraction objects currently in memory (after demo, destructors have run): 0

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 0

Invalid menu choice. Please enter a number between 1 and 6.

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 10

Invalid menu choice. Please enter a number between 1 and 6.

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: !a

Invalid menu choice. Please enter a number between 1 and 6.

===== Fraction Class Test Menu =====
1. Demo: setting the denominator to zero
2. Demo: setting the numerator to zero
3. Demo: setting a negative value
4. Demo: invalid mixed number (numerator > denominator with a whole part)
5. Demo: constructor failure, copy constructor, and object count
6. Quit
Enter your choice: 6

Goodbye!
aidentsang@Aidens-MacBook-Pro src % */

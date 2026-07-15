**NG 7/14/2026**
* ** To provide you with thorough feedback, I read your code line by line, sometimes multiple times**. Jumping from file to file is too time-consuming. Unless noted otherwise, place your class definitions above the main() and all function definitions below main(), all in one file. While the industry standard involves multi-source file programs, we will use a single file format for these labs unless instructed otherwise. Submit a fully completed lab by th due date using the correct GitHub invite link to get a second chance
* **feedback.md is for instructor use only**: please DO NOT change the feedback.md; make a copy if needed; do not add anything; if you do not understand  the feedback, let me know asap (mymail.laccd.edu, grigorn@laccd.edu)
* if any, items with (-X) - no deductions this time, serve as a warning; please ensure these errors are corrected, as repeating them in future assignments will result in X points being deducted
* in feedback, #N means line number, e.g., 
```text
* #25  global var(s); only constant may be global -10
meaning: see line #25 ; -10 deduction points for the mistake
```
* **class definition style & standards**:  first, member vars  one per line and do not forget to initialize them; although private is a default access specifier, still label private members  clearly for better readability; second- functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions, except for static function,  should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary;  to promote strong exception guarantee and to reduce redundancy, all setter functions, including c’tors, must call a setter function that sets all member variables
* **strong exception guarantee**: this guarantee acts as a transaction. If the operation successfully completes, all changes take effect; if it fails mid-execution, all partial changes are completely undone. If incoming values are invalid, do not change member variables; provided all member variables have been initialized to a valid state in the class definition and c’tors, the object will always be valid
* **there is no such thing as a partially valid record or set of related data** (let's say, a Creature record in an input file). If any required field (e.g., health, strength) in a record is invalid, then the entire record must be considered invalid. As a developer, your responsibility is to validate the input, not to "fix" it by replacing invalid values with defaults. Doing so changes the user's data and assumes you know what they intended to enter. In general, you should not guess what the user meant or silently modify invalid input. Instead, detect the invalid record and handle it according to the program's requirements (for example, by rejecting it or reporting an error). 
* in this class, **classes must completely manage their own failures**; classes must catch and handle internal errors locally to maintain safe, fully encapsulated invariants. In other words, classes must maintain encapsulation by catching and handling internal exceptions locally. According to the C++ Core Guidelines, an object should achieve the no-fail or strong exception guarantee by rolling back state or swallowing expected failures internally so callers aren't burdened with cleanup.
* 245 redundant; invalid menu choice should be handled by default case of the menu switch; create a highly reusable function that takes an error message string as a parameter, clears the failed input, and outputs the error message to be called in the default case of the menu switch -5
```text
do {
switch (sortChoice) {
            case SORT_NAME:
            case SORT_HEALTH:
                sortMenu(names, types, health, strength, numCreatures, sortChoice);
                break;
            case BACK:
		//message about going back to the previous menu
                break;
            default:
                clearCin("Invalid menu choice");
        }
}while (sortChoice!=QUIT) 
```

 * listing member variables first and member functions second is a widely used convention because it makes classes easier to read, understand, and maintain; member variables define what the object is (its state), in other words, they tell you what this class is about; once you understand what the class is about and the data the object stores, the member functions, on the other hand, operate on member variable(s)  and it is hard to understand the function without understanding what it operates on  -2
* #82 unnecessary variable = unnecessary computational + “human” expense; e.g. int menuChoice; e.g., while(menuChoice!=QUIT) {//code} -2
* menu should have only two options: demo and quit  -5
* readability, comments; do not state the obvious, do not reiterate/duplicate the code,  AI and the textbooks reiterate/duplicate the code because they try to teach something, as a way of explanation; remove outdated code- it is disrespectful to leave outdated/commented out code; comments are supposed to help understand the code and not create unnecessary clutter; comments should be to the right of the statement whenever possible, not above => those who need to read them – will find them and read, those who do not will go to the next line; "Code never lies, comments sometimes do." - Ron Jeffries”; every C++ programmer knows how const, structs, function prototype looks like; what’s is the goal of excessive ____ and ****? what is the purpose of the comments as this(ese) one(s)? -2
```text
/ ---------- static member definition ----------
int Fraction::objectCount = 0;

// ---------- FractionException member functions ----------
FractionException::FractionException() {

```
* #126 common name is what() 
* why have so many try/catch blocks in the Fraction class, when you can have only one in setFraction with 3 args? -5
* *156 and like: unnecessary  in c’tor, member variables already been set to defaults in the class definition 
* #189 and like: what happens if newNumerator is invalid? setFraction with 3 args will throw an exception, and who is catching it? uncaught exceptions usually result in abrupt program termination; when a C++ function throws an exception that it doesn't catch, the exception propagates backward up the function call stack, the program searches for a matching catch block while automatically cleaning up local variables in a process called stack unwinding, if it reaches the top without being caught, the program abruptly terminates; to reduce the size of exe file and other computational expenses, and to provide a strong exception guarantee, setFraction() with 3 args  should throw and catch exceptions; see assignment;  – 10
* #234-242 and like: excessive use of cout/cin/ file stream/and/or endl and/or << >> results in unnecessary computational expense (time and space); applies to all output, not just menu; << and >> are not just symbols, they are  operators with functions “behind” them; calling an object ( cin, cout, infile, etc., is a computation expense  as well, menu options should be on separate lines in the source code and console; same applies when working with files -5
* << not needed between strings
* put ‘\n’ is at the end of the previous whenever possible
* Should print a couple of blank lines before the menu to separate from the lines of text above it * no need for the “.” at the end of menu options; it is just clutter, but no useful info to a user
*  e.g., input>>name>>id>gpa; 
```text
//e.g.
cout<<fixed<<showpoint<<setprecision(2); //needed once only unless they need to be changed

cout << "\n\nMenu:\n" //note \n\n before Menu – automatically creates separation
        "1. Encrypt\n" //not ‘\n’ at the end of the previous line for better readability
        "2. Decrypt\n"
```
* Splitting exception handling between the class (for example, Fraction) and its client (main()) is like keeping your forks in your own kitchen drawer while storing your knives in a neighbor’s car—and then depending on that neighbor, someone you barely know, who is rarely home and has absolutely no obligation to help you, to wash your dishes and provide clean knives whenever you need them, on a moment’s notice, at any hour of the day or night.  What are the chances your neighbor will deliver on time every time? I find it unacceptable loss of control. In software design, do not hand over responsibility for protecting your own data and enforcing your own rules to code that does not fully understand the object’s internal state. The class that owns the data should own the responsibility of validating it and handling the errors related to it.
 Keep exception handling close to the code that has the knowledge, context, and authority to manage the problem correctly. Good design means keeping control where it belongs, minimizing unnecessary dependencies, and preventing your code from becoming dependent on external components to maintain its own correctness
* resubmit by cut-off


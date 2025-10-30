// includes needed modules
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// class to store a float as a string
// Author: Evan Baumgartner
class stringNum
{
private:
    // method to add two stringNums, used if both stringNums have the same sign
    stringNum add(stringNum otherNum)
    {
        stringNum returnNum; // declares a stringNum to be returned

        // balances integer string lengths
        while (integer.length() < otherNum.integer.length()) // loops while integer string length is less than other integer string length
            integer = '0' + integer; // adds a leading 0 to integer string length
        while (integer.length() > otherNum.integer.length()) // loops while other integer string length is less than integer string length
            otherNum.integer = '0' + otherNum.integer; // adds a leading 0 to other integer string length

        // balances decimal string lengths
        while (decimal.length() < otherNum.decimal.length()) // loops while decimal string length is less than other decimal string length
            decimal = decimal + '0'; // adds a trailing 0 to integer string length
        while (decimal.length() > otherNum.decimal.length())  // loops while other decimal string length is less than decimal string length
            otherNum.decimal = otherNum.decimal + '0'; // adds a trailing 0 to other decimal string length

        string newDec; // declares variable for new decimal value
        string newInt; // declares variable for new integer value

        bool carryOver = false; // boolean to track carry over
        for (int i = decimal.length() - 1; i >= 0; i--) // iterates across decimal values
        {
            int added = (decimal[i] - '0') + (otherNum.decimal[i] - '0'); // gets value of addition of the two cast characters for the given positon
            
            if (carryOver) // checks if there's a carry over
            {
                added++; // adds one to addition
                carryOver = false; // resets carry over
            }

            if (added > 9) // checks if the sum is greater than 9 (needs a carry over)
            {
                carryOver = true; // sets carry over to true
                added -= 10; // gets ones place of addition
            }

            char newNum = added + '0'; // casts addition to character
            newDec = newNum + newDec; // adds addition character to new decimal
        }

        for (int i = integer.length() - 1; i >= 0; i--) // iterates across integer
        {
            int added = (integer[i] - '0') + (otherNum.integer[i] - '0'); // gets value of addition of the two cast characters for the given positon
            
            if (carryOver) // checks if there's a carry over
            {
                added++; // adds one to addition
                carryOver = false; // resets carry over
            }

            if (added > 9) // checks if the sum is greater than 9 (needs a carry over)
            {
                carryOver = true; // sets carry over to true
                added -= 10; // gets ones place of addition
            }

            char newNum = added + '0'; // casts addition to character
            newInt = newNum + newInt; // adds addition character to new integer
        }

        if (carryOver) // checks if a carry over is left over
            newInt = '1' + newInt; //adds trailing 1 to integer

        // sets values of returnNum
        returnNum.integer = newInt;
        returnNum.decimal = newDec;
        returnNum.negative = negative; // sets sign of number to current sign

        return returnNum; // returns filled in returnNum
    }

    // method to add two stringNums, used if stringNums have opposite signs
    stringNum subtract(stringNum otherNum)
    {
        stringNum returnNum; // declares a stringNum to be returned

        // balances integer string lengths
        while (integer.length() < otherNum.integer.length()) // loops while integer string length is less than other integer string length
            integer = '0' + integer; // adds a leading 0 to integer string length
        while (integer.length() > otherNum.integer.length()) // loops while other integer string length is less than integer string length
            otherNum.integer = '0' + otherNum.integer; // adds a leading 0 to other integer string length

        // balances decimal string lengths
        while (decimal.length() < otherNum.decimal.length()) // loops while decimal string length is less than other decimal string length
            decimal = decimal + '0'; // adds a trailing 0 to integer string length
        while (decimal.length() > otherNum.decimal.length())  // loops while other decimal string length is less than decimal string length
            otherNum.decimal = otherNum.decimal + '0'; // adds a trailing 0 to other decimal string length

        string newDec; // declares variable for new decimal value
        string newInt; // declares variable for new integer value

        bool borrow = false; // boolean to track if a borrow has occured in previous subtraction
        for (int i = decimal.length() - 1; i >= 0; i--) // iterates across decimal values
        {

            int subtracted = (decimal[i] - '0') - (otherNum.decimal[i] - '0'); // gets value of subtraction of the two cast characters for the given positon
            
            if (borrow) // checks if a borrow has occured in previus subtractions
            {
                subtracted--; // decreases subtracted value by 1
                borrow = false; // resets borrow
            }

            if (subtracted < 0) // checks if the subtracted value is negative (needs a borrow)
            {
                borrow = true; // setsborrow for next subtraction
                subtracted = 10 + subtracted; // adds 10 to get new value after borrowing
            }

            char newNum = subtracted + '0'; // casts subtracted number to character
            newDec = newNum + newDec; // adds subtracted value to decimal
        }

        for (int i = integer.length() - 1; i >= 0; i--) // iterates across integer values
        {
            int subtracted = (integer[i] - '0') - (otherNum.integer[i] - '0');// gets value of subtraction of the two cast characters for the given positon
            
            if (borrow) // checks if a borrow has occured in previus subtractions
            {
                subtracted--; // decreases subtracted value by 1
                borrow = false; // resets borrow
            }

            if (subtracted < 0) // checks if the subtracted value is negative (needs a borrow)
            {
                borrow = true; // setsborrow for next subtraction
                subtracted = 10 + subtracted; // adds 10 to get new value after borrowing
            }

            char newNum = subtracted + '0'; // casts subtracted number to character
            newInt = newNum + newInt; // adds subtracted value to integer
        }

        // sets values of returnNum
        returnNum.integer = newInt;
        returnNum.decimal = newDec;
        returnNum.negative = negative; // sets sign of number to current sign

        return returnNum; // returns filled in returnNum
    }

public:
    string integer; // stores integer values as a string (everything before the decimal)
    string decimal; // stores decimal values as a string (everything after the decimal)
    bool negative = false; // boolean storing if the number is negative

    // method to check if values in the number are valid
    bool validateNum()
    {
        if (integer.empty()) // returns false if integer is empty
            return false;

        for (auto val : integer) // iterates across the integer
        {
            if (!isdigit(val)) // returns false if the value is not a digit
                return false;
        }

        for (auto val : decimal) // iterates across decimal
        {
            if (!isdigit(val)) // returns false if the value is not a digit
                return false;
        }

        return true;
    }

    // method to add stringNum with another input stringNum
    stringNum addNum(stringNum otherNum)
    {
        formatNum(); // formats stringNum for proper addition
        otherNum.formatNum(); // formats other stringNum for proper addition

        if (negative == otherNum.negative) // checks if numbers are of the same sign
        {
            return add(otherNum); // adds two numbers
        }
        else // if numbers are opposite signs
        {
            if (absGTE(otherNum)) // checks if current stringNum is greater than or equal to other stringNum
            {
                return subtract(otherNum); // returns subtraction of stringNums
            }
            else
            {
                return otherNum.add(*this); // if other stringNum is greater, uses other stringNum's addition to properly perform subtraction
            }
        }
    }

    // method to format the stringNum for printing and comparison
    void formatNum()
    {
        int firstNot0 = integer.find_first_not_of('0'); // finds first value in interger that isn't 0
        (firstNot0 == string::npos) ? integer = '0' : integer = integer.substr(firstNot0); // if it is only zeros or empty integer is 0, else it sets integer to the number past initial zeros

        int lastNot0 = decimal.find_last_not_of('0'); // finds last value in decimal that is not 0
        (lastNot0 == string::npos) ? decimal = "0" : decimal.substr(0, lastNot0 + 1);  // if it is only zeros or empty integer is 0, else it sets decimal to the number before trail zeros

        if (integer == "0" && decimal == "0") // sets negative to false if integer and decimal are 0
        {
            negative = false;
        };

        return;
    }

    // method to check if the absolute value of a stringNum is greater than the absolute value of another input stringNum
    bool absGTE(stringNum otherNum)
    {
        formatNum(); // formats stringNum for proper comparison
        otherNum.formatNum(); // formats other stringNum for proper comparison
        if (integer.length() != otherNum.integer.length()) // checks if the integer lengths are different
            return (integer.length() > otherNum.integer.length()) ? true : false; // returns true if the integer is longer than the other
        if (integer != otherNum.integer) // checks if the integers are not equal
            return (integer > otherNum.integer) ? true : false; // returns true if integer value is larger (string comparison)
        if (decimal != otherNum.decimal) // checks if the decimals are not equal
            return (decimal > otherNum.decimal) ? true : false; // returns true if the decimal calue is larger (string comparison)
        return true; // returns true if values are equal
    }

    // method to print the number of a StringNum
    void printNum()
    {
        formatNum(); // formats the number for proper output
        string sign; // declares a string variable for the sign
        (negative) ? sign = '-' : sign = ""; // sets sign to '-' if the number is negative or en empty string if it's positive

        if (decimal.empty() || decimal == "0") // checks if the decimal is empty or equals 0
        {
            cout << sign << integer << endl; // prints sign and integer value
        }
        else // decimal is not 0
        {
            cout << sign << integer << "." << decimal << endl; // prints sign, integer, and decimal with '.' between
        }
    }
};

// function to take in a single line and format it into a stringNum, valid strings are of the form (+/-)A.(B)
// if strings have a decimal but no numbers after it the decimal is set to 'X' to induce an invalid number
// Author: Evan Baumgartner
stringNum parseNum(string line)
{
    string formatLine = line; // makes a formatLine variable to filter out +/-

    stringNum returnNum; // makes a returnNum stringNum structure to be returned

    if (formatLine[0] == '-') // checks if the first character is '-'
    {
        returnNum.negative = true; // makes returnNum negative
        formatLine = formatLine.substr(1); // gets rid of '-' in formatLine
    }
    else if (formatLine[0] == '+') // checks if the first character is '+'
    {
        formatLine = formatLine.substr(1); // gets rid of '+' in formatLine (default of stringNum is positive)
    }

    int decPos = formatLine.find('.'); // finds position of the first decimal if there is one
    
    if (decPos == string::npos) // checks if there was not decimal (find returned an end position instead of a number)
    {
        returnNum.integer = formatLine; // sets the integer to formatLine because there is no decimal
    }
    else
    {
        // checks if the character after the decimal position is the end of the line or 
        // if there's no character before the decimal (invalid)
        if (formatLine[decPos + 1] == string::npos || decPos == 0) 
        {
            returnNum.decimal = 'X'; // sets decimal to 'X' to induce invalid string
        }
        else
        {
            returnNum.integer = formatLine.substr(0, decPos); // sets integer to string before decimal
            returnNum.decimal = formatLine.substr(decPos + 1); // sets decimal to string after decimal
        }
    }

    return returnNum;
}

// function to take in a string and turn it into numbers then adding them, strings are generally of the form (+/-)A.(B) (+/-)C.(D)
// Author: Evan Baumgartner
void parseLine(string line)
{
    int spacePos = line.find(' '); // gets the position of the first space in the line
    if (spacePos == string::npos) // checks if there is no space
    {
        cout << "Invalid formatting" << endl; // statement if there is no space
        return;
    }
    string num1 = line.substr(0, spacePos); // gets everything before the space
    string num2 = line.substr(spacePos + 1); // gets everything after the space

    stringNum stringNum1 = parseNum(num1); // gets stringNum based on items before space
    stringNum stringNum2 = parseNum(num2); // gets stringNum based on items after space

    stringNum newNum; // creates a new stringNum for addition

    if (stringNum1.validateNum() && stringNum2.validateNum()) // checks if both stringNums are valid
    {
        newNum = stringNum1.addNum(stringNum2); // sets newNum to the addition of both stringNums
    }
    else
    {
        cout << "Invalid formatting" << endl; // statement if either number is invalid
        return;
    }

    newNum.printNum(); // prints added number

    return;
}

int main()
{
    string fileName; // creates a string for the file name

    cout << "Input file name: "; // prompt for file name
    cin >> fileName;             // gets file name
    cout << endl;

    ifstream stringFile(fileName); // gets file stream
    string line;                   // creates a line to read each line of the file

    if (stringFile.is_open()) // checks is the file can be opened or is available
    {
        while (getline(stringFile, line)) // loops across lines of the file
        {
            if (!line.empty()) // checks if the line is not empty
                parseLine(line); // calls parseLine to get numbers and print addition
        }
    }
    else
    {
        cout << "File unable to be opened" << endl; // statement if file can't be opened
    }

    return 0;
}
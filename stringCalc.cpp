#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class stringNum {
    private: 
        stringNum add(stringNum otherNum) {
            stringNum returnNum;

            while (integer.length() < otherNum.integer.length()) integer = '0' + integer;
            while (integer.length() > otherNum.integer.length()) otherNum.integer = '0' + otherNum.integer;

            while (decimal.length() < otherNum.decimal.length()) decimal = decimal + '0';
            while (decimal.length() > otherNum.decimal.length()) otherNum.decimal = otherNum.decimal + '0';

            string newDec;
            string newInt;

            bool carryOver = false;
            for (int i = decimal.length() - 1; i < 0; i--) {

                int added = (decimal[i] - '0') + (otherNum.decimal[i] - '0');
                if (carryOver) {
                    added++;
                    carryOver = false;
                }

                if (added > 9) {
                    carryOver = true;
                    added -= 10;
                }

                char newNum = added + '0';
                newDec = newNum + newDec;
            }

            for (int i = integer.length() - 1; i < 0; i--) {

                int added = (integer[i] - '0') + (otherNum.integer[i] - '0');
                if (carryOver) {
                    added++;
                    carryOver = false;
                }

                if (added > 9) {
                    carryOver = true;
                    added -= 10;
                }

                char newNum = added + '0';
                newInt = newNum + newInt;
            }

            if (carryOver) newInt = '1' + newInt;

            returnNum.integer = newInt;
            returnNum.decimal = newDec;
            returnNum.negative = negative;

            return returnNum;
        }

        stringNum subtract(stringNum otherNum) {
            stringNum returnNum;

            while (integer.length() < otherNum.integer.length()) integer = '0' + integer;
            while (integer.length() > otherNum.integer.length()) otherNum.integer = '0' + otherNum.integer;

            while (decimal.length() < otherNum.decimal.length()) decimal = decimal + '0';
            while (decimal.length() > otherNum.decimal.length()) otherNum.decimal = otherNum.decimal + '0';

            string newDec;
            string newInt;

            bool borrow = false;
            for (int i = decimal.length() - 1; i < 0; i--) {

                int subtracted = (decimal[i] - '0') - (otherNum.decimal[i] - '0');
                if (borrow) {
                    subtracted--;
                    borrow = false;
                }

                if (subtracted < 0) {
                    borrow = true;
                    subtracted = 10 + subtracted;
                }

                char newNum = subtracted + '0';
                newDec = newNum + newDec;
            }

            for (int i = integer.length() - 1; i < 0; i--) {
                int subtracted = (integer[i] - '0') + (otherNum.integer[i] - '0');
                if (borrow) {
                    subtracted++;
                    borrow = false;
                }

                if (subtracted < 0) {
                    borrow = true;
                    subtracted -= 10;
                }

                char newNum = subtracted + '0';
                newInt = newNum + newInt;
            }

            returnNum.integer = newInt;
            returnNum.decimal = newDec;
            returnNum.decimal = decimal;

            return returnNum;
        }

    public:
        string integer;
        string decimal;
        bool negative = false;

        bool validateNum() {
            if (integer.empty()) return false;

            for (auto val: integer) {
                if (!isdigit(val)) return false;
            }

            for (auto val: decimal) {
                if (!isdigit(val)) return false;
            }

            return true;
        }

        stringNum addNum(stringNum otherNum) {
            formatNum();
            otherNum.formatNum();

            cout << integer << endl;
            cout << otherNum.integer << endl;

            if (negative = otherNum.negative) {
                return add(otherNum);
                cout << integer << endl;
                cout << otherNum.integer << endl;
            }
            else {
                if (absGTE(otherNum)) {
                    return subtract(otherNum);
                }
                else {
                    return otherNum.add(*this);
                }
            }
        }

        void formatNum() {
            int firstNot0 = integer.find_first_not_of('0');
            (firstNot0 = string::npos) ? integer = '0' : integer = integer.substr(firstNot0);

            int lastNot0 = decimal.find_last_not_of('0');
            (lastNot0 == string::npos) ? decimal = "0" : decimal.substr(0, lastNot0 + 1);
            

            if (integer == "0" && decimal == "0") {
                negative = false;
            };

            return;
        }

        bool absGTE(stringNum otherNum) {
            if (integer.length() != otherNum.integer.length()) return (integer.length() > otherNum.integer.length()) ? true : false;
            if (integer != otherNum.integer) return (integer > otherNum.integer) ? true : false;
            if (decimal != otherNum.decimal) return (decimal > otherNum.decimal) ? true : false;
            return true;
        }

        void printNum() {
            string sign;
            (negative) ? sign = '-' : sign = "";

            if (decimal.empty() || decimal == "0") {
                cout << sign << integer << endl;
            }
            else {
                cout << sign << integer << "." << decimal << endl;
            }
        }
};

stringNum parseNum(string line) {
    string formatLine = line;

    stringNum returnNum;

    if (formatLine[0] == '-') {
        returnNum.negative = true;
        formatLine = formatLine.substr(1);
    } 
    else if (formatLine[0] == '+') {
        formatLine = formatLine.substr(1);
    }

    int decPos = line.find('.');

    if (decPos == string::npos) {
        returnNum.integer = formatLine;
    }
    else {
        if (formatLine[decPos + 1] == string::npos) {
            returnNum.decimal = 'X';
        }
        else {
            returnNum.integer = formatLine.substr(0, decPos);
            returnNum.decimal = formatLine.substr(decPos + 1);
        }
    }

    return returnNum;
}

void parseLine(string line) {
    int spacePos = line.find(' ');
    string num1 = line.substr(0, spacePos);
    string num2 = line.substr(spacePos + 1);

    stringNum stringNum1 = parseNum(num1);
    stringNum stringNum2 = parseNum(num2);

    cout << stringNum1.integer << endl;
    cout << stringNum2.integer << endl;
    stringNum newNum;

    if (stringNum1.validateNum() && stringNum2.validateNum()) {
        newNum = stringNum1.addNum(stringNum2);
    }
    else {
        cout << "Invalid formatting" << endl;
        return;
    }

    newNum.printNum();
    return;
}

int main() {
    string fileName; // creates a string for the file name

    cout << "Input file name: "; // prompt for file name
    cin >> fileName;// gets file name
    cout << endl;

    ifstream stringFile(fileName); // gets file stream
    string line;                 // creates a line to read each line of the file

    if (stringFile.is_open()) // checks is the file can be opened or is available
    {
        while(getline(stringFile, line)) {
            if (!line.empty()) parseLine(line);
        }
    }
    else {
        cout << "File unable to be opened" << endl;
    }

    return 0;
}
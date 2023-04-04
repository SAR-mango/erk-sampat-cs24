#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: ./caprot num_to_rotate" << endl;
        return 1;
    }

    string inputString = "";
    getline(cin, inputString);
    const long stringLength = inputString.length();
    long shiftNum = stoi(argv[1]) % stringLength;
    long i = 0;
    vector<long> capitalIndexes;
    long vectorSize = 0;

    for (i = 0; i < stringLength; i++) {
        if (isupper(inputString[i])) {
            capitalIndexes.push_back(i);
            inputString[i] = tolower(inputString[i]);
            vectorSize++;
        }
    }

    for (i = 0; i < vectorSize; i++) {
        if (capitalIndexes.at(i) + shiftNum < 0) {
            inputString[stringLength + capitalIndexes.at(i) + shiftNum] = toupper(inputString[stringLength + capitalIndexes.at(i) + shiftNum]);
        }
        else if (capitalIndexes.at(i) + shiftNum >= stringLength) {
            inputString[capitalIndexes.at(i) + shiftNum - stringLength] = toupper(inputString[capitalIndexes.at(i) + shiftNum - stringLength]);
        }
        else {
            inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
        }
    }

    /*if (shiftNum >= 0) {
        for (i = 0; i < vectorSize; i++) {
            if (capitalIndexes.at(i) + shiftNum >= stringLength) {
                inputString[(capitalIndexes.at(i) + shiftNum) % stringLength] 
                = toupper(inputString[(capitalIndexes.at(i) + shiftNum) % stringLength]);
            }
            else {
                inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
            }
        }
    }
    else {
        if (abs(shiftNum) <= stringLength) {
            for (i = 0; i < vectorSize; i++) {
                if (capitalIndexes.at(i) + shiftNum < 0) {
                    inputString[stringLength + (capitalIndexes.at(i) + shiftNum) % stringLength] 
                    = toupper(inputString[stringLength + (capitalIndexes.at(i) + shiftNum) % stringLength]);
                }
                else {
                    inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
                }
            }
        }
        else {
            for (i = 0; i < vectorSize; i++) {
                if (capitalIndexes.at(i) + shiftNum < 0) {
                    inputString[capitalIndexes.at(i) + stringLength + (shiftNum % stringLength) - 2] 
                    = toupper(inputString[capitalIndexes.at(i) + stringLength + (shiftNum % stringLength) - 2]);
                }
                else {
                    inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
                }
            }
        }
    }*/

    cout << inputString << endl;
    return 0;
}

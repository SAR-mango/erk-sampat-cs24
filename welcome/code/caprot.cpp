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
    const long shiftNum = long(stoi(argv[1]));
    long i = 0;
    vector<long> capitalIndexes;
    getline(cin, inputString);
    const long stringLength = long(inputString.length());
    long vectorSize = 0;

    for (i = 0; i < stringLength; i++) {
        if (isupper(inputString[i])) {
            capitalIndexes.push_back(i);
            inputString[i] = tolower(inputString[i]);
            vectorSize++;
        }
    }

    if (shiftNum >= 0) {
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
                inputString[capitalIndexes.at(i) + stringLength + (shiftNum % stringLength) - 2] 
                = toupper(inputString[capitalIndexes.at(i) + stringLength + (shiftNum % stringLength) - 2]);
            }
        }
    }

    cout << inputString << endl;
    return 0;
}

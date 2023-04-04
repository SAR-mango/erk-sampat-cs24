#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: ./caprot num_to_rotate" << endl;
        return 1;
    }

    string inputString = "";
    long shiftNum = stoi(argv[1]);
    unsigned long i = 0;
    vector<unsigned long> capitalIndexes;
    getline(cin, inputString);

    for (i = 0; i < inputString.length(); i++) {
        if (isupper(inputString[i])) {
            capitalIndexes.push_back(i);
            inputString[i] = tolower(inputString[i]);
        }
    }
    if (shiftNum >= 0) {
        for (i = 0; i < capitalIndexes.size(); i++) {
            if (capitalIndexes.at(i) + shiftNum >= inputString.length()) {
                inputString[(capitalIndexes.at(i) + shiftNum) % (inputString.length())] = toupper(inputString[(capitalIndexes.at(i) + shiftNum) % (inputString.length())]);
            }
            else {
                inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
            }
        }
    }
    else {
        for (i = 0; i < capitalIndexes.size(); i++) {
            if (long(capitalIndexes.at(i)) + shiftNum < 0) {
                inputString[inputString.length() - ((capitalIndexes.at(i) + shiftNum) % (inputString.length()))] = toupper(inputString[inputString.length() - ((capitalIndexes.at(i) + shiftNum) % (inputString.length()))]);
            }
            else {
                inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
            }
        }
    }

    cout << inputString << endl;
    return 0;
}

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
        }
    }
    for (i = 0; i < capitalIndexes.size(); i++) {
        inputString[capitalIndexes.at(i)] = tolower(inputString[capitalIndexes.at(i)]);
        /*if (capitalIndexes.at(i) + shiftNum >= inputString.length()) {
            inputString[capitalIndexes.at(i) + shiftNum - inputString.length() + 1] = toupper(inputString[capitalIndexes.at(i) + shiftNum - inputString.length() + 1]);
        }
        else {
            inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
        }*/
        inputString[(capitalIndexes.at(i) + shiftNum) % (inputString.length() - 1)] = toupper(inputString[(capitalIndexes.at(i) + shiftNum) % (inputString.length() - 1)]);
    }
    cout << inputString << endl;
    return 0;
}

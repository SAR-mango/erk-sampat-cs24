#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]) {
    string inputString = "";
    int shiftNum = stoi(argv[1]);
    vector<int> capitalIndexes;
    cin >> inputString;
    if (shiftNum < 0) {
        cout << inputString << endl;
        return 0;
    }
    for (int i = 0; i < inputString.length(); i++) {
        if (isupper(inputString[i])) {
            capitalIndexes.push_back(i);
        }
    }
    for (int i = 0; i < capitalIndexes.size(); i++) {
        inputString[capitalIndexes.at(i)] = tolower(inputString[capitalIndexes.at(i)]);
        if (capitalIndexes.at(i) + shiftNum >= inputString.length()) {
            inputString[capitalIndexes.at(i) + shiftNum - inputString.length() + 1] = toupper(inputString[capitalIndexes.at(i) + shiftNum - inputString.length() + 1]);
        }
        else {
            inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
        }
    }
    cout << inputString << endl;
    return 0;
}

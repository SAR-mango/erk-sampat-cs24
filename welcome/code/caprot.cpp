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
    int shiftNum = stoi(argv[1]);
    vector<int> capitalIndexes;
    getline(cin, inputString);
    if (shiftNum < 0) {
        cout << inputString << endl;
        return 0;
    }
    for (int i = 0; i < int(inputString.length()); i++) {
        if (isupper(inputString[i])) {
            capitalIndexes.push_back(i);
        }
    }
    for (int i = 0; i < int(capitalIndexes.size()); i++) {
        inputString[capitalIndexes.at(i)] = tolower(inputString[capitalIndexes.at(i)]);
        if (capitalIndexes.at(i) + shiftNum >= int(inputString.length())) {
            inputString[capitalIndexes.at(i) + shiftNum - inputString.length() + 1] = toupper(inputString[capitalIndexes.at(i) + shiftNum - inputString.length() + 1]);
        }
        else {
            inputString[capitalIndexes.at(i) + shiftNum] = toupper(inputString[capitalIndexes.at(i) + shiftNum]);
        }
    }
    cout << inputString << endl;
    return 0;
}

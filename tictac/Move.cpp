#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.

void error();
void print();

Move::Move(const std::string& input) {
    if (input.length() < 6) {
        error();
    }
    int index = 0;
    if (isdigit(input[index])) {
        int move_num = stoi(input[index]);
        if (1 <= move_num && move_num <= 9) {
            number = move_number;
        }
        else {
            error();
        }
    }
    else {
        error();
    }
    index++;
    while (isspace(input[index]) {
        index++;
    }
    if (index == 1) {
        error();
    }
    if (tolower(input[index]) == 'x' || tolower(input[index]) == 'o') {
        player = toupper(input[index]);
    }
    else {
        error();
    }
    index++;
    int temp_index = index;
    while (isspace(input[index]) {
        index++;
    }
    if (index == temp_index) {
        error();
    }
    if (tolower(input[index]) == 'a' || tolower(input[index]) == 'b' || tolower(input[index]) == 'c') {
        row = toupper(input[index]);
    }
    else {
        error();
    }
    index++;
    if (isdigit(input[index])) {
        int col = stoi(input[index]);
        if (col == 1 || col == 2 || col == 3) {
            column = col;
        }
        else {
            error();
        }
    }
    else {
        error();
    }
    if (index == input.length() - 1) {
        print();
    }
    index++;
    if (!isspace(input[index])) {
        error();
    }
    for (index++; index < input.length(); index++) {
        if (!(isspace(input[index]) || input[index] == '#')) {
            error();
        }
        if (input[index] == '#') {
            break;
        }
    }
    print();
}

void error() {
    std::cout << "Parse error." << std::endl;
    exit(1);
}

void print() {
    std::cout << number << ' ' << player << ' ' << row << column << std::endl;

std::ostream& operator << (std::ostream& stream, const Move& move) {

}

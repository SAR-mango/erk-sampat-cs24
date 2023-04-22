#include <iostream>
#include <string>
#include <cctype>
#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.

Move::Move(const std::string& input) {
    if (input.length() < 6) {
        error();
    }
    size_t index = 0;
    if (isdigit(input[index])) {
        int move_num = std::atoi(&input[index]);
        if (1 <= move_num && move_num <= 9) {
            number = move_num;
        }
        else {
            error();
        }
    }
    else {
        error();
    }
    index++;
    while (isspace(input[index])) {
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
    size_t temp_index = index;
    while (isspace(input[index])) {
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
        int col = std::atoi(&input[index]);
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
        //print();
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
    //print();
}
void Move::error() {
    std::cout << "Parse error." << std::endl;
    exit(1);
}
/*void Move::print() {
    std::cout << number << ' ' << player << ' ' << row << column << std::endl;
}*/

std::ostream& operator << (std::ostream& stream, const Move& move) {
    //std::cout << number << ' ' << player << ' ' << row << column << std::endl;
    std::cout << number << ' ' << player << ' ' << row << column <<;
}

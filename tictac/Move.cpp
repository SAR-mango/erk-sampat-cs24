#include <iostream>
#include <string>
#include <cctype>
#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.

Move::Move(const std::string& input) {
    if (input.length() < 6) {
        throw ParseError;
    }
    size_t index = 0;
    if (isdigit(input[index])) {
        int move_num = std::atoi(&input[index]);
        if (1 <= move_num && move_num <= 9) {
            number = move_num;
        }
        else {
            throw std::invalid_argument("");
        }
    }
    else {
        throw std::invalid_argument("");
    }
    index++;
    while (isspace(input[index])) {
        index++;
    }
    if (index == 1) {
        throw std::invalid_argument("");
    }
    if (tolower(input[index]) == 'x' || tolower(input[index]) == 'o') {
        player = toupper(input[index]);
    }
    else {
        throw std::invalid_argument("");
    }
    index++;
    size_t temp_index = index;
    while (isspace(input[index])) {
        index++;
    }
    if (index == temp_index) {
        throw std::invalid_argument("");
    }
    if (tolower(input[index]) == 'a' || tolower(input[index]) == 'b' || tolower(input[index]) == 'c') {
        row = toupper(input[index]);
    }
    else {
        throw std::invalid_argument("");
    }
    index++;
    if (isdigit(input[index])) {
        int col = std::atoi(&input[index]);
        if (col == 1 || col == 2 || col == 3) {
            column = col;
        }
        else {
            throw std::invalid_argument("");
        }
    }
    else {
        throw std::invalid_argument("");
    }
    if (index == input.length() - 1) {
        //print();
    }
    index++;
    if (!isspace(input[index])) {
        throw std::invalid_argument("");
    }
    for (index++; index < input.length(); index++) {
        if (!(isspace(input[index]) || input[index] == '#')) {
            throw std::invalid_argument("");
        }
        if (input[index] == '#') {
            break;
        }
    }
    //print();
}

std::ostream& operator << (std::ostream& stream, const Move& move) {

}

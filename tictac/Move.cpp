#include <iostream>
#include <cctype>
#include "Errors.h"
#include "Move.h"

// Space for implementing Move functions.

Move::Move(const std::string& input) {
    if (input.length() < 6) { // minimum length of a valid entry is 6
        //throw ParseError("length less than 6");
        //exit(1);
    }
    size_t index = 0;
    if (isdigit(input[index])) {
        int move_num = std::atoi(&input[index]);
        if (1 <= move_num && move_num <= 9) {
            number = move_num;
        }
        else {
            throw ParseError("invalid move number");
            exit(1);
        }
    }
    else {
        throw ParseError("first character is not a move number");
        exit(1);
    }
    index++;
    while (isspace(input[index])) {
        index++;
    }
    if (index == 1) {
        throw ParseError("no whitespace following move number");
        exit(1);
    }
    if (tolower(input[index]) == 'x' || tolower(input[index]) == 'o') {
        player = toupper(input[index]);
    }
    else {
        throw ParseError("invalid player code");
        exit(1);
    }
    index++;
    size_t temp_index = index;
    while (isspace(input[index])) {
        index++;
    }
    if (index == temp_index) {
        throw ParseError("no whitespace following player code");
        exit(1);
    }
    if (tolower(input[index]) == 'a' || tolower(input[index]) == 'b' || tolower(input[index]) == 'c') {
        row = toupper(input[index]);
    }
    else {
        throw ParseError("invalid row");
        exit(1);
    }
    index++;
    if (isdigit(input[index])) {
        int col = std::atoi(&input[index]);
        if (col == 1 || col == 2 || col == 3) {
            column = col;
        }
        else {
            throw ParseError("invalid column");
            exit(1);
        }
    }
    else {
        throw ParseError("column is not a number");
        exit(1);
    }
    index++;
    if (index < input.length() - 1) {
        if (!isspace(input[index])) {
            throw ParseError("no whitespace following column");
            exit(1);
        }
        for (index++; index < input.length(); index++) {
            if (!(isspace(input[index]) || input[index] == '#')) {
                throw ParseError("invalid character following whitespace after column");
                exit(1);
            }
            if (input[index] == '#') {
                break;
            }
        }
    }
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
    return std::cout << move.number << ' ' << move.player << ' ' << move.row << move.column;
}

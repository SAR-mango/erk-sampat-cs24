#include <iostream>

#include "Board.h"
#include "Errors.h"
#include "Move.h"

int main (int argc, char** argv) {
    bool verbose = false;
    if (argc == 2 && std::string(argv[1]) == "-v") {
        verbose = true;
        std::cout << "> ";
    }
    std::string line;
    Board board;
    std::getline(std::cin, line);
    while (!std::cin.eof()) {
        if (std::cin.peek() == EOF && line == "\0") {
            break;
        }
        try {
            Move move(line);
            board.addMove(move);
        }
        catch(const ParseError& e) {
            if (verbose) {
                std::cout << "Parse error: " << e.what() << '\n';
            }
            else {
                std::cout << "Parse error.\n";
            }
            return 1;
        }
        catch(const InvalidMove& e) {
            if (verbose) {
                std::cout << "Invalid move: " << e.what() << '\n';
            }
            else {
                std::cout << "Invalid move.\n";
            }
            return 2;
        }
        std::getline(std::cin, line);
    }
    Game_State status = board.getStatus();
    if (status == GS_PROG_NEW) {
        std::cout << "Game in progress: New game." << std::endl;
    }
    else if (status == GS_PROG_X_TURN) {
        std::cout << "Game in progress: X's turn." << std::endl;
    }
    else if (status == GS_PROG_O_TURN) {
        std::cout << "Game in progress: O's turn." << std::endl;
    }
    else if (status == GS_OVER_X_W) {
        std::cout << "Game over: X wins." << std::endl;
    }
    else if (status == GS_OVER_O_W) {
        std::cout << "Game over: O wins." << std::endl;
    }
    else {
        std::cout << "Game over: Draw." << std::endl;
    }
    return 0;
}

#include "Errors.h"
#include "Board.h"

void Board::addMove(Move move) {
    if (last_move_num == 0) {
        if (move.number != 1) {
            throw InvalidMove("first move number is not 1");
        }
        last_move_num = 1;
        getSquare(move.row, move.column).occupier = move.player;
        if (move.player == 'X') {
            status = GS_PROG_O_TURN;
        }
        else {
            status = GS_PROG_X_TURN;
        }
    }
    if (move.number != last_move_num + 1) {
        throw InvalidMove("move number and last move number are not consecutive");
    }
    if (last_move_num >= 2) {
        if (getWinner() == 'X') {
            status = GS_OVER_X_W;
        }
        else if (getWinner() == 'O') {
            status = GS_OVER_O_W;
        }
        else if (last_move_number == 9) {
            status = GS_OVER_DRAW;
        }
        else {
        }
    }
    if ((move.player == 'X' && status == GS_PROG_O_TURN) || (move.player == 'O' && status == GS_PROG_X_TURN)) {
        throw InvalidMove("other player's turn");
    }
    if (status == GS_OVER_X_W || status == GS_OVER_O_W) {
        throw InvalidMove("a player has already won");
    }
    if (status == GS_OVER_DRAW) {
        throw InvalidMove("the game is a draw");
    }
    if (getSquare(move.row, move.column).occupier != '\0') {
        throw InvalidMove("square was already occupied");
    }
    last_move_num++;
    if (move.player == 'X') {
        status = GS_PROG_O_TURN;
    }
    else {
        status = GS_PROG_X_TURN;
    }
    getSquare(move.row, move.column).occupier = move.player;
}

Game_State Board::getStatus() {
    return status;
}

char Board::getWinner() {
    Square wins[8][3] = {
        {A1, A2, A3}, 
        {B1, B2, B3}, 
        {C1, C2, C3}, 
        {A1, B1, C1}, 
        {A2, B2, C2}, 
        {A3, B3, C3}, 
        {A1, B2, C3}, 
        {A3, B2, C1}
    }
    for (int i = 0; i < 8; i++) {
        if (wins[i][0].occupier == wins[i][1].occupier && wins[i][0].occupier == wins[i][2].occupier) {
            return wins[i][0].occupier;
        }
        else {
            return '\0';
        }
    }
}

Square& Board::getSquare(char row, int col) {
    if (row == 'A') {
        if (col == 1) {
            return &A1;
        }
        else if (col == 2) {
            return &A2;
        }
        else {
            return &A3;
        }
    }
    else if (row == 'B') {
        if (col == 1) {
            return &B1;
        }
        else if (col == 2) {
            return &B2;
        }
        else {
            return &B3;
        }
    }
    else {
        if (col == 1) {
            return &C1;
        }
        else if (col == 2) {
            return &C2;
        }
        else {
            return &C3;
        }
    }
}

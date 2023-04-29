#include "Errors.h"
#include "Board.h"

void Board::addMove(Move move) {
    if (last_move_num == 0) {
        if (move.number != 1) {
            throw InvalidMove("first move number is not 1");
        }
        last_move_num = 1;
        getSquare(move.row, move.column)->occupier = move.player;
        if (move.player == 'X') {
            status = GS_PROG_O_TURN;
        }
        else {
            status = GS_PROG_X_TURN;
        }
    }
    else {
        if (move.number != last_move_num + 1) {
            throw InvalidMove("move number and last move number are not consecutive");
        }
        if ((move.player == 'X' && status == GS_PROG_O_TURN) || (move.player == 'O' && status == GS_PROG_X_TURN)) {
            throw InvalidMove("other player's turn");
        }
        if (status == GS_OVER_X_W || status == GS_OVER_O_W) {
            throw InvalidMove("a player has already won");
        }
        if (getSquare(move.row, move.column)->occupier != '\0') {
            throw InvalidMove("square is already occupied");
        }
        last_move_num++;
        if (move.player == 'X') {
            status = GS_PROG_O_TURN;
        }
        else {
            status = GS_PROG_X_TURN;
        }
        getSquare(move.row, move.column)->occupier = move.player;
        if (last_move_num >= 5) {
            if (getWinner() == 'X') {
                status = GS_OVER_X_W;
            }
            else if (getWinner() == 'O') {
                status = GS_OVER_O_W;
            }
            else if (last_move_num == 9) {
                status = GS_OVER_DRAW;
            }
            else {
            }
        }
    }
}

Game_State Board::getStatus() {
    return status;
}

char Board::getWinner() {
    for (int i = 0; i < 8; i++) {
        if (wins[i][0]->occupier == wins[i][1]->occupier && wins[i][0]->occupier == wins[i][2]->occupier && wins[i][0]->occupier != '\0') {
            return wins[i][0]->occupier;
        }
    }
    return '\0';
}

Square* Board::getSquare(char row, int col) {
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

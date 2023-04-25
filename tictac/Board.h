#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

enum Game_State {GS_PROG_NEW, GS_PROG_X_TURN, GS_PROG_O_TURN, GS_OVER_X_W, GS_OVER_O_W, GS_OVER_DRAW};
struct Square {
    char occupier = '\0';
};

class Board {
    public:
        void addMove(Move move);
        Game_State getStatus();

    private:
        int last_move_num = 0;
        Square A1, A2, A3, B1, B2, B3, C1, C2, C3;
        Square* wins[8][3] = {
            {&A1, &A2, &A3}, 
            {&B1, &B2, &B3}, 
            {&C1, &C2, &C3}, 
            {&A1, &B1, &C1}, 
            {&A2, &B2, &C2}, 
            {&A3, &B3, &C3}, 
            {&A1, &B2, &C3}, 
            {&A3, &B2, &C1}
        };
        Game_State status = GS_PROG_NEW;

        char getWinner();
        Square* getSquare(char row, int col);
};

#endif

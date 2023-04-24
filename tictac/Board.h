#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

enum game_state {GS_PROG_NEW, GS_PROG_X_TURN, GS_PROG_O_TURN, GS_OVER_X_W, GS_OVER_O_W, GS_OVER_DRAW};

class Board {
    public:
        game_state getStatus();
        void addMove(Move move);
        Board();
    private:
        int move_num = 0;
        struct Square {
            bool occupied = false;
            char occupier = '';
        }
        int occ_squares = 0;
        Square A1, A2, A3, B1, B2, B3, C1, C2, C3;
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
}

#endif

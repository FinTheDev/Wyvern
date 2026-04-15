#pragma once

#include "../include/types.h"

struct Board {
    Piece squares[8][8];
    
    void setupSquare(int row, int col, PieceType piece, Color color);
    void setupStartingPosition();
    void print();
};

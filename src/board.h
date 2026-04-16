#pragma once

#include "../include/types.h"
#include "move.h"

struct Board {
    Piece squares[8][8];
    Color sideToMove;

    void setupSquare(int row, int col, PieceType piece, Color color);
    void setupStartingPosition();
    void print();
    void makeMove(const Move& m);
    void undoMove(const Move& m);
};

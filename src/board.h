#pragma once

#include "../include/types.h"
#include "move.h"

struct Board {
    Piece squares[8][8];
    Color sideToMove;

    bool whiteKingMoved = false;
    bool blackKingMoved = false;

    bool whiteKingsideRookMoved = false;
    bool whiteQueensideRookMoved = false;

    bool blackKingsideRookMoved = false;
    bool blackQueensideRookMoved = false;

    void setupSquare(int row, int col, PieceType piece, Color color);
    void setupStartingPosition();
    void print();
    void makeMove(Move& m);
    void undoMove(Move& m);

    bool findKing(Color color, int& row, int& col) const;
    bool isSquareAttacked(int row, int col, Color attacker) const;
    bool isKingInCheck(Color side) const;
};

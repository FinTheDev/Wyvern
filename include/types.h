#pragma once

enum class PieceType {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class Color {
    WHITE,
    BLACK,
    NONE
};

struct Square {
    int row;
    int col;
};

struct Piece {
    PieceType type;
    Color color;
};

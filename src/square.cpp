#include "square.h"

std::string coordToSquare(int row, int col) {
    char file = 'a' + col;
    char rank = '1' + row;
    return std::string() + file + rank;
}

std::string moveToString(int r1, int c1, int r2, int c2) {
    return coordToSquare(r1, c1) + coordToSquare(r2, c2);
}

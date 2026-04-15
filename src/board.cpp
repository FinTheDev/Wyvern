#include <iostream>
#include "board.h"

void Board::setupStartingPosition() {}

void Board::print() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            std::cout << ". ";
        }
        std::cout << "\n";
    }
}

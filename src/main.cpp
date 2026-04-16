#include <iostream>
#include "board.h"
#include "perft.h"

int main() {

    Board board;
    board.setupStartingPosition();

    std::cout << perft(board, 1) << std::endl;
    std::cout << perft(board, 2) << std::endl;
    std::cout << perft(board, 3) << std::endl;

    return 0;
}

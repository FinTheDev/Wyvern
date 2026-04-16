#include <iostream>
#include "board.h"
#include "perft.h"

int main() {

    Board board;
    board.setupStartingPosition();

    perft(board, 4);

    return 0;
}

#include <iostream>
#include <vector>
#include "board.h"
#include "movegen.h"
#include "square.h"

int main() {

    Board board;
    board.setupStartingPosition();
    board.print();

    std::vector<Move> moves;
    
    for (const Move& m : moves) {
        std::cout << moveToString(m.fromRow, m.fromCol, m.toRow, m.toCol) << std::endl;
    }
    
    return 0;
}

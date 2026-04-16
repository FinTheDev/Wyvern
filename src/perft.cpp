#include <iostream>
#include <vector>
#include "board.h"
#include "movegen.h"
#include "square.h"

long long perft(Board& board, int depth) {
    if (depth == 0)
        return 1;

    std::vector<Move> moves;
    generateMoves(board, moves);

    long long total = 0;

    for (Move& m : moves) {
        board.makeMove(m);

        Color sideJustMoved =
            (board.sideToMove == Color::WHITE) ? Color::BLACK : Color::WHITE;

        if (!board.isKingInCheck(sideJustMoved)) {
            total += perft(board, depth - 1);
        }

        board.undoMove(m);
    }

    if (depth == 4)
        std::cout << "TOTAL: " << total << std::endl;

    return total;
}

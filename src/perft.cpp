#include <vector>
#include "board.h"
#include "movegen.h"

long long perft(Board& board, int depth) {
    if (depth == 0)
        return 1;

    std::vector<Move> moves;
    generateMoves(board, moves);

    long long nodes = 0;

    for (const Move& m : moves) {
        board.makeMove(m);
        nodes += perft(board, depth - 1);
        board.undoMove(m);
    }

    return nodes;
}

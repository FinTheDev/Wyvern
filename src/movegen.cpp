#include <iostream>
#include "movegen.h"
#include "board.h"

void genKnight(const Board& board, int row, int col, std::vector<Move>& moveList) {
    int rowOffsets[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int colOffsets[8] = {1, -1, 1, -1, 2, -2, 2, -2};

    for (int i = 0; i < 8; i++) {
        const int targetRow = row + rowOffsets[i];
        const int targetCol = col + colOffsets[i];

        if (targetRow < 0 || targetRow >= 8 || targetCol < 0 || targetCol >= 8) {
            continue;
        }

        Piece targetPiece = board.squares[targetRow][targetCol];
        Piece currentPiece = board.squares[row][col];

        if (targetPiece.type == PieceType::EMPTY ||
            targetPiece.color != currentPiece.color) {

            moveList.push_back(Move(row, col, targetRow, targetCol));
        }
    }
}

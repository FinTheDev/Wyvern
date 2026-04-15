#include <cassert>
#include "movegen.h"
#include "board.h"

void genKnight(const Board& board, int row, int col, std::vector<Move>& moveList) {
    int rowOffsets[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int colOffsets[8] = {1, -1, 1, -1, 2, -2, 2, -2};

    Piece currentPiece = board.squares[row][col];
    assert(currentPiece.type != PieceType::EMPTY);

    for (int i = 0; i < 8; i++) {
        const int targetRow = row + rowOffsets[i];
        const int targetCol = col + colOffsets[i];

        if (targetRow < 0 || targetRow >= 8 || targetCol < 0 || targetCol >= 8) {
            continue;
        }

        Piece targetPiece = board.squares[targetRow][targetCol];

        if (targetPiece.type == PieceType::EMPTY ||
            targetPiece.color != currentPiece.color) {

            moveList.push_back(Move(row, col, targetRow, targetCol));
        }
    }
}

void genRook(const Board& board, int row, int col, std::vector<Move>& moveList) {
    int directions[4][2] = {
        {-1, 0},
        { 1, 0},
        { 0,-1},
        { 0, 1}
    };
    
    Piece currentPiece = board.squares[row][col];
    assert(currentPiece.type != PieceType::EMPTY);

    for (int i = 0; i < 4; i++) {

        int directionRow = directions[i][0];
        int directionCol = directions[i][1];

        int targetRow = row + directionRow;
        int targetCol = col + directionCol;

        while (targetRow >= 0 && targetRow < 8 &&
               targetCol >= 0 && targetCol < 8) {

            Piece targetPiece = board.squares[targetRow][targetCol];

            if (targetPiece.type == PieceType::EMPTY) {
                moveList.push_back(Move(row, col, targetRow, targetCol));
            }
            else {
                if (targetPiece.color != currentPiece.color) {
                    moveList.push_back(Move(row, col, targetRow, targetCol));
                }
                break;
            }

            targetRow += directionRow;
            targetCol += directionCol;
        }
    }
}

#include <cassert>
#include "movegen.h"
#include "board.h"

void generateMoves(const Board& board, std::vector<Move>& moves) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece p = board.squares[r][c];

            if (p.type == PieceType::EMPTY)
                continue;

            if (p.color != board.sideToMove)
                continue;

            switch (p.type) {
                case PieceType::PAWN:
                    genPawn(board, r, c, moves);
                    break;

                case PieceType::KNIGHT:
                    genKnight(board, r, c, moves);
                    break;

                case PieceType::BISHOP:
                    genBishop(board, r, c, moves);
                    break;

                case PieceType::ROOK:
                    genRook(board, r, c, moves);
                    break;

                case PieceType::QUEEN:
                    genQueen(board, r, c, moves);
                    break;

                case PieceType::KING:
                    genKing(board, r, c, moves);
                    break;

                default:
                    break;
            }
        }
    }
}

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

            moveList.push_back(
                Move(row, col, targetRow, targetCol, board.squares[targetRow][targetCol])
            );
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
                moveList.push_back(
                    Move(row, col, targetRow, targetCol, board.squares[targetRow][targetCol])
                );
            }
            else {
                if (targetPiece.color != currentPiece.color) {
                    moveList.push_back(
                        Move(row, col, targetRow, targetCol, board.squares[targetRow][targetCol])
                    );
                }
                break;
            }

            targetRow += directionRow;
            targetCol += directionCol;
        }
    }
}

void genBishop(const Board& board, int row, int col, std::vector<Move>& moveList) {
    int directions[4][2] = {
        {-1,-1},
        {-1, 1},
        { 1,-1},
        { 1, 1}
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
                moveList.push_back(
                    Move(row, col, targetRow, targetCol, board.squares[targetRow][targetCol])
                );
            }
            else {
                if (targetPiece.color != currentPiece.color) {
                    moveList.push_back(
                        Move(row, col, targetRow, targetCol, board.squares[targetRow][targetCol])
                    );
                }
                break;
            }

            targetRow += directionRow;
            targetCol += directionCol;
        }
    }
}

void genQueen(const Board& board, int row, int col, std::vector<Move>& moveList) {
    genRook(board, row, col, moveList);
    genBishop(board, row, col, moveList);
}

void genKing(const Board& board, int row, int col, std::vector<Move>& moveList) {
    int rowOffsets[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int colOffsets[8] = {1, 0, -1, 1, -1, 1, 0, -1};

    Piece currentPiece = board.squares[row][col];
    assert(currentPiece.type != PieceType::EMPTY);

    for (int i = 0; i < 8; i++) {
        int targetRow = row + rowOffsets[i];
        int targetCol = col + colOffsets[i];

        if (targetRow < 0 || targetRow >= 8 ||
            targetCol < 0 || targetCol >= 8)
            continue;

        Piece targetPiece = board.squares[targetRow][targetCol];

        if (targetPiece.type == PieceType::EMPTY ||
            targetPiece.color != currentPiece.color) {

            moveList.push_back(
                Move(row, col, targetRow, targetCol, board.squares[targetRow][targetCol])
            );
        }
    }

    if (currentPiece.color == Color::WHITE && row == 0 && col == 4 && !board.whiteKingMoved) {
        if (!board.whiteKingsideRookMoved &&
            board.squares[0][7].type == PieceType::ROOK &&
            board.squares[0][7].color == Color::WHITE &&
            board.squares[row][col+1].type == PieceType::EMPTY &&
            board.squares[row][col+2].type == PieceType::EMPTY &&
            !board.isSquareAttacked(0,4,Color::BLACK) &&
            !board.isSquareAttacked(0,5,Color::BLACK) &&
            !board.isSquareAttacked(0,6,Color::BLACK)) {

            moveList.push_back(
                Move(row, col, row, col+2, board.squares[row][col+2])
            );
        }

        if (!board.whiteQueensideRookMoved &&
            board.squares[0][0].type == PieceType::ROOK &&
            board.squares[0][0].color == Color::WHITE &&
            board.squares[row][col-1].type == PieceType::EMPTY &&
            board.squares[row][col-2].type == PieceType::EMPTY &&
            board.squares[row][col-3].type == PieceType::EMPTY &&
            !board.isSquareAttacked(0,4,Color::BLACK) &&
            !board.isSquareAttacked(0,3,Color::BLACK) &&
            !board.isSquareAttacked(0,2,Color::BLACK)) {

            moveList.push_back(
                Move(row, col, row, col-2, board.squares[row][col-2])
            );
        }
    }

    if (currentPiece.color == Color::BLACK && row == 7 && col == 4 && !board.blackKingMoved) {
        if (!board.blackKingsideRookMoved &&
            board.squares[7][7].type == PieceType::ROOK &&
            board.squares[7][7].color == Color::BLACK &&
            board.squares[row][col+1].type == PieceType::EMPTY &&
            board.squares[row][col+2].type == PieceType::EMPTY &&
            !board.isSquareAttacked(7,4,Color::WHITE) &&
            !board.isSquareAttacked(7,5,Color::WHITE) &&
            !board.isSquareAttacked(7,6,Color::WHITE)) {

            moveList.push_back(
                Move(row, col, row, col+2, board.squares[row][col+2])
            );
        }

        if (!board.blackQueensideRookMoved &&
            board.squares[7][0].type == PieceType::ROOK &&
            board.squares[7][0].color == Color::BLACK &&
            board.squares[row][col-1].type == PieceType::EMPTY &&
            board.squares[row][col-2].type == PieceType::EMPTY &&
            board.squares[row][col-3].type == PieceType::EMPTY &&
            !board.isSquareAttacked(7,4,Color::WHITE) &&
            !board.isSquareAttacked(7,3,Color::WHITE) &&
            !board.isSquareAttacked(7,2,Color::WHITE)) {

            moveList.push_back(
                Move(row, col, row, col-2, board.squares[row][col-2])
            );
        }
    }
}

void genPawn(const Board& board, int row, int col, std::vector<Move>& moveList) {
    Piece currentPiece = board.squares[row][col];
    assert(currentPiece.type == PieceType::PAWN);

    int dir = (currentPiece.color == Color::WHITE) ? 1 : -1;
    int forwardRow = row + dir;

    if (forwardRow >= 0 && forwardRow < 8) {
        if (board.squares[forwardRow][col].type == PieceType::EMPTY) {
            moveList.push_back(
                Move(row, col, forwardRow, col, board.squares[forwardRow][col])
            );

            int startRank = (currentPiece.color == Color::WHITE) ? 1 : 6;

            if (row == startRank) {
                int doubleRow = row + 2 * dir;

                if (doubleRow >= 0 && doubleRow < 8 &&
                    board.squares[doubleRow][col].type == PieceType::EMPTY) {

                    moveList.push_back(
                        Move(row, col, doubleRow, col, board.squares[doubleRow][col])
                    );
                }
            }
        }

        int captureCols[2] = {col - 1, col + 1};

        for (int i = 0; i < 2; i++) {
            int c = captureCols[i];

            if (c < 0 || c >= 8)
                continue;

            Piece target = board.squares[forwardRow][c];

            if (target.type != PieceType::EMPTY &&
                target.color != currentPiece.color) {

                moveList.push_back(
                    Move(row, col, forwardRow, c, board.squares[forwardRow][c])
                );
            }
        }
    }
}

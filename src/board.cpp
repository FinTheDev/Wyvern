#include <iostream>
#include <cctype>
#include "board.h"

void Board::setupSquare(int row, int col, PieceType piece, Color color) {
    squares[row][col] = {piece, color};
}

void Board::setupStartingPosition() {
    sideToMove = Color::WHITE;

    const PieceType backRank[8] = {
        PieceType::ROOK,
        PieceType::KNIGHT,
        PieceType::BISHOP,
        PieceType::QUEEN,
        PieceType::KING,
        PieceType::BISHOP,
        PieceType::KNIGHT,
        PieceType::ROOK
    };

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            setupSquare(r, c, PieceType::EMPTY, Color::NONE);

    for (int c = 0; c < 8; c++) {
        setupSquare(0, c, backRank[c], Color::WHITE);
        setupSquare(7, c, backRank[c], Color::BLACK);
    }

    for (int c = 0; c < 8; c++) {
        setupSquare(1, c, PieceType::PAWN, Color::WHITE);
        setupSquare(6, c, PieceType::PAWN, Color::BLACK);
    }
}

void Board::print() {
    for (int r = 7; r >= 0; r--) {
        std::cout << r + 1 << " ";

        for (int c = 0; c < 8; c++) {
            Piece p = squares[r][c];
            char symbol = '.';

            switch (p.type) {
                case PieceType::PAWN:   symbol = 'P'; break;
                case PieceType::KNIGHT: symbol = 'N'; break;
                case PieceType::BISHOP: symbol = 'B'; break;
                case PieceType::ROOK:   symbol = 'R'; break;
                case PieceType::QUEEN:  symbol = 'Q'; break;
                case PieceType::KING:   symbol = 'K'; break;
                default: break;
            }

            if (p.color == Color::BLACK)
                symbol = std::tolower(symbol);

            std::cout << symbol << " ";
        }

        std::cout << "\n";
    }

    std::cout << "  a b c d e f g h\n";
}

void Board::makeMove(Move& m) {
    m.prevWhiteKingMoved = whiteKingMoved;
    m.prevBlackKingMoved = blackKingMoved;
    m.prevWhiteKingsideRookMoved = whiteKingsideRookMoved;
    m.prevWhiteQueensideRookMoved = whiteQueensideRookMoved;
    m.prevBlackKingsideRookMoved = blackKingsideRookMoved;
    m.prevBlackQueensideRookMoved = blackQueensideRookMoved;

    Piece movingPiece = squares[m.fromRow][m.fromCol];
    m.captured = squares[m.toRow][m.toCol];
    Piece capturedPiece = m.captured;

    squares[m.toRow][m.toCol] = movingPiece;
    squares[m.fromRow][m.fromCol] = {PieceType::EMPTY, Color::NONE};

    if (movingPiece.type == PieceType::KING) {
        if (movingPiece.color == Color::WHITE)
            whiteKingMoved = true;
        else
            blackKingMoved = true;
    }

    if (movingPiece.type == PieceType::ROOK) {
        if (m.fromRow == 0 && m.fromCol == 0)
            whiteQueensideRookMoved = true;
        if (m.fromRow == 0 && m.fromCol == 7)
            whiteKingsideRookMoved = true;
        if (m.fromRow == 7 && m.fromCol == 0)
            blackQueensideRookMoved = true;
        if (m.fromRow == 7 && m.fromCol == 7)
            blackKingsideRookMoved = true;
    }

    if (capturedPiece.type == PieceType::ROOK) {
        if (m.toRow == 0 && m.toCol == 0)
            whiteQueensideRookMoved = true;
        if (m.toRow == 0 && m.toCol == 7)
            whiteKingsideRookMoved = true;
        if (m.toRow == 7 && m.toCol == 0)
            blackQueensideRookMoved = true;
        if (m.toRow == 7 && m.toCol == 7)
            blackKingsideRookMoved = true;
    }

    if (movingPiece.type == PieceType::KING && m.fromRow == m.toRow && m.fromCol == 4 && m.toCol == 6) {
        squares[m.toRow][5] = squares[m.toRow][7];
        squares[m.toRow][7] = {PieceType::EMPTY, Color::NONE};
    }

    if (movingPiece.type == PieceType::KING && m.fromRow == m.toRow && m.fromCol == 4 && m.toCol == 2) {
        squares[m.toRow][3] = squares[m.toRow][0];
        squares[m.toRow][0] = {PieceType::EMPTY, Color::NONE};
    }

    sideToMove = (sideToMove == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

void Board::undoMove(Move& m) {
    Piece movingPiece = squares[m.toRow][m.toCol];

    squares[m.fromRow][m.fromCol] = movingPiece;
    squares[m.toRow][m.toCol] = m.captured;

    sideToMove = (sideToMove == Color::WHITE) ? Color::BLACK : Color::WHITE;

    if (movingPiece.type == PieceType::KING && m.fromRow == m.toRow && m.fromCol == 4 && m.toCol == 6) {
        squares[m.toRow][7] = squares[m.toRow][5];
        squares[m.toRow][5] = {PieceType::EMPTY, Color::NONE};
    }

    if (movingPiece.type == PieceType::KING && m.fromRow == m.toRow && m.fromCol == 4 && m.toCol == 2) {
        squares[m.toRow][0] = squares[m.toRow][3];
        squares[m.toRow][3] = {PieceType::EMPTY, Color::NONE};
    }

    whiteKingMoved = m.prevWhiteKingMoved;
    blackKingMoved = m.prevBlackKingMoved;
    whiteKingsideRookMoved = m.prevWhiteKingsideRookMoved;
    whiteQueensideRookMoved = m.prevWhiteQueensideRookMoved;
    blackKingsideRookMoved = m.prevBlackKingsideRookMoved;
    blackQueensideRookMoved = m.prevBlackQueensideRookMoved;
}

bool Board::findKing(Color color, int& row, int& col) const {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece p = squares[r][c];
            if (p.type == PieceType::KING && p.color == color) {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

bool Board::isSquareAttacked(int row, int col, Color attacker) const {
    int knightOffsets[8][2] = {
        {2,1},{2,-1},{-2,1},{-2,-1},
        {1,2},{1,-2},{-1,2},{-1,-2}
    };

    for (auto& o : knightOffsets) {
        int r = row + o[0];
        int c = col + o[1];

        if (r>=0 && r<8 && c>=0 && c<8) {
            Piece p = squares[r][c];
            if (p.type == PieceType::KNIGHT && p.color == attacker)
                return true;
        }
    }

    int rookDirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    for (auto& d : rookDirs) {
        int r = row + d[0];
        int c = col + d[1];

        while (r>=0 && r<8 && c>=0 && c<8) {
            Piece p = squares[r][c];

            if (p.type != PieceType::EMPTY) {
                if (p.color == attacker &&
                   (p.type == PieceType::ROOK || p.type == PieceType::QUEEN))
                    return true;
                break;
            }

            r += d[0];
            c += d[1];
        }
    }

    int bishopDirs[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};

    for (auto& d : bishopDirs) {
        int r = row + d[0];
        int c = col + d[1];

        while (r>=0 && r<8 && c>=0 && c<8) {
            Piece p = squares[r][c];

            if (p.type != PieceType::EMPTY) {
                if (p.color == attacker &&
                   (p.type == PieceType::BISHOP || p.type == PieceType::QUEEN))
                    return true;
                break;
            }

            r += d[0];
            c += d[1];
        }
    }

    return false;
}

bool Board::isKingInCheck(Color side) const {
    int row, col;

    if (!findKing(side, row, col))
        return false;

    Color enemy = (side == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return isSquareAttacked(row, col, enemy);
}

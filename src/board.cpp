#include <iostream>
#include <cctype>
#include "board.h"

void Board::setupSquare(int row, int col, PieceType piece, Color color) {
    squares[row][col] = {piece, color};
}

void Board::setupStartingPosition() {
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

#include <iostream>
#include <cctype>
#include "board.h"

void Board::setupStartingPosition() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            squares[r][c] = {PieceType::EMPTY, Color::NONE};
        }
    }

    squares[0][0] = {PieceType::ROOK, Color::BLACK};
    squares[0][1] = {PieceType::KNIGHT, Color::BLACK};
    squares[0][2] = {PieceType::BISHOP, Color::BLACK};
    squares[0][3] = {PieceType::QUEEN, Color::BLACK};
    squares[0][4] = {PieceType::KING, Color::BLACK};
    squares[0][5] = {PieceType::BISHOP, Color::BLACK};
    squares[0][6] = {PieceType::KNIGHT, Color::BLACK};
    squares[0][7] = {PieceType::ROOK, Color::BLACK};

    for (int c = 0; c < 8; c++)
        squares[1][c] = {PieceType::PAWN, Color::BLACK};

    for (int c = 0; c < 8; c++)
        squares[6][c] = {PieceType::PAWN, Color::WHITE};

    squares[7][0] = {PieceType::ROOK, Color::WHITE};
    squares[7][1] = {PieceType::KNIGHT, Color::WHITE};
    squares[7][2] = {PieceType::BISHOP, Color::WHITE};
    squares[7][3] = {PieceType::QUEEN, Color::WHITE};
    squares[7][4] = {PieceType::KING, Color::WHITE};
    squares[7][5] = {PieceType::BISHOP, Color::WHITE};
    squares[7][6] = {PieceType::KNIGHT, Color::WHITE};
    squares[7][7] = {PieceType::ROOK, Color::WHITE};
}

void Board::print() {

    for (int r = 0; r < 8; r++) {
        
        std::cout << 8 - r << " ";

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
                symbol = static_cast<char>(tolower(symbol));

            std::cout << symbol << " ";
        }

        std::cout << "\n";
    }

    std::cout << "  a b c d e f g h\n";
}

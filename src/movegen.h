#pragma once

#include "board.h"
#include "move.h"
#include <vector>

void genKnight(const Board& board, int row, int col, std::vector<Move>& moveList);
void genRook(const Board& board, int row, int col, std::vector<Move>& moveList);
void genBishop(const Board& board, int row, int col, std::vector<Move>& moveList);
void genQueen(const Board& board, int row, int col, std::vector<Move>& moveList);

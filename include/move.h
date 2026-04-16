#pragma once

struct Move {
    int fromRow, fromCol;
    int toRow, toCol;

    Piece captured;

    bool prevWhiteKingMoved;
    bool prevBlackKingMoved;
    bool prevWhiteKingsideRookMoved;
    bool prevWhiteQueensideRookMoved;
    bool prevBlackKingsideRookMoved;
    bool prevBlackQueensideRookMoved;

    Move(int fr, int fc, int tr, int tc, Piece cap)
        : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), captured(cap) {}
};

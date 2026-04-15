#pragma once

#include "../include/types.h"

struct Board {
    Piece squares[8][8];

    void setupStartingPosition();
    void print();
};

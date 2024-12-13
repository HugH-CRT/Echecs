#ifndef GLOBAL_H
#define GLOBAL_H

namespace ChessGame
{

struct Color
{
    int r;
    int g;
    int b;
    int a;
};

enum PlayerColor
{
    White = 0,
    Black = 1,
};

enum PieceType
{
    Pawn   = 0,
    Knight = 1,
    Bishop = 2,
    Rook   = 3,
    Queen  = 4,
    King   = 5,
};

}

#endif // GLOBAL_H

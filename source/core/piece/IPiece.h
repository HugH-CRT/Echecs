#ifndef IPIECE_H
#define IPIECE_H

#include "global.h"

#include <string>

class ChessBoard;

class IPiece
{
public:
    IPiece(int x, int y, ChessGame::PlayerColor color, ChessGame::PieceType piece, ChessBoard* board);
    IPiece(int x, int y, ChessGame::PlayerColor color, ChessGame::PieceType piece, const std::string &asset, ChessBoard* board);
    virtual ~IPiece() = default;

    int x(void) const { return _x; }
    int y(void) const { return _y; }
    ChessGame::PlayerColor color(void) const { return _color; }
    ChessGame::PieceType piece(void) const { return _type; }
    bool firstMove() const { return b_firstMove; }

    virtual bool move(int x, int y) = 0;

protected:
    void place(int x, int y);

    ChessBoard *_board = nullptr; // didn't have ownership.

    int _x, _y;
    ChessGame::PlayerColor _color;
    ChessGame::PieceType _type;
    bool b_firstMove = true;
    std::string _assetPath = "";
};

#endif // IPIECE_H

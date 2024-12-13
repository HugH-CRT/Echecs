#include "core/Piece/IPiece.h"

IPiece::IPiece(int x,
               int y,
               ChessGame::PlayerColor color,
               ChessGame::PieceType piece,
               ChessBoard *board)
    : _x(x)
    , _y(y)
    , _color(color)
    , _type(piece)
    , _board(board)
{
    //
}

IPiece::IPiece(int x,
               int y,
               ChessGame::PlayerColor color,
               ChessGame::PieceType piece,
               const std::string &asset,
               ChessBoard *board)
    : _x(x)
    , _y(y)
    , _color(color)
    , _type(piece)
    , _assetPath(asset)
    , _board(board)
{
    //
}

void IPiece::place(int x, int y)
{
    _x = x;
    _y = y;

    // @todo logic place with ChessBoard
}


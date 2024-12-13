#include "player.h"

#include "Piece/IPiece.h"

IPlayer::IPlayer(ChessGame::PlayerColor color)
    : _color(color)
{
    //
}

WhitePlayer::WhitePlayer()
    : IPlayer(ChessGame::PlayerColor::White)
{
    //
}

WhitePlayer::~WhitePlayer()
{
    //
}

BlackPlayer::BlackPlayer()
    : IPlayer(ChessGame::PlayerColor::Black)
{
    //
}

BlackPlayer::~BlackPlayer()
{
    //
}

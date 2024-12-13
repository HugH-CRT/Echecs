#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"

#include <vector>
#include <memory>

class IPiece;

///////////////// IPlayer /////////////////

class IPlayer
{
public:
    IPlayer(ChessGame::PlayerColor color);
    virtual ~IPlayer() = default;

    ChessGame::PlayerColor color(void) const { return _color; }

protected:
    std::vector<std::unique_ptr<IPiece>> m_pieces;
    ChessGame::PlayerColor _color;
};

///////////////// ///////////////// /////////////////


///////////////// WhitePlayer /////////////////

class WhitePlayer final : public IPlayer
{
public:
    WhitePlayer();
    ~WhitePlayer() override;
};

///////////////// ///////////////// /////////////////


///////////////// BlackPlayer /////////////////

class BlackPlayer final : public IPlayer
{
public:
    BlackPlayer();
    ~BlackPlayer() override;
};

///////////////// ///////////////// /////////////////

#endif // PLAYER_H

/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de Player
 * @file Player.h
 * @date 26/10/2021
 * @version 0.8
 */

#if !defined Joueur_h
#define Joueur_h

#include "Piece.h"
#include "ChessBoard.h"

class Player
{
   protected:
    Piece *m_pieces[16];
    bool p_isWhite;

   public:
    Player();
    virtual ~Player();
    bool IsWhite();
    bool PlacePieces( ChessBoard &e );
};

class PlayerWhite : public Player
{
   public:
    PlayerWhite();
};

class PlayerBlack : public Player
{
   public:
    PlayerBlack();
};

#endif

/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de Joueur
 * @file Joueur.cpp
 * @date 26/10/2021
 * @version 0.5
 */

#include <assert.h>
#include <iostream>
#include "Player.h"

using namespace std;

/**
 * @brief Constructeur par défaut
 */
Player::Player(){}

/**
 * @brief Destructeur
 */
Player::~Player()
{
    for ( int i = 0; i < 16; i++ )
        delete m_pieces[i];
}

/**
 * @brief Place toutes les pieces du joueur sur l'ChessBoard
 * @param ChessBoard e
 * @return bool -> Determine si le placement des pieces s'est correctement effectuer
 */
bool
Player::PlacePieces( ChessBoard &e )
{
    for ( int i = 0; i < 16; i++ )
        if ( !e.PlacePiece( m_pieces[i] ) )
            return false;
    return true;
}

/**
 * @brief Constructeur du joueur Blanc, crée ces pieces et les ajoute dans sa liste de pieces
 */
PlayerWhite::PlayerWhite()
{
    int  p        = 0;
    string i_r    = ":/img/white/assets/white/king.png";
    King *r        = new King( true, i_r );
    m_pieces[p++] = r;

    string i_q    = ":/img/white/assets/white/queen.png";
    Queen *q      = new Queen( true, i_q );
    m_pieces[p++] = q;

    string i_t    = ":/img/white/assets/white/rook.png";
    Rook *tg      = new Rook( true, true, i_t );
    m_pieces[p++] = tg;
    Rook *td      = new Rook( true, false, i_t );
    m_pieces[p++] = td;

    string i_f    = ":/img/white/assets/white/bishop.png";
    Bishop *fg       = new Bishop( true, true, i_f );
    m_pieces[p++] = fg;
    Bishop *fd       = new Bishop( true, false, i_f );
    m_pieces[p++] = fd;

    string i_c    = ":/img/white/assets/white/knight.png";
    Knight *cg  = new Knight( true, true, i_c );
    m_pieces[p++] = cg;
    Knight *cd  = new Knight( true, false, i_c);
    m_pieces[p++] = cd;

    string i_p    = ":/img/white/assets/white/pawn.png";

    for ( int i = 1; i <= 8; i++ ) {
        Pawn *ptr = new Pawn( true, i , i_p);
        m_pieces[p++] = ptr;
    }
    p_isWhite = true;

    assert( 16 == p );
}

/**
 * @brief Constructeur du joueur Noir, crée ces pieces et les ajoute dans sa liste de pieces
 */
PlayerBlack::PlayerBlack()
{
    int  p        = 0;
    string i_r    = ":/img/black/assets/black/king.png";
    King *r        = new King( false, i_r );
    m_pieces[p++] = r;

    string i_q    = ":/img/black/assets/black/queen.png";
    Queen *q      = new Queen( false, i_q );
    m_pieces[p++] = q;

    string i_t    = ":/img/black/assets/black/rook.png";
    Rook *tg      = new Rook( false, true, i_t );
    m_pieces[p++] = tg;
    Rook *td      = new Rook( false, false, i_t );
    m_pieces[p++] = td;

    string i_f    = ":/img/black/assets/black/bishop.png";
    Bishop *fg       = new Bishop( false, true, i_f );
    m_pieces[p++] = fg;
    Bishop *fd       = new Bishop( false, false, i_f );
    m_pieces[p++] = fd;

    string i_c = ":/img/black/assets/black/knight.png";
    Knight *cg  = new Knight( false, true, i_c );
    m_pieces[p++] = cg;
    Knight *cd  = new Knight( false, false, i_c );
    m_pieces[p++] = cd;

    string i_p    = ":/img/black/assets/black/pawn.png";

    for ( int i = 1; i <= 8; i++ ) {
        Pawn *ptr     = new Pawn( false, i, i_p );
        m_pieces[p++] = ptr;
    }
    p_isWhite = false;
    assert( 16 == p );
}

/**
 * @return Renvoie l'attribut iswhite
 */
bool
Player::IsWhite() { return p_isWhite; }

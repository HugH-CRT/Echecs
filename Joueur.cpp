/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de Joueur
 * @file Joueur.cpp
 * @date 26/10/2021
 * @version 0.5
 */

#include <assert.h>
#include <iostream>
#include "Joueur.h"

using namespace std;

/**
 * @brief Default constructor
 */
Player::Player(){}

/**
 * @brief Destructor of Player
 */
Player::~Player()
{
    for ( int i = 0; i < 16; i++ )
        delete m_pieces[i];
}

/**
 * @brief Place all of the player's pieces on the ChessBoard
 * @param ChessBoard e
 * @return bool -> Determines if the placement of the pieces was done correctly
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
 * @brief White player's constructor, create these pieces and add them to his list of pieces
 */
PlayerWhite::PlayerWhite()
{
    int  p        = 0;
    string i_r    = ":/img_blanc/assets/blanc/roi.png";
    King *r        = new King( true, i_r );
    m_pieces[p++] = r;

    string i_q    = ":/img_blanc/assets/blanc/reine.png";
    Queen *q      = new Queen( true, i_q );
    m_pieces[p++] = q;

    string i_t    = ":/img_blanc/assets/blanc/tour.png";
    Rook *tg      = new Rook( true, true, i_t );
    m_pieces[p++] = tg;
    Rook *td      = new Rook( true, false, i_t );
    m_pieces[p++] = td;

    string i_f    = ":/img_blanc/assets/blanc/fou.png";
    Bishop *fg       = new Bishop( true, true, i_f );
    m_pieces[p++] = fg;
    Bishop *fd       = new Bishop( true, false, i_f );
    m_pieces[p++] = fd;

    string i_c    = ":/img_blanc/assets/blanc/cavalier.png";
    Knight *cg  = new Knight( true, true, i_c );
    m_pieces[p++] = cg;
    Knight *cd  = new Knight( true, false, i_c);
    m_pieces[p++] = cd;

    string i_p    = ":/img_blanc/assets/blanc/pion.png";

    for ( int i = 1; i <= 8; i++ ) {
        Pawn *ptr = new Pawn( true, i , i_p);
        m_pieces[p++] = ptr;
    }
    p_isWhite = true;

    assert( 16 == p );
}

/**
 * @brief Black player's builder, create these pieces and add them to his list of pieces
 */
PlayerBlack::PlayerBlack()
{
    int  p        = 0;
    string i_r    = ":/img_noir/assets/noir/roi.png";
    King *r        = new King( false, i_r );
    m_pieces[p++] = r;

    string i_q    = ":/img_noir/assets/noir/reine.png";
    Queen *q      = new Queen( false, i_q );
    m_pieces[p++] = q;

    string i_t    = ":/img_noir/assets/noir/tour.png";
    Rook *tg      = new Rook( false, true, i_t );
    m_pieces[p++] = tg;
    Rook *td      = new Rook( false, false, i_t );
    m_pieces[p++] = td;

    string i_f    = ":/img_noir/assets/noir/fou.png";
    Bishop *fg       = new Bishop( false, true, i_f );
    m_pieces[p++] = fg;
    Bishop *fd       = new Bishop( false, false, i_f );
    m_pieces[p++] = fd;

    string i_c = ":/img_noir/assets/noir/cavalier.png";
    Knight *cg  = new Knight( false, true, i_c );
    m_pieces[p++] = cg;
    Knight *cd  = new Knight( false, false, i_c );
    m_pieces[p++] = cd;

    string i_p    = ":/img_noir/assets/noir/pion.png";

    for ( int i = 1; i <= 8; i++ ) {
        Pawn *ptr     = new Pawn( false, i, i_p );
        m_pieces[p++] = ptr;
    }
    p_isWhite = false;
    assert( 16 == p );
}

/**
 * @return Returns the iswhite attribute
 */
bool
Player::IsWhite() { return p_isWhite; }

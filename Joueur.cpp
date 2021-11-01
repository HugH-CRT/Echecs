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
 * @brief Joueur::Joueur
 */
Joueur::Joueur(){}

/**
 * @brief Joueur::~Joueur
 */
Joueur::~Joueur()
{
    for ( int i = 0; i < 16; i++ )
        delete m_pieces[i];
}

/**
 * @brief Joueur::placerPieces
 * @param e
 * @return
 */
bool
Joueur::placerPieces( Echiquier &e )
{
    for ( int i = 0; i < 16; i++ )
        if ( !e.placer( m_pieces[i] ) )
            return false;
    return true;
}

/**
 * @brief JoueurBlanc::JoueurBlanc
 */
JoueurBlanc::JoueurBlanc()
{
    int  p        = 0;
    string i_r    = ":/img_blanc/assets/blanc/roi.png";
    Roi *r        = new Roi( true, i_r );
    m_pieces[p++] = r;

    string i_q    = ":/img_blanc/assets/blanc/reine.png";
    Reine *q      = new Reine( true, i_q );
    m_pieces[p++] = q;

    string i_t    = ":/img_blanc/assets/blanc/tour.png";
    Tour *tg      = new Tour( true, true, i_t );
    m_pieces[p++] = tg;
    Tour *td      = new Tour( true, false, i_t );
    m_pieces[p++] = td;

    string i_f    = ":/img_blanc/assets/blanc/fou.png";
    Fou *fg       = new Fou( true, true, i_f );
    m_pieces[p++] = fg;
    Fou *fd       = new Fou( true, false, i_f );
    m_pieces[p++] = fd;

    string i_c    = ":/img_blanc/assets/blanc/cavalier.png";
    Cavalier *cg  = new Cavalier( true, true, i_c );
    m_pieces[p++] = cg;
    Cavalier *cd  = new Cavalier( true, false, i_c);
    m_pieces[p++] = cd;

    string i_p    = ":/img_blanc/assets/blanc/pion.png";

    for ( int i = 1; i <= 8; i++ ) {
        Pion *ptr = new Pion( true, i , i_p);
        m_pieces[p++] = ptr;
    }
    iswhite = true;

    assert( 16 == p );
}

/**
 * @brief JoueurNoir::JoueurNoir
 */
JoueurNoir::JoueurNoir()
{
    int  p        = 0;
    string i_r    = ":/img_noir/assets/noir/roi.png";
    Roi *r        = new Roi( false, i_r );
    m_pieces[p++] = r;

    string i_q    = ":/img_noir/assets/noir/reine.png";
    Reine *q      = new Reine( false, i_q );
    m_pieces[p++] = q;

    string i_t    = ":/img_noir/assets/noir/tour.png";
    Tour *tg      = new Tour( false, true, i_t );
    m_pieces[p++] = tg;
    Tour *td      = new Tour( false, false, i_t );
    m_pieces[p++] = td;

    string i_f    = ":/img_noir/assets/noir/fou.png";
    Fou *fg       = new Fou( false, true, i_f );
    m_pieces[p++] = fg;
    Fou *fd       = new Fou( false, false, i_f );
    m_pieces[p++] = fd;

    string i_c = ":/img_noir/assets/noir/cavalier.png";
    Cavalier *cg  = new Cavalier( false, true, i_c );
    m_pieces[p++] = cg;
    Cavalier *cd  = new Cavalier( false, false, i_c );
    m_pieces[p++] = cd;

    string i_p    = ":/img_noir/assets/noir/pion.png";

    for ( int i = 1; i <= 8; i++ ) {
        Pion *ptr     = new Pion( false, i, i_p );
        m_pieces[p++] = ptr;
    }
    iswhite = false;
    assert( 16 == p );
}

/**
 * @brief Joueur::isWhite
 * @return
 */
bool
Joueur::isWhite() { return iswhite; }

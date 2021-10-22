#include <assert.h>
#include <iostream>
#include "Joueur.h"

using namespace std;

Joueur::~Joueur()
{
    for ( int i = 0; i < 16; i++ )
        delete m_pieces[i];
}

void
Joueur::affiche()
{
    for ( int i = 0; i < 16; i++ )
        m_pieces[i]->affiche();
}

bool
Joueur::placerPieces( Echiquier &e )
{
    for ( int i = 0; i < 16; i++ )
        if ( !e.placer( m_pieces[i] ) )
            return false;
    return true;
}

JoueurBlanc::JoueurBlanc()
{
    int  p        = 0;
    Roi *r        = new Roi( true );
    m_pieces[p++] = r;
    Reine *q      = new Reine( true );
    m_pieces[p++] = q;
    Tour *tg      = new Tour( true, true );
    m_pieces[p++] = tg;
    Tour *td      = new Tour( true, false );
    m_pieces[p++] = td;
    Fou *fg       = new Fou( true, true );
    m_pieces[p++] = fg;
    Fou *fd       = new Fou( true, false );
    m_pieces[p++] = fd;
    Cavalier *cg  = new Cavalier( true, true );
    m_pieces[p++] = cg;
    Cavalier *cd  = new Cavalier( true, false );
    m_pieces[p++] = cd;
    for ( int i = 1; i <= 8; i++ ) {
        Pion *ptr     = new Pion( true, i );
        m_pieces[p++] = ptr;
    }
    assert( 16 == p );
}

JoueurNoir::JoueurNoir()
{
    int  p        = 0;
    Roi *r        = new Roi( false );
    m_pieces[p++] = r;
    Reine *q      = new Reine( false );
    m_pieces[p++] = q;
    Tour *tg      = new Tour( false, true );
    m_pieces[p++] = tg;
    Tour *td      = new Tour( false, false );
    m_pieces[p++] = td;
    Fou *fg       = new Fou( false, true );
    m_pieces[p++] = fg;
    Fou *fd       = new Fou( false, false );
    m_pieces[p++] = fd;
    Cavalier *cg  = new Cavalier( false, true );
    m_pieces[p++] = cg;
    Cavalier *cd  = new Cavalier( false, false );
    m_pieces[p++] = cd;
    for ( int i = 1; i <= 8; i++ ) {
        Pion *ptr     = new Pion( false, i );
        m_pieces[p++] = ptr;
    }
    assert( 16 == p );
}


bool
JoueurBlanc::isWhite()
{
    return true;
}

bool
JoueurNoir::isWhite()
{
    return false;
}
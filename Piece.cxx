#include <iostream>
#include "Piece.h"
using namespace std;

Piece::Piece( int x, int y, bool white )
{
    m_x     = x;
    m_y     = y;
    m_white = white;
    cout << "Constructeur Piece special" << endl;
}

Piece::Piece( const Piece &autre )
{
    m_x     = autre.m_x;
    m_y     = autre.m_y;
    m_white = autre.m_white;
    cout << "Constructeur Piece par copie" << endl;
}

Piece &
Piece::operator=( const Piece &autre )
{
    m_x     = autre.m_x;
    m_y     = autre.m_y;
    m_white = autre.m_white;
    cout << "Affectation Piece" << endl;
    return *this;
}

void
Piece::init( int x, int y, bool white )
{
    m_x     = x;
    m_y     = y;
    m_white = white;
}

void
Piece::move( int x, int y )
{
    m_x = x;
    m_y = y;
}

int
Piece::x()
{
    return m_x;
}

int
Piece::y()
{
    return m_y;
}

bool
Piece::isWhite()
{
    return m_white;
}

bool
Piece::isBlack()
{
    return !m_white;
}

void
Piece::affiche()
{
    cout << "Piece: x=" << m_x << " y=" << m_y << " " << ( m_white ? "blanche" : "noire" ) << endl;
}

char
Piece::vue()
{
    return this->isWhite() ? 'B' : 'N';
}

Roi::Roi( bool white ) : Piece( 5, white ? 1 : 8, white )
{
    cout << "Constructeur Roi" << endl;
}

Roi::~Roi()
{
    cout << "Destructeur Roi" << endl;
}

bool
Roi::mouvementValide( Echiquier &e, int x, int y )
{
    cout << "Mouvement Valide Roi" << endl;
    return true;
}

char
Roi::vue()
{
    return m_white ? 'R' : 'r';
}

void
Roi::roque()
{
    cout << "Roque Roi" << endl;
}

Reine::Reine( bool white )
    : Piece( 4, white ? 1 : 8, white ), Fou( white, true ), Tour( white, true )
{
    cout << "Constructeur Reine" << endl;
}

bool
Reine::mouvementValide( Echiquier &e, int x, int y )
{
    return Fou::mouvementValide( e, x, y ) || Tour::mouvementValide( e, x, y );
}

char
Reine::vue()
{
    return Fou::m_white ? 'Q' : 'q';
}

Tour::Tour( bool white, bool gauche ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white )
{
    cout << "Constructeur Tour" << endl;
}

bool
Tour::mouvementValide( Echiquier &e, int x, int y )
{
    cout << "Mouvement Valide Tour" << endl;
    return false;
}

char
Tour::vue()
{
    return m_white ? 'T' : 't';
}

Fou::Fou( bool white, bool gauche ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white )
{
    cout << "Constructeur Fou" << endl;
}

bool
Fou::mouvementValide( Echiquier &e, int x, int y )
{
    cout << "Mouvement Valide Fou" << endl;
    return false;
}

char
Fou::vue()
{
    return m_white ? 'F' : 'f';
}

Cavalier::Cavalier( bool white, bool gauche ) : Piece( gauche ? 2 : 7, white ? 1 : 8, white )
{
    cout << "Constructeur Cavalier" << endl;
}

bool
Cavalier::mouvementValide( Echiquier &e, int x, int y )
{
    cout << "Mouvement Valide Cavalier" << endl;
    return false;
}

char
Cavalier::vue()
{
    return m_white ? 'C' : 'c';
}

Pion::Pion( bool white, int x ) : Piece( x, white ? 2 : 7, white )
{
    cout << "Constructeur Pion" << endl;
}

bool
Pion::mouvementValide( Echiquier &e, int x, int y )
{
    cout << "Mouvement Valide Pion" << endl;
    return false;
}

char
Pion::vue()
{
    return m_white ? 'P' : 'p';
}

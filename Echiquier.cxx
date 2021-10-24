#include <iostream>
#include <assert.h>
#include "Echiquier.h"

using namespace std;

Echiquier::Echiquier()
{
    for ( int i = 0; i < 64; i++ )
        m_cases[i] = nullptr;
}

Piece *
Echiquier::getPiece( int x, int y )
{
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    return m_cases[( x - 1 ) + ( y - 1 ) * 8];
}


bool
Echiquier::placer( Piece *p )
{
    if ( nullptr == p )
        return false;
    int x = p->x();
    int y = ( *p ).y();
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    if ( nullptr != getPiece( x, y ) )
        return false;  // case non vide
    m_cases[( x - 1 ) + ( y - 1 ) * 8] = p;
    return true;
}

bool
Echiquier::deplacer( Piece *p, int x, int y )
{
    this->enleverPiece( p->x() , p->y() );
    p->move(x,y);
    this->placer(p);
}


Piece *
Echiquier::enleverPiece( int x, int y )
{
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    Piece *ptr                         = m_cases[( x - 1 ) + ( y - 1 ) * 8];
    m_cases[( x - 1 ) + ( y - 1 ) * 8] = nullptr;
    return ptr;
}

void
Echiquier::affiche()
{
    cout << endl << "  12345678" << endl;
    for ( int y = 1; y <= 8; ++y ) {
        cout << y << " ";
        for ( int x = 1; x <= 8; ++x ) {
            char   c;
            Piece *p = getPiece( x, y );
            if ( nullptr == p )
                c = ( ( x + y ) % 2 ) == 0 ? '#' : '.';
            else
                c = p->vue();  // p->isWhite() ? 'B' : 'N';
            cout << c;
        }
        cout << " " << y << endl;
    }
    cout << "  12345678" << endl;
}

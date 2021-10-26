#include <iostream>
#include <assert.h>
#include "Echiquier.h"

using namespace std;

Echiquier::Echiquier()
{
    for ( int i = 0; i < 64; i++ )
        m_cases[i] = nullptr;

    for ( int i = 0; i < 8; i++ )
        for( int j = 0; j < 8 ; j++ )
            matriceVisuel[i][j] = '.';

    for( int j = 0; j < 8 ; j++ )
    {
        matriceVisuel[1][j] = 'P';
        matriceVisuel[6][j] = 'P';
    }

    matriceVisuel[0][0] = 'T';
    matriceVisuel[0][7] = 'T';
    matriceVisuel[7][0] = 'T';
    matriceVisuel[7][7] = 'T';

    matriceVisuel[0][1] = 'C';
    matriceVisuel[0][6] = 'C';
    matriceVisuel[7][1] = 'C';
    matriceVisuel[7][6] = 'C';

    matriceVisuel[0][2] = 'F';
    matriceVisuel[0][5] = 'F';
    matriceVisuel[7][2] = 'F';
    matriceVisuel[7][5] = 'F';

    matriceVisuel[0][3] = 'Q';
    matriceVisuel[0][4] = 'K';
    matriceVisuel[7][3] = 'Q';
    matriceVisuel[7][4] = 'K';

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
    char lettre = matriceVisuel[ p->y() - 1 ][ p->x() - 1 ];

    matriceVisuel[ p->y() - 1 ][ p->x() - 1 ] = '.';
    matriceVisuel[ y - 1 ][ x - 1 ] = '.';

    enleverPiece( p->x() , p->y() );
    enleverPiece( x , y );

    p->move(x,y);

    matriceVisuel[ p->y() - 1 ][ p->x() - 1 ] = lettre;

    placer(p);
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
    for ( int i = 0 ; i < 8 ; i++)
    {
        for ( int j = 0 ; j < 8 ; j++)
        {
            cout << " " << matriceVisuel[i][j];
        }
        cout << "" << endl;
    }
    cout << "" << endl;
}

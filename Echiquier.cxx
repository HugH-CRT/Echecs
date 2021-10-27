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


bool
Echiquier::VerifMoveRoiRoque(Roi *r,int x ,int y)
{
    //Si le Roi est à droite de la tour
    if ( r->x() > x )
    {
        //Parcours les cases entre le roi et la tour
        for ( int i = r->x() - 1  ; i >= x ; i-- )
        {
            //Parcours toutes les pieces de l'echiquier
            for ( int j = 0; j < 64 ; j++ )
            {
                //Si la case n'est pas vide et de la couleur adverse
                if ( m_cases[j]->isWhite()!= r->isWhite() && m_cases[j] != nullptr ) 
                {
                    if ( m_cases[j]->mouvementValide( *this , i , y ) )
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        //Parcours les cases entre le roi et la tour
        for ( int i = r->x() + 1  ; i <= x ; i++ )
        {
            //Parcours toutes les pieces de l'echiquier
            for ( int j = 0; j < 64 ; j++ )
            {
                //Si la case n'est pas vide et de la couleur adverse
                if ( m_cases[j]->isWhite()!= r->isWhite() && m_cases[j] != nullptr ) 
                {
                    if ( m_cases[j]->mouvementValide( *this , i , y ) )
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool 
Echiquier::deplacementRoque( Roi *r, Tour *t)
{

    matriceVisuel[ r->y() - 1 ][ r->x() - 1 ] = '.';
    matriceVisuel[ t->y() - 1 ][ t->x() - 1 ] = '.';

    enleverPiece( r->x() , r->y() );
    enleverPiece( t->x() , t->y() );

    if ( r->isWhite() )
    {
        if ( r->x() > t->x() )
        {
            r->move( 3 , 8 );
            t->move( 4 , 8 );
        }
        else
        {
            r->move( 7 , 8 );
            t->move( 6 , 8 );
        }
    }
    else
    {
        if ( r->x() > t->x() )
        {
            r->move( 3 , 1 );
            t->move( 4 , 1 );
        }
        else
        {
            r->move( 7 , 1 );
            t->move( 6 , 1 );
        }
    }

    matriceVisuel[ r->y() - 1 ][ r->x() - 1 ] = 'R';
    matriceVisuel[ t->y() - 1 ][ t->x() - 1 ] = 'T';

    placer(r);
    placer(t);
}
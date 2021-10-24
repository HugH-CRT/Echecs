#include <iostream>
#include <assert.h>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"
using namespace std;

bool
compare_position( Piece &p, Piece &q )
{
    q = p;
    q.affiche();
    return ( p.x() == q.x() ) && ( p.y() == q.y() );
}

int
main( int argc, char **argv )
{
    Echiquier e;

    JoueurBlanc jb;
    JoueurNoir  jn;

    assert( jb.placerPieces( e ) );
    assert( jn.placerPieces( e ) );

    e.affiche();

    Piece *maPiece = e.getPiece(2,2);

    if( maPiece->mouvementValide(e,2,7) )
    {
        
    }
 

    maPiece->mouvementValide(e,2,3);

    maPiece->mouvementValide(e,2,6);

    maPiece->mouvementValide(e,3,6);

}

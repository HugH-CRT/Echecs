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
    e.affiche();

    JoueurBlanc jb;
    JoueurNoir  jn;

    jb.placerPieces( e ) ;
    jn.placerPieces( e ) ;

    e.affiche();

}

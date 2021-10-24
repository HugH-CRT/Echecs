/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include <assert.h>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

bool
compare_position( Piece &p, Piece &q )
{
    q = p;
    q.affiche();
    return ( p.x() == q.x() ) && ( p.y() == q.y() );
}

/**
 * Programme principal
 */
int
main( int argc, char **argv )
{
    Echiquier e;
    e.affiche();

    JoueurBlanc jb;
    JoueurNoir  jn;
    
    assert( jb.placerPieces( e ) );
    assert( jn.placerPieces( e ) );

    e.affiche();

    Roi rb( true );
    Roi rn( false );

    assert( rb.mouvementValide( e, 2, 2 ) );
    Piece *ptr = &rb;
    assert( ptr->mouvementValide( e, 2, 2 ) ); 

    ptr = &rb;
    Roi *rptr = dynamic_cast<Roi *>( ptr );
    assert( nullptr != rptr );
    rptr->roque();

    Reine qb( true );
    qb.mouvementValide( e, 2, 2 );

}

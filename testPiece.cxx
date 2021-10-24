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
    //Crée l'echiquier avec les 64 pointeurs
    Echiquier e;

    //Crée les 2 joueurs 
    JoueurBlanc jb;
    JoueurNoir  jn;

    //Place les pieces des 2 joueurs
    assert( jb.placerPieces( e ) );
    assert( jn.placerPieces( e ) );

    //Affiche l'echiquier
    e.affiche();

    //Récupère le pion position x = 2 , y = 2
    Piece *maPiece = e.getPiece(2,2);

    //Verifier si on peut le déplacer en avant de 1 case
    if( maPiece->mouvementValide( e , 2 , 3 ) )
    {
        //Déplace la piece sur l'echiquier
        e.deplacer( maPiece , 3 , 7 );
    }

    //Affiche de nouveau l'echiquier avec le pion qui à avancer
    e.affiche();
}

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

    /*
    * Récupère le pion position x = 2 , y = 2
    * Verifier si on peut le déplacer en avant de 2 cases
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec le pion qui à avancer
    */

    Piece *maPieceBlanche = e.getPiece(2,2);

    if( maPieceBlanche->mouvementValide( e , 2 , 4 ) )
    {
        e.deplacer( maPieceBlanche , 2 , 4 );
    }
    e.affiche();

    /*
    * Récupère le pion position x = 1 , y = 7
    * Verifier si on peut le déplacer en avant de 2 cases
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec le pion qui à avancer
    */

    Piece *maPieceNoire = e.getPiece(1,7);

    if( maPieceNoire->mouvementValide( e , 1 , 5 ) )
    {
        e.deplacer( maPieceNoire , 1 , 5 );
    }
    e.affiche();

    /*
    * La piece blanche mange la noire en diagonale
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec le pion qui à avancer
    */

    if( maPieceBlanche->mouvementValide( e , 1 , 5 ) )
    {
        e.deplacer( maPieceBlanche , 1 , 5 );
    }
    e.affiche();

    /*
    * La tour noir avance de 2 cases
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec la tour qui à avancer
    */

    Piece *maTourNoire = e.getPiece(1,8);

    if( maTourNoire->mouvementValide( e , 1 , 6 ) )
    {
        e.deplacer( maTourNoire , 1 , 6 );
    }
    e.affiche();

    /*
    * Le fou blanc avance vers en bas à gauche de 1 case
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec le fou qui à avancer
    */

    Piece *monFouBlanc = e.getPiece( 3 , 1 );

    if( monFouBlanc->mouvementValide( e , 2 , 2 ) )
    {
        e.deplacer( monFouBlanc , 2 , 2 );
    }
    e.affiche();


    /*
    * Le cavalier noir avance vers en bas à gauche 
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec le cavalier qui à avancer
    */
    Piece *monCavalierNoire = e.getPiece( 2 , 1 );

    if( monCavalierNoire->mouvementValide( e , 1 , 3 ) )
    {
        e.deplacer( monCavalierNoire , 1 , 3 );
    }
    e.affiche();


    Piece *monPionBlanc2 = e.getPiece( 5 , 7 );

    if( monPionBlanc2->mouvementValide( e , 5 , 6 ) )
    {
        e.deplacer( monPionBlanc2 , 5 , 6 );
    }
    e.affiche();


    Piece *monRoiBlanc = e.getPiece( 5 , 8 );

    if( monRoiBlanc->mouvementValide( e , 5 , 7 ) )
    {
        e.deplacer( monRoiBlanc , 5 , 7 );
    }
    e.affiche();

    e.afficheVisuel();

}
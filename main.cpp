#include "mainwindow.h"
#include <QApplication>
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
    * La tour noir avance de 1 case
    * Déplace la piece sur l'echiquier
    * Affiche de nouveau l'echiquier avec le pion qui à avancer
    */

    Piece *maTourNoire = e.getPiece(1,8);

    if( maTourNoire->mouvementValide( e , 1 , 6 ) )
    {
        e.deplacer( maTourNoire , 1 , 6 );
    }
    e.affiche();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

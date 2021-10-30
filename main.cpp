/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @file main.cpp
 * @date 26/10/2021
 * @version 0.5
 */

#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <assert.h>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"

using namespace std;


int
main( int argc, char **argv )
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //Crée l'echiquier avec les 64 pointeurs
    Echiquier e;

    //Crée les 2 joueurs
    JoueurBlanc jb;
    JoueurNoir  jn;

    //Place les pieces des 2 joueurs
    assert( jb.placerPieces( e ) );
    assert( jn.placerPieces( e ) );

    //Affiche l'echiquier terminal
    e.affiche();

    return a.exec();

}

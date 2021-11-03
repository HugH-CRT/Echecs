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
#include "Player.h"
#include "ChessBoard.h"

using namespace std;


int
main( int argc, char **argv )
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

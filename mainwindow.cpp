/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de MainWindow
 * @file mainwindow.cpp
 * @date 26/10/2021
 * @version 0.5
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Echiquier.h"
#include "Piece.h"
#include "Joueur.h"
#include <iostream>
#include <assert.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Crée l'echiquier avec les 64 pointeurs
    Echiquier e;

    //Crée les 2 joueurs
    JoueurBlanc jb;
    JoueurNoir  jn;

    //Place les pieces des 2 joueurs
    assert( jb.placerPieces( e ) );
    assert( jn.placerPieces( e ) );

    ui->echiquierView->setModel(/**Model**/);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_echiquierView_cellClicked(int row, int column)
{

}

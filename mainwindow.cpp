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

#include "mainwindow.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QString>
using namespace std;

Echiquier e;
Piece *pieceEnCours;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    JoueurBlanc jb;
    JoueurNoir  jn;

    assert( jb.placerPieces( e ) );
    assert( jn.placerPieces( e ) );

    this->RefreshMatrice(this);


}

MainWindow::~MainWindow() { delete ui; }

void
MainWindow::RefreshMatrice(QWidget *parent)
{
    QStandardItemModel* model = new QStandardItemModel(8,8,parent) ;

    for ( int i = 0 ; i < 8 ; i++ )
    {
        for ( int j = 0 ; j < 8 ; j++ )
        {
            QModelIndex index = model->index(i,j,QModelIndex());
            model->setData(index,QVariant( QString( e.matriceVisuel[i][j] ) ));
        }
    }

    ui->tableViewEchiquier->setModel(model);
}



void MainWindow::on_tableViewEchiquier_clicked(const QModelIndex &index)
{
    cout << index.row() << " " << index.column() << endl;
    pieceEnCours = e.getPiece(index.row(),index.column());

    cout << pieceEnCours << endl;

    if ( pieceEnCours->mouvementValide(e,4,1) )
    {
        e.deplacer(pieceEnCours,4,1);
    }

//    this->RefreshMatrice(this);
}


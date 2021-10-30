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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    assert( jn.placerPieces( e ) );
    assert( jb.placerPieces( e ) );


    this->RefreshMatrice(this);
}

MainWindow::~MainWindow() { delete ui; }

void
MainWindow::RefreshMatrice(QWidget *parent)
{
    model = new QStandardItemModel(8,8,parent) ;

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

    if ( pieceEnCours != nullptr && pieceEnCours->isWhite() == WhitePlay && pieceEnCours->mouvementValide( e, index.column()+1  , index.row()+1  )  )
    {
        e.deplacer( pieceEnCours , index.column()+1  , index.row()+1 );
        WhitePlay = !WhitePlay;
    }
    else
    {
        pieceEnCours = e.getPiece(  index.column()+1  , index.row()+1 );
        pieceEnCours->AfficheMouvementValide();
    }

    this->RefreshMatrice(this);
}

void MainWindow::setColor(int column,int row)
{
   QModelIndex index = model->index(row,column,QModelIndex());
   model->setData(index, QBrush ( QColor( Qt::blue ) ), Qt::BackgroundRole  );
   ui->tableViewEchiquier->setModel(model);
}



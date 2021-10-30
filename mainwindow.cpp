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
    QStandardItemModel* model = new QStandardItemModel(8,8,parent) ;

    for ( int i = 0 ; i < 8 ; i++ )
    {
        for ( int j = 0 ; j < 8 ; j++ )
        {
            QModelIndex index = model->index(i,j,QModelIndex());

            if (e.getPiece(j+1, i+1) != nullptr){
               string s = e.getPiece(j+1, i+1)->path();
               int n = s.length();
               char char_array[n + 1];
               strcpy(char_array, s.c_str());
               QPixmap monImage(char_array);
               QIcon* m_icon = new QIcon();
                m_icon->addPixmap(monImage);
               QStandardItem *m_item = new QStandardItem();
                m_item->setIcon(*m_icon);

               model->setItem(i, j , m_item);
            }
          //  model->setData(index,QVariant( QString( e.matriceVisuel[i][j] ) ));
       }
    }

    ui->tableViewEchiquier->setModel(model);
}


void MainWindow::on_tableViewEchiquier_clicked(const QModelIndex &index)
{

    if ( pieceEnCours != nullptr && pieceEnCours->isWhite() == WhitePlay && pieceEnCours->mouvementValide( e, index.column()+1  , index.row()+1  )  )
    {
        cout << pieceEnCours->isWhite() << endl;
        e.deplacer( pieceEnCours , index.column()+1  , index.row()+1 );
        WhitePlay = !WhitePlay;
    }
    else
    {
        pieceEnCours = e.getPiece(  index.column()+1  , index.row()+1 );
    }

    this->RefreshMatrice(this);
}



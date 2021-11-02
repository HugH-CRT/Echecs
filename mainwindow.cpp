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
#include "stop.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QString>
#include <vector>
#include <string>
#include <sstream>
#include <QStringListModel>

using namespace std;

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    assert( jn.placerPieces( e ) );
    assert( jb.placerPieces( e ) );

    // Initialisation image pour le premier coup
    QPixmap monImage(":/img_blanc/assets/blanc/pion.png");
    ui->TourLabel->setAlignment(Qt::AlignCenter);
    ui->TourLabel->setPixmap(monImage);

    ui->view_PionNoir->setIconSize( QSize( 43 , 43 ) );
    ui->view_PionBlanc->setIconSize( QSize( 43 , 43 ) );
    ui->view_Histo->setIconSize(QSize(20,20));
    ui->view_Histo_2->setIconSize(QSize(20,20));

    // Initialisation du premier visuel de la matrice
    this->RefreshMatrice(this);

    connect(ui->actionRegles, SIGNAL(triggered()), this, SLOT(actRegle()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(actDarkMode()));
    connect(ui->actionLight, SIGNAL(triggered()), this, SLOT(actLightMode()));
    connect(ui->actionDocumentation_Code_Source, SIGNAL(triggered()), this , SLOT(actDocumentation()));
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() { delete ui; }

/**
 * @brief MainWindow::RefreshMatrice
 * @param parent
 */
void
MainWindow::RefreshMatrice(QWidget *parent)
{
    model = new QStandardItemModel(8,8,parent) ;

    for ( int i = 0 ; i < 8 ; i++ )
        for ( int j = 0 ; j < 8 ; j++ )
        {
            if ( e.getPiece( j + 1 , i + 1 ) != nullptr )
                SetImage( QPixmap ( ConvertToChar( e.getPiece( j + 1 , i + 1 )->path() ) ), i , j , model);

            QColor myColor = ( i % 2 == j % 2 ?  QColor (103,159,90, 150) : QColor (225, 206, 154, 150) ) ;

            setColorBackGround( myColor, i , j , model);

            if (  e.getPiece(j+1, i+1) != nullptr && e.getPiece( j + 1 , i + 1 )->isEchec() )
                setColorBackGround( QColor ( "darkRed" ), i , j , model);
        }

    QPixmap monImage = ( WhitePlay ? QPixmap ( ":/img_blanc/assets/blanc/pion.png" ) : QPixmap ( ":/img_noir/assets/noir/pion.png" ) );

    ui->TourLabel->setAlignment( Qt::AlignCenter );
    ui->TourLabel->setPixmap( monImage );

    ui->tableViewEchiquier->setModel( model );
    ui->tableViewEchiquier->setIconSize( QSize( 90 , 90 ) );
}

/**
 * @brief MainWindow::on_tableViewEchiquier_clicked
 * @param index
 */
void
MainWindow::on_tableViewEchiquier_clicked(const QModelIndex &index)
{
    QVariant selectedCell      = model->data( index, Qt::BackgroundRole );
    QColor colorOfSelectedCell = selectedCell.value<QColor>();

    if ( pieceEnCours != nullptr && pieceEnCours->isWhite() == WhitePlay && colorOfSelectedCell.value() == 255 )
    {
        if ( ( ( WhitePlay ) && ( xRoiBlanc != index.column()+1 || yRoiBlanc != index.row()+1 ) ) || ( !WhitePlay ) && ( xRoiNoir != index.column() + 1 || yRoiNoir != index.row() + 1 ) )
        {
            if ( xRoiNoir == index.column()+1 && yRoiNoir == index.row()+1 ) xRoiNoir = 0;
            if ( xRoiBlanc == index.column()+1 && yRoiBlanc == index.row()+1 ) xRoiBlanc = 0;

            if ( pieceEnCours->x() == xRoiNoir && pieceEnCours->y() == yRoiNoir )
            {
                xRoiNoir = index.column()+1;
                yRoiNoir = index.row()+1;
            }
            else if (  pieceEnCours->x() == xRoiBlanc && pieceEnCours->y() == yRoiBlanc )
            {
                xRoiBlanc = index.column()+1;
                yRoiBlanc = index.row()+1;
            }

            if (xRoiNoir == 0 || xRoiBlanc == 0)
            {
                this->RefreshMatrice(this);
                windowEnd = new stop(this);
                cout << "Fin de game" << endl;
                windowEnd->show();
            }

            if ( WhitePlay == true)
            {
                if ( e.getPiece( index.column() + 1 , index.row() + 1 ) != nullptr )
                {
                   imagesPiecesMangeesBlanc.push_back( e.getPiece( index.column() + 1 , index.row() + 1 )->path() );
                   displayEatPieces(imagesPiecesMangeesBlanc,true);
                }
            }
            else if ( e.getPiece( index.column() + 1 , index.row() + 1 ) != nullptr )
                {
                    imagesPiecesMangeesNoir.push_back( e.getPiece( index.column() + 1 , index.row() + 1 )->path() );
                    displayEatPieces(imagesPiecesMangeesNoir,false);
                }

            AddToHistory(pieceEnCours, index.column()+1 , index.row()+1);
            e.deplacer( pieceEnCours , index.column()+1  , index.row()+1 );

            if ( WhitePlay )
            {
               if ( e.getPiece( xRoiBlanc , yRoiBlanc )->isEchec() )  e.getPiece( xRoiBlanc , yRoiBlanc )->setIsEchec();
               this->setColor( pieceEnCours->AfficheMouvementValide( e , WhitePlay ) );

               if ( this->Echec( xRoiNoir , yRoiNoir ) )
               {
                   bool isEchecMat = this->IsEchecMat( pieceEnCours->MouvementPossibleRoi( e , xRoiNoir , yRoiNoir ) );

                   if ( isEchecMat )
                   {
                       cout << "Echec et mat" << endl;
                       //Fin de partie
                   }
                   e.getPiece( xRoiNoir , yRoiNoir )->setIsEchec();
               }
            }
            else
            {
                if ( e.getPiece( xRoiNoir , yRoiNoir )->isEchec() )  e.getPiece( xRoiNoir , yRoiNoir )->setIsEchec();
                this->setColor( pieceEnCours->AfficheMouvementValide(e,WhitePlay));

                if ( this->Echec( xRoiBlanc , yRoiBlanc ) )
                {
                    bool isEchecMat = this->IsEchecMat( pieceEnCours->MouvementPossibleRoi( e , xRoiBlanc , yRoiBlanc ) );

                    if ( isEchecMat )
                    {
                        cout << "Echec et mat" << endl;
                    }
                    e.getPiece( xRoiBlanc , yRoiBlanc )->setIsEchec();
                }
            }

            WhitePlay = !WhitePlay;
            this->RefreshMatrice(this);
        }
    }
    else
    {
        pieceEnCours = e.getPiece(  index.column()+1  , index.row()+1 );
        this->RefreshMatrice(this);
        if ( pieceEnCours != nullptr ) this->setColor( pieceEnCours->AfficheMouvementValide(e,WhitePlay) );
    }
}

/**
 * @brief MainWindow::setColor
 * @param values
 */
void
MainWindow::setColor(list<string>values)
{
   for (string coordonees : values)
   {
       std::vector<std::string> seglist = SplitString( coordonees, '-');

       try {
           QColor color = ( seglist.at(2) == "true" ? QColor (255,0,255, 255) : QColor (116,208,255, 255) );
           QModelIndex index = model->index( std::stoi( seglist.at(1) ) , std::stoi( seglist.at(0) ) ,QModelIndex());
           model->setData(index, QColor( color ), Qt::BackgroundRole  );
       }  catch (...) {}
   }
   ui->tableViewEchiquier->setModel(model);
}

/**
 * @brief MainWindow::Echec
 * @param x
 * @param y
 * @return
 */
bool
MainWindow::Echec ( int x , int y)
{
    QModelIndex index = model->index( y - 1,x - 1 , QModelIndex() );
    QVariant selectedCell      = model->data( index, Qt::BackgroundRole );
    QColor colorOfSelectedCell = selectedCell.value<QColor>();

    return ( colorOfSelectedCell.value() == 255 ? true : false );
}

/**
 * @brief MainWindow::IsEchecMat
 * @param values
 * @return
 */
bool
MainWindow::IsEchecMat( list<string> values)
{
    bool isEchecMat = true;
    for (string coordonees : values)
    {
        std::vector<std::string> seglist = SplitString( coordonees, '-');

        isEchecMat = this->Echec( std::stoi( seglist.at( 0 ) ) , std::stoi( seglist.at(1) ) ) ;
        if ( !isEchecMat )  break;
    }
    return isEchecMat;
}

/**
 * @brief MainWindow::displayEatPieces
 * @param PiecesEated
 * @param white
 */
void
MainWindow::displayEatPieces(list<string> PiecesEated, bool white)
{
    QStandardItemModel *monModel = new QStandardItemModel(1, 16) ;
    int i = 0;

    for (string path : PiecesEated)
    {     
        SetImage( QPixmap ( ConvertToChar( path ) ) , 0 , i , monModel);
        i++;
    }

    if ( white )
        ui->view_PionBlanc->setModel(monModel);
    else
       ui->view_PionNoir->setModel(monModel);
}

void
MainWindow::AddToHistory(Piece* laPiece,int x, int y )
{
   History.push_back(  std::to_string( laPiece->x() ) + ":" + std::to_string( laPiece->y() )  + " -> ");
   HistoryPictures.push_back( laPiece->path() );

   HistoryEat.push_back( std::to_string( x )  + ":" +  std::to_string( y ) );

   if ( e.getPiece( x , y ) != nullptr )
   {
       HistoryPicturesEat.push_back( e.getPiece( x , y )->path() );
   }
   else
   {
       HistoryPicturesEat.push_back( ":/img/assets/invisible.png" );
   }

   QStandardItemModel* Histo = new QStandardItemModel(this);
   QStandardItemModel* HistoEat = new QStandardItemModel(this);
   int i = 0;

   for (string text : History)
   {
        QPixmap monImage( ConvertToChar( HistoryPictures.at( i ) ) );
        SetImage( monImage , i , 0 , Histo);

        QModelIndex index = Histo->index( i,0 , QModelIndex() );
        Histo->setData(index, ConvertToChar( text ) );

        i++;
   }

   i = 0;
   for (string text : HistoryEat)
   {
          QPixmap monImage2( ConvertToChar( HistoryPicturesEat.at( i ) ) );

          cout << ConvertToChar( HistoryPicturesEat.at( i ) ) << endl;
          cout << ConvertToChar(":/img_blanc/assets/blanc/roi.png") << endl;

          if ( *ConvertToChar(":/img_blanc/assets/blanc/roi.png") == *ConvertToChar( HistoryPicturesEat.at( i ) ) )
          {
             SetImage( monImage2 , i , 0 , HistoEat);
          }
          else
          {
             SetImage( monImage2 , i , 0 , HistoEat);
          }

          QModelIndex index2 = HistoEat->index( i,0 , QModelIndex() );
          HistoEat->setData(index2, ConvertToChar( text ) );
          i++;
   }

   ui->view_Histo->setModel(Histo);
   ui->view_Histo_2->setModel(HistoEat);
}

const char *
MainWindow::ConvertToChar(string monText)
{
    char const *char_array = monText.c_str();
    return char_array;
}

void
MainWindow::setColorBackGround(QColor color ,int i, int j ,QStandardItemModel* model)
{
    QModelIndex index = model->index( i , j , QModelIndex() );
    model->setData( index, QBrush ( color ), Qt::BackgroundRole  );
}

void
MainWindow::SetImage ( QPixmap monImage, int i , int j, QStandardItemModel* model)
{
    QIcon* m_icon = new QIcon();
    m_icon->addPixmap(monImage);

    QStandardItem *m_item = new QStandardItem();
    m_item->setIcon(*m_icon);

    model->setItem( i, j , m_item );
}

std::vector<std::string>
MainWindow::SplitString( string word, char split)
{
    std::stringstream wordStream(word);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(wordStream, segment, split))
    {
       seglist.push_back( segment );
    }
    return seglist;
}

/**
 * @brief MainWindow::actRegle
 */
void
MainWindow::actRegle() { system("start /max https://ecole.apprendre-les-echecs.com/regles-echecs/"); }

/**
 * @brief MainWindow::actDarkMode
 */
void
MainWindow::actDarkMode()
{
    this->setStyleSheet("background-color: rgb(88, 88, 88);");
    ui->tableViewEchiquier->setStyleSheet("background-color: rgb(212, 212, 212);");
    ui->groupBox->setStyleSheet("background-color: rgb(212, 212, 212);");
    ui->view_PionBlanc->setStyleSheet("background-color: rgb(212, 212, 212);");
    ui->view_PionNoir->setStyleSheet("background-color: rgb(212, 212, 212);");
}

/**
 * @brief MainWindow::actLightMode
 */
void
MainWindow::actLightMode()
{
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->tableViewEchiquier->setStyleSheet("");
    ui->groupBox->setStyleSheet("");
    ui->view_PionBlanc->setStyleSheet("");
    ui->view_PionNoir->setStyleSheet("");
}

/**
 * @brief MainWindow::actDocumentation
 */
void
MainWindow::actDocumentation() { }

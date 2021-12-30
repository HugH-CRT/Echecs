/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de MainWindow
 * @file mainwindow.cpp
 * @date 26/10/2021
 * @version 0.8.5
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "Player.h"
#include <iostream>
#include <assert.h>
#include "mainwindow.h"
#include "upgradepawn.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QString>
#include <vector>
#include <string>
#include <sstream>
#include <QStringListModel>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>

using namespace std;

/**
 * @brief Builder of the game page, initialize the game
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ActFenetreDefault();
    timer = new QTimer(this);
    connect ( timer , SIGNAL( timeout() ), this, SLOT( SetTimer() ) );

    assert( playerWhite.PlacePieces( e ) );
    assert( playerBlack.PlacePieces( e ) );

    // Initialisation image pour le premier coup
    QPixmap monImage(":/img/white/assets/white/pawn.png");
    ui->TourLabel->setAlignment(Qt::AlignCenter);
    ui->TourLabel->setPixmap(monImage);

    ui->view_PionNoir->setIconSize( QSize( 43 , 43 ) );
    ui->view_PionBlanc->setIconSize( QSize( 43 , 43 ) );
    ui->view_Histo->setIconSize(QSize(20,20));
    ui->view_Histo_2->setIconSize(QSize(20,20));

    // Initialisation du premier visuel de la matrice
    this->RefreshMatrix(this);

    connect(ui->actionRegles, SIGNAL(triggered()), this, SLOT(ActRegle()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(ActDarkMode()));
    connect(ui->actionLight, SIGNAL(triggered()), this, SLOT(ActLightMode()));
    connect(ui->actionDocumentation_Code_Source, SIGNAL(triggered()), this , SLOT(ActDocumentation()));
    connect(ui->actionDefault, SIGNAL(triggered()), this, SLOT(ActFenetreDefault()));
    connect(ui->actionFullscreen, SIGNAL(triggered()), this, SLOT(ActFenetreFullscreen()));
    connect(ui->actionFullFenetrer, SIGNAL(triggered()), this, SLOT(ActFenetreFullFenetrer()));
    connect(ui->actionFrancais, SIGNAL(triggered()), this, SLOT(ActLangueFrancais()));
    connect(ui->actionAnglais, SIGNAL(triggered()), this, SLOT(ActLangueAnglais()));
    connect(ui->actionAllemand, SIGNAL(triggered()), this, SLOT(ActLangueRusse()));
    connect(ui->actionEspagnol, SIGNAL(triggered()), this, SLOT(ActLangueEspagnol()));


    timer->start();
}

/**
 * @brief Game Page Destroyer
 */
MainWindow::~MainWindow() { delete ui; }

/**
 * @brief Refreshes the game board after each move
 * @param parent
 */
void
MainWindow::RefreshMatrix(QWidget *parent)
{
    model = new QStandardItemModel(8,8,parent) ;

    for ( int i = 0 ; i < 8 ; i++ )
        for ( int j = 0 ; j < 8 ; j++ )
        {
            if ( e.GetPiece( j + 1 , i + 1 ) != nullptr )
                SetPicture( QPixmap ( ConvertToChar( e.GetPiece( j + 1 , i + 1 )->GetPath() ) ), i , j , model);

            QColor myColor = ( i % 2 == j % 2 ?  QColor (103,159,90, 150) : QColor (225, 206, 154, 150) ) ;

            SetColorBackGround( myColor, i , j , model);

            if (  e.GetPiece(j+1, i+1) != nullptr && e.GetPiece( j + 1 , i + 1 )->GetIsEchec() )
                SetColorBackGround( QColor ( "darkRed" ), i , j , model);
        }

    QPixmap monImage = ( whitePlay ? QPixmap ( ":/img/white/assets/white/pawn.png" ) : QPixmap ( ":/img/black/assets/black/pawn.png" ) );

    ui->TourLabel->setAlignment( Qt::AlignCenter );
    ui->TourLabel->setPixmap( monImage );

    ui->tableViewEchiquier->setModel( model );
    ui->tableViewEchiquier->setIconSize( QSize( 90 , 90 ) );
}

/**
 * @brief Method called on the click of a cell
 * @param &index -> Index of the selected cell
 */
void
MainWindow::on_tableViewEchiquier_clicked(const QModelIndex &index)
{
    QVariant selectedCell      = model->data( index, Qt::BackgroundRole );
    QColor colorOfSelectedCell = selectedCell.value<QColor>();

    if ( currentPiece != nullptr && currentPiece->GetIsWhite() == whitePlay && colorOfSelectedCell.value() == 255 )
    {
        if ( ( ( whitePlay ) && ( xWhiteKing != index.column()+1 || yWhiteKing != index.row()+1 ) ) || ( !whitePlay ) && ( xBlackKing != index.column() + 1 || yBlackKing != index.row() + 1 ) )
        {
            if ( xBlackKing == index.column()+1 && yBlackKing == index.row()+1 ) xBlackKing = 0;
            if ( xWhiteKing == index.column()+1 && yWhiteKing == index.row()+1 ) xWhiteKing = 0;

            if ( currentPiece->GetX() == xBlackKing && currentPiece->GetY() == yBlackKing )
            {
                xBlackKing = index.column()+1;
                yBlackKing = index.row()+1;
            }
            else if (  currentPiece->GetX() == xWhiteKing && currentPiece->GetY() == yWhiteKing )
            {
                xWhiteKing = index.column()+1;
                yWhiteKing = index.row()+1;
            }

            if (xBlackKing == 0 || xWhiteKing == 0)
            {
                this->RefreshMatrix(this);
                timer->stop();
                EndGameDisplay();
            }

            if ( whitePlay == true)
            {
                if ( e.GetPiece( index.column() + 1 , index.row() + 1 ) != nullptr )
                {
                   picturesEatedWhitePieces.push_back( e.GetPiece( index.column() + 1 , index.row() + 1 )->GetPath() );
                   DisplayEatPieces(picturesEatedWhitePieces,true);
                }
            }
            else if ( e.GetPiece( index.column() + 1 , index.row() + 1 ) != nullptr )
            {
                picturesEatedBlackPieces.push_back( e.GetPiece( index.column() + 1 , index.row() + 1 )->GetPath() );
                DisplayEatPieces(picturesEatedBlackPieces,false);
            }

            AddToHistory(currentPiece, index.column()+1 , index.row()+1);
            //Part for the castling
                if ( currentPiece->GetIsWhite() )
                {
                    if ( dynamic_cast<King*>(currentPiece) != nullptr && currentPiece->GetX() + 2 == index.column() + 1 )
                    {
                      e.MovePiece( e.GetPiece( 8 , 1 ) , 6 , 1 );
                    }
                    else if ( dynamic_cast<King*>(currentPiece) != nullptr && currentPiece->GetX() - 2 == index.column() + 1 )
                    {
                        e.MovePiece( e.GetPiece( 1 , 1 ) , 4 , 1 );
                    }
                }
                else
                {
                    if ( dynamic_cast<King*>(currentPiece) != nullptr && currentPiece->GetX() + 2 == index.column() + 1 )
                    {
                      e.MovePiece( e.GetPiece( 8 , 8 ) , 6 , 8 );
                    }
                    else if ( dynamic_cast<King*>(currentPiece) != nullptr && currentPiece->GetX() - 2 == index.column() + 1 )
                    {
                        e.MovePiece( e.GetPiece( 1 , 8 ) , 4 , 8 );
                    }
                }
            //
            e.MovePiece( currentPiece , index.column()+1  , index.row()+1 );

            if ( whitePlay )
            {
               if ( e.GetPiece( xWhiteKing , yWhiteKing )->GetIsEchec() )  e.GetPiece( xWhiteKing , yWhiteKing )->SetIsEchec();
               this->SetColor( currentPiece->DisplayAvailableMovement( e , whitePlay ) );

               if ( this->Echec( xBlackKing , yBlackKing ) )
               {
                   bool isEchecMat = this->IsEchecMat( currentPiece->CheckAvailableMovementKing( e , xBlackKing , yBlackKing ) );

                   if ( isEchecMat )
                   {
                       //Fin de partie
                   }
                   e.GetPiece( xBlackKing , yBlackKing )->SetIsEchec();
               }
            }
            else
            {
                if ( e.GetPiece( xBlackKing , yBlackKing )->GetIsEchec() )
                     e.GetPiece( xBlackKing , yBlackKing )->SetIsEchec();

                this->SetColor( currentPiece->DisplayAvailableMovement(e,whitePlay));

                if ( this->Echec( xWhiteKing , yWhiteKing ) )
                {
                    bool isEchecMat = this->IsEchecMat( currentPiece->CheckAvailableMovementKing( e , xWhiteKing , yWhiteKing ) );

                    if ( isEchecMat )
                    {
                       //  cout << "Echec et mat" << endl;
                    }
                    e.GetPiece( xWhiteKing , yWhiteKing )->SetIsEchec();
                }
            }

            whitePlay = !whitePlay;
            this->RefreshMatrix(this);

            if ( dynamic_cast<Pawn*>(currentPiece) != nullptr && ( index.row()+1 == 8 || index.row()+1 == 1 ) )
            {
                UpgradePawn pageUpgrade( this , currentPiece->GetIsWhite() );
                pageUpgrade.setModal( true );
                pageUpgrade.exec();
            }
        }
    }
    else
    {
        currentPiece = e.GetPiece(  index.column()+1  , index.row()+1 );
        this->RefreshMatrix(this);

        if ( currentPiece != nullptr )
        {
            Piece *maPiece = this->DoomTheKing();

            if ( maPiece == nullptr )
            {
                if ( dynamic_cast<King*>(currentPiece) != nullptr )
                {
                    this->SetColor( this->WithdrawUnacceptedMoveKing( currentPiece->DisplayAvailableMovement(e,whitePlay) ) );
                    this->SetColorForCastling();
                }
                else
                  this->SetColor( currentPiece->DisplayAvailableMovement(e,whitePlay) );
            }
            else if ( maPiece != currentPiece )
            {
                if ( currentPiece->Deplace( e , maPiece->GetX() , maPiece->GetY() ) )
                {
                    list<string> values;
                    if ( dynamic_cast<Queen*>(currentPiece) != nullptr )
                    {
                        Bishop monFou = Bishop( currentPiece->GetX() , currentPiece->GetY() , currentPiece->GetIsWhite() , true ,true , "" );
                        Piece* PieceFou = &monFou;
                        values = this->RoadToAttack( maPiece->GetX() , maPiece->GetY(), PieceFou );

                        if ( values.size() == 1)
                        {
                            Rook maTour   = Rook( currentPiece->GetX(), currentPiece->GetY(), currentPiece->GetIsWhite() , true , true , "" );
                            Piece* PieceTour = &maTour;
                            values = this->RoadToAttack( maPiece->GetX() , maPiece->GetY(), PieceTour );
                        }
                    }
                    else
                    {
                       values = this->RoadToAttack( maPiece->GetX() , maPiece->GetY(), currentPiece );

                    }
                    this->SetColor( values );
                }
            }
        }
    }
}

list<string>
MainWindow::WithdrawUnacceptedMoveKing(list<string> values)
{
    list<string> acceptedMovement;

    for (string coordonees : values)
    {
        try {
            bool availableMovement = true;
            std::vector<std::string> seglist = SplitString( coordonees, '-');
            int y = std::stoi( seglist.at(1) ) + 1;
            int x = std::stoi( seglist.at(0) ) + 1;

            for ( int j = 0; j < 64 ; j++ )
                if ( e.GetTab()[j] != nullptr && e.GetTab()[j]->GetIsWhite() !=  currentPiece->GetIsWhite() )
                {
                    if ( dynamic_cast<Pawn*>( e.GetTab()[j] ) == nullptr )
                    {
                        if ( e.GetTab()[j]->Deplace( e , x , y ) )
                        {
                            availableMovement = false;
                            break;
                        }
                    }
                    else
                    {
                        if (  e.GetTab()[j]->GetIsWhite() && ( e.GetTab()[j]->GetX() + 1 == x && e.GetTab()[j]->GetY() + 1 == y || e.GetTab()[j]->GetX() - 1 == x && e.GetTab()[j]->GetY() + 1 == y ) )
                        {
                            availableMovement = false;
                            break;
                        }
                        else if ( !e.GetTab()[j]->GetIsWhite() && ( e.GetTab()[j]->GetX() - 1 == x && e.GetTab()[j]->GetY() - 1 == y || e.GetTab()[j]->GetX() + 1 == x && e.GetTab()[j]->GetY() - 1 == y ) )
                        {
                            availableMovement = false;
                            break;
                        }
                    }
                }


            if ( availableMovement )
               acceptedMovement.push_back( std::to_string( x - 1 ) + "-" + std::to_string( y - 1 ) + "-" + seglist.at(2) );

        }  catch (...) {}
    }
    return acceptedMovement;
}

Piece*
MainWindow::DoomTheKing()
{
    int tamponX;
    int tamponY;
    bool end = false;
    int nbAttaquant = 0;
    int coordonneeXAttaquant;
    int coordonneeYAttaquant;
    list<int> values;

    for ( int j = 0; j < 64 ; j++ )
        if ( e.GetTab()[j] != nullptr )
            if ( e.GetTab()[j]->GetIsWhite() != currentPiece->GetIsWhite() && dynamic_cast<Knight*>(e.GetTab()[j]) == nullptr )
            {
                values.clear();
                if ( e.GetTab()[j]->Deplace( e , currentPiece->GetX() , currentPiece->GetY() ) && dynamic_cast<Queen*>(e.GetTab()[j]) == nullptr )
                {
                    values = test( e.GetTab()[j] ) ;
                }
                else if ( dynamic_cast<Queen*>(e.GetTab()[j]) != nullptr )
                {
                    Bishop monFou = Bishop( e.GetTab()[j]->GetX() , e.GetTab()[j]->GetY() , e.GetTab()[j]->GetIsWhite() , true ,true , "" );
                    Piece* PieceFou = &monFou;

                    if ( monFou.Deplace( e , currentPiece->GetX() , currentPiece->GetY() ) )
                        values = test( PieceFou ) ;

                    Rook maTour   = Rook( e.GetTab()[j]->GetX(), e.GetTab()[j]->GetY(), e.GetTab()[j]->GetIsWhite() , true , true , "" );
                    Piece* PieceTour = &maTour;

                    if ( maTour.Deplace( e ,currentPiece->GetX() , currentPiece->GetY() ) )
                    {
                       list<int> result = test( PieceTour );
                       if ( result.size() > 0 )
                           values = result;
                    }
                }
                nbAttaquant += values.size() / 2;

                if ( values.size() != 0 )
                {
                     auto it = values.begin();

                     std::advance(it, 0);
                     coordonneeXAttaquant = *it;

                     std::advance(it, 1);
                     coordonneeYAttaquant = *it;
                }
            }

    if ( nbAttaquant == 0 )     { return e.GetPiece( 0 , 0 ); }
    else if ( nbAttaquant == 1 ){ return e.GetPiece( coordonneeXAttaquant , coordonneeYAttaquant ); }
    else                        { return e.GetPiece( currentPiece->GetX() , currentPiece->GetY() ); }
}

list<int>
MainWindow::test( Piece* maPiece )
{
    int nbAttaquant = 0;
    int tamponX = maPiece->GetX();
    int tamponY = maPiece->GetY();
    list<int> values;
    bool tourVertical = false;
    bool tourHorizontal = false;
    bool diagHGFou = false;
    bool diagHDFou = false;
    bool diagBGFou = false;
    bool diagBDFou = false;

    if( dynamic_cast<Rook*>( maPiece ) != nullptr )
    {
        if ( maPiece->GetY() != currentPiece->GetY() &&  maPiece->GetX() == currentPiece->GetX() )
        {
            tourVertical = true;
        }
        else
            tourHorizontal = true;
    }
    else if ( dynamic_cast<Bishop*>( maPiece ) != nullptr )
    {
         if ( maPiece->GetX() > currentPiece->GetX() && maPiece->GetY() > currentPiece->GetY() ) { diagBDFou = true; }
         else if ( maPiece->GetX() > currentPiece->GetX() && maPiece->GetY() < currentPiece->GetY() ) { diagHDFou = true; }
         else if ( maPiece->GetX() < currentPiece->GetX() && maPiece->GetY() < currentPiece->GetY() ) { diagHGFou = true; }
         else if ( maPiece->GetX() < currentPiece->GetX() && maPiece->GetY() > currentPiece->GetY() ) { diagBGFou = true; }
    }

    maPiece->SetX( currentPiece->GetX() );
    maPiece->SetY( currentPiece->GetY() );

    if ( currentPiece->GetIsWhite() )
    {
        nbAttaquant += test2( xWhiteKing , yWhiteKing, maPiece , tourVertical,tourHorizontal, diagHGFou, diagHDFou , diagBGFou , diagBDFou );
    }
    else
        nbAttaquant += test2( xBlackKing , yBlackKing, maPiece, tourVertical,tourHorizontal , diagHGFou, diagHDFou , diagBGFou , diagBDFou );

    maPiece->SetX( tamponX );
    maPiece->SetY( tamponY );

    if ( nbAttaquant != 0 )
    {
         values.push_back( maPiece->GetX() );
         values.push_back( maPiece->GetY() );
    }
    return values;
}

int
MainWindow::test2(int x, int y, Piece* maPiece, bool tourVertical, bool tourHorizontal, bool diagHGFou, bool diagHDFou, bool diagBGFou, bool diagBDFou )
{
    int nbAttaquant = 0;
    if ( maPiece->Deplace( e , x , y ) )
    {
        if ( tourVertical && x == maPiece->GetX() )                         { nbAttaquant++; }
        else if ( tourHorizontal && y == maPiece->GetY() )                  { nbAttaquant++; }
        else if ( diagHGFou && maPiece->GetX() < x && maPiece->GetY() < y ) { nbAttaquant++; }
        else if ( diagHDFou && maPiece->GetX() > x && maPiece->GetY() < y ) { nbAttaquant++; }
        else if ( diagBGFou && maPiece->GetX() < x && maPiece->GetY() > y ) { nbAttaquant++; }
        else if ( diagBDFou && maPiece->GetX() > x && maPiece->GetY() > y ) { nbAttaquant++; }
        else { nbAttaquant++; }
    }
    return nbAttaquant;
}

list<string>
MainWindow::RoadToAttack( int x , int y, Piece* maPiece )
{
    list<string> values =  maPiece->DisplayAvailableMovement( e , whitePlay );;
    list<string> result;

    if ( dynamic_cast<Rook*>( maPiece ) != nullptr )
    {
        for (string coordonees : values)
        {
            std::vector<std::string> seglist = SplitString( coordonees, '-');
            try
            {
                if ( maPiece->GetX() == x )
                {
                    if (  std::stoi( seglist.at( 0 ) ) + 1  == x )
                        result.push_back( seglist.at( 0 ) + "-" +  seglist.at( 1 ) + "-false" );
                }
                else
                    if (  std::stoi( seglist.at( 1 ) ) + 1 == y )
                        result.push_back( seglist.at( 0 ) + "-" + seglist.at( 1 ) + "-false" );
            }  catch (...) {}

        }
    }
    else if ( dynamic_cast<Bishop*>( maPiece ) != nullptr )
        for (string coordonees : values)
            try
            {
                std::vector<std::string> seglist = SplitString( coordonees, '-');

                if ( maPiece->GetX() < x && maPiece->GetY() < y || maPiece->GetX() > x && maPiece->GetY() > y )
                {
                    if ( std::stoi( seglist.at(0) ) + 1 < x && std::stoi( seglist.at(1) ) + 1 < y  || std::stoi( seglist.at(0) ) + 1 > x && std::stoi( seglist.at(1) ) + 1 > y || std::stoi( seglist.at(0) ) + 1 == x && std::stoi( seglist.at(1) ) + 1 == y)
                        result.push_back( seglist.at( 0 ) + "-" + seglist.at( 1 ) + "-false" );
                }
                else if ( maPiece->GetX() < x && maPiece->GetY() > y || maPiece->GetX() > x && maPiece->GetY() < y )
                    if ( std::stoi( seglist.at(0) ) + 1 < x && std::stoi( seglist.at(1) ) + 1 > y  || std::stoi( seglist.at(0) ) + 1 > x && std::stoi( seglist.at(1) ) + 1 < y  || std::stoi( seglist.at(0) ) + 1 == x && std::stoi( seglist.at(1) ) + 1 == y )
                        result.push_back( seglist.at( 0 ) + "-" + seglist.at( 1 ) + "-false" );
            } catch (...) {}

    result.push_back( std::to_string( x - 1 ) + "-" + std::to_string( y - 1 )+ "-true" );
    return result;
}


void
MainWindow::receiveData( int value )
{
    if ( value == 1 )
    {
        Rook *myRook = new Rook(currentPiece->GetX(), currentPiece->GetY(),currentPiece->GetIsWhite(),true, true, currentPiece->GetIsWhite() ? ":/img/white/assets/white/rook.png" : ":/img/black/assets/black/rook.png" );
        e.MovePiece(myRook,currentPiece->GetX() , currentPiece->GetY());
    }
    else if (value == 2 )
    {
        Bishop * myBishop = new Bishop(currentPiece->GetX(), currentPiece->GetY(),currentPiece->GetIsWhite(),true, true, currentPiece->GetIsWhite() ? ":/img/white/assets/white/bishop.png" : ":/img/black/assets/black/bishop.png" );
        e.MovePiece(myBishop,currentPiece->GetX() , currentPiece->GetY());
    }
    else if ( value == 3 )
    {
        Knight* myKnight = new Knight(currentPiece->GetX(), currentPiece->GetY(),currentPiece->GetIsWhite(),true, true, currentPiece->GetIsWhite() ? ":/img/white/assets/white/knight.png" : ":/img/black/assets/black/knight.png" );
        e.MovePiece(myKnight,currentPiece->GetX() , currentPiece->GetY());
    }
    else
    {
        Queen* myQueen = new Queen(currentPiece->GetX(), currentPiece->GetY(),currentPiece->GetIsWhite(),true, true, currentPiece->GetIsWhite() ? ":/img/white/assets/white/queen.png" : ":/img/black/assets/black/queen.png" );
        e.MovePiece(myQueen,currentPiece->GetX() , currentPiece->GetY());
    }

    this->RefreshMatrix(this);
}

void
MainWindow::SetColorForCastling()
{
    list<string> values;
    if ( dynamic_cast<Rook*>( e.GetPiece(8,1) ) != nullptr && e.GetPiece(8,1)->GetIsWhite() == currentPiece->GetIsWhite() )
        if ( currentPiece->CastlingAvailable( e , e.GetPiece(8,1) , currentPiece ) )
            values.push_back("6-0-true");

    if ( dynamic_cast<Rook*>( e.GetPiece(1,1) ) != nullptr && e.GetPiece(1,1)->GetIsWhite() == currentPiece->GetIsWhite() )
        if ( currentPiece->CastlingAvailable( e , e.GetPiece(1,1) , currentPiece ) )
           values.push_back("2-0-true");

    if ( dynamic_cast<Rook*>( e.GetPiece(8,8) ) != nullptr && e.GetPiece(8,8)->GetIsWhite() == currentPiece->GetIsWhite() )
        if ( currentPiece->CastlingAvailable( e , e.GetPiece(8,8) , currentPiece ) )
            values.push_back("6-7-true");

    if ( dynamic_cast<Rook*>( e.GetPiece(1,8) ) != nullptr && e.GetPiece(1,8)->GetIsWhite() == currentPiece->GetIsWhite() )
        if ( currentPiece->CastlingAvailable( e , e.GetPiece(1,8) , currentPiece ) )
            values.push_back("2-7-true");

    this->SetColor(values);
}

/**
 * @brief Assigns the colors light blue or pink for the valid cells retrieved by the list as a parameter
 * @param list <string> values ​​-> List of all the coordinates of the cells valid for the movements of the selected part.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
 */
void
MainWindow::SetColor(list<string>values)
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

bool
MainWindow::Echec( int x , int y )
{
    QModelIndex index = model->index( y - 1,x - 1 , QModelIndex() );
    QVariant selectedCell      = model->data( index, Qt::BackgroundRole );
    QColor colorOfSelectedCell = selectedCell.value<QColor>();

    return ( colorOfSelectedCell.value() == 255 ? true : false );
}

/**
 * @brief Checks if in the list of valid boxes for the King's movements, one of the cells is not colored.
 *        Clarification: At this time of execution the possible movements of the piece which defeated the king are colored.
 * @param list <string> values ​​-> List of all the coordinates of the cells valid for the displacements of the king in failure.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
 * @return bool -> Determine if the king is checkmate.
 */
bool
MainWindow::IsEchecMat( list<string> values )
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
 * @brief Displays the pieces eaten
 * @param list <string> PiecesEated -> list of the image paths of the pieces eaten.
 * @param bool white -> Determine if this list is displayed for the white player or the black player.
 */
void
MainWindow::DisplayEatPieces( list<string> PiecesEated, bool white )
{
    QStandardItemModel *monModel = new QStandardItemModel(1, 16) ;
    int i = 0;

    for (string path : PiecesEated)
    {     
        SetPicture( QPixmap ( ConvertToChar( path ) ) , 0 , i , monModel);
        i++;
    }

    if ( white )
        ui->view_PionBlanc->setModel(monModel);
    else
       ui->view_PionNoir->setModel(monModel);
}

/**
 * @brief Adds the movements performed to the movement history and updates the associated visual.
 * @param Piece* laPiece -> The piece that has just performed a movement
 * @param int x -> coordinate of the column of the cell targeted by the movement
 * @param int y -> coordinate of the cell line targeted by the movement
 */
void
MainWindow::AddToHistory( Piece* laPiece,int x, int y )
{
   History.push_back(  std::to_string( laPiece->GetX() ) + ":" + std::to_string( laPiece->GetY() )  + " -> ");
   HistoryPictures.push_back( laPiece->GetPath() );

   HistoryEat.push_back( std::to_string( x )  + ":" +  std::to_string( y ) );

   if ( e.GetPiece( x , y ) != nullptr )
   {
       HistoryPicturesEat.push_back( e.GetPiece( x , y )->GetPath() );
   }
   else
   {
       HistoryPicturesEat.push_back( ":/img/assets/invisible.png" );
   }

   QStandardItemModel* Histo = new QStandardItemModel(this);
   QStandardItemModel* HistoEat = new QStandardItemModel(this);

   int indexLign = 0;
   for (int i = History.size() - 1 ; i > - 1 ; i--)
   {
        QPixmap monImage( ConvertToChar( HistoryPictures.at( i ) ) );
        SetPicture( monImage , indexLign , 0 , Histo);

        QModelIndex index = Histo->index( indexLign,0 , QModelIndex() );
        Histo->setData(index, ConvertToChar( History.at( i ) ) );
        indexLign++;

   }
   indexLign = 0;

   for (int i = HistoryEat.size() - 1 ; i > - 1 ; i--)
   {
          QPixmap monImage2( ConvertToChar( HistoryPicturesEat.at( i ) ) );
          SetPicture( monImage2 , indexLign , 0 , HistoEat);

          QModelIndex index2 = HistoEat->index( indexLign,0 , QModelIndex() );
          HistoEat->setData(index2, ConvertToChar( HistoryEat.at(i) ) );
          indexLign++;
   }

   ui->view_Histo->setModel(Histo);
   ui->view_Histo_2->setModel(HistoEat);
}

/**
 * @brief Convert the text passed as a parameter to type char
 * @param string monText -> Text to convert
 * @return const char * -> Pointer to converted text
 */
const char *
MainWindow::ConvertToChar( string monText )
{
    char const *char_array = monText.c_str();
    return char_array;
}

/**
 * @brief Assigns the color, to the index cell, of the model provided as a parameter
 * @param QColor color -> color to assign
 * @param int i -> coordinate of the column of the cell targeted by the movement
 * @param int j -> coordinate of the cell line targeted by the movement
 * @param QStandardItemModel* model * -> Model on which applied the modifications
 */
void
MainWindow::SetColorBackGround( QColor color ,int i, int j ,QStandardItemModel* model )
{
    QModelIndex index = model->index( i , j , QModelIndex() );
    model->setData( index, QBrush ( color ), Qt::BackgroundRole  );
}

/**
 * @brief Assigns the image, to the index cell, of the model provided as a parameter
 * @param QColor color -> color to assign
 * @param int i -> coordinate of the column of the cell targeted by the movement
 * @param int j -> coordinate of the cell line targeted by the movement
 * @param QStandardItemModel* model * -> Model on which applied the modifications
 */
void
MainWindow::SetPicture ( QPixmap monImage, int i , int j, QStandardItemModel* model )
{
    QIcon* m_icon = new QIcon();
    m_icon->addPixmap(monImage);

    QStandardItem *m_item = new QStandardItem();
    m_item->setIcon(*m_icon);

    model->setItem( i, j , m_item );
}

/**
 * @brief Split a word according to the specified character
 * @param string word -> word to split
 * @param char split -> separation character
 * @return std::vector<std::string> seglist -> split list
 */
std::vector<std::string>
MainWindow::SplitString( string word, char split )
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
 * @brief Open the game rules documentation
 */
void
MainWindow::ActRegle() { system("start /max https://ecole.apprendre-les-echecs.com/regles-echecs/"); }

/**
 * @brief Switch the app to dark mode
 */
void
MainWindow::ActDarkMode()
{
    this->setStyleSheet("background-color: rgb(88, 88, 88);");
    ui->tableViewEchiquier->setStyleSheet("background-color: rgb(212, 212, 212);");
    ui->groupBox->setStyleSheet("background-color: rgb(212, 212, 212);");
    ui->view_PionBlanc->setStyleSheet("background-color: rgb(212, 212, 212);");
    ui->view_PionNoir->setStyleSheet("background-color: rgb(212, 212, 212);");
}

/**
 * @brief Switch the application to clear mode
 */
void
MainWindow::ActLightMode()
{
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->tableViewEchiquier->setStyleSheet("");
    ui->groupBox->setStyleSheet("");
    ui->view_PionBlanc->setStyleSheet("");
    ui->view_PionNoir->setStyleSheet("");
}

/**
 * @brief Open the application documentation
 */
void
MainWindow::ActDocumentation() { }

void
MainWindow::ShowTime()
{
    QTime time = QTime(Hours,minutes,seconds) ;
    QString time_text = time.toString("hh:mm:ss");
    ui->lcdTimer->display( (time_text) );
}

void
MainWindow::SetTimer()
{
   timer->setInterval(1000);
   seconds++;

   if ( seconds == 60 )
   {
       seconds = 0;
       minutes++;
   }
   if ( minutes == 60 )
   {
       Hours++;
       minutes = 0;
   }
   ShowTime();
}
/**
 * @brief MainWindow::EndGameDisplay
 */
void
MainWindow::EndGameDisplay()
{
    this->RefreshMatrix(this);
    QMessageBox::StandardButton endDisplay = QMessageBox::information( this, "Chess",
                                                                       tr("END GAME \n"),
                                                                       QMessageBox::Ok,
                                                                       QMessageBox::Ok);
    if (endDisplay != QMessageBox::Ok) {
        // ok boomer
    } else {
        this->close();
        ui->tableViewEchiquier->setEnabled(false);
    }
}

/**
 * @brief MainWindow::closeEvent
 * @param event
 */
void
MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Chess",
                                                                tr("Are you sure ? \n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();

    } else {
        event->accept();
    }
}

/**
 * @brief MainWindow::ActFenetreDefault
 */
void
MainWindow::ActFenetreDefault()
{
    this->setMaximumSize(1080, 950);
    this->setGeometry(420, 30, 1080, 950);
}

/**
 * @brief MainWindow::ActFenetreFullscreen
 */
void
MainWindow::ActFenetreFullscreen()
{
    this->setMaximumSize(1920,1080);
    this->setGeometry(0, 0, 1920, 1080);
}

/**
 * @brief MainWindow::ActFenetreFullFenetrer
 */
void
MainWindow::ActFenetreFullFenetrer()
{
    this->setMaximumSize(1920,1080);
    this->setGeometry(0, 30, 1920, 1050);
}

/**
 * @brief MainWindow::ActLangueFrancais
 */
void
MainWindow::ActLangueFrancais(){}

/**
 * @brief MainWindow::ActLangueAnglais
 */
void
MainWindow::ActLangueAnglais(){}

/**
 * @brief MainWindow::ActLangueAllemand
 */
void
MainWindow::ActLangueAllemand(){}

/**
 * @brief MainWindow::ActLangueRusse
 */
void
MainWindow::ActLangueRusse(){}

/**
 * @brief MainWindow::ActLangueEspagnol
 */
void
MainWindow::ActLangueEspagnol(){}



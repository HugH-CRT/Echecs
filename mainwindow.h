/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de MainWindow
 * @file mainwindow.h
 * @date 26/10/2021
 * @version 0.8.5
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QTimer>

#include "ChessBoard.h"
#include "Player.h"
#include "Piece.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow( QWidget *parent = nullptr );
        ~MainWindow();

        void RefreshMatrix( QWidget* );
        void SetColor( list<string> );
        bool Echec ( int, int );
        bool IsEchecMat( list<string> );
        void DisplayEatPieces( list<string>, bool );
        void AddToHistory( Piece*, int, int );
        const char* ConvertToChar(  string );
        void SetColorBackGround( QColor, int , int , QStandardItemModel* );
        void SetPicture ( QPixmap , int, int, QStandardItemModel* );
        std::vector<std::string> SplitString( string, char );
        void EndGameDisplay();
        void closeEvent(QCloseEvent *event);
        void SetColorForCastling();
        Piece* DoomTheKing();
        list<string> WithdrawUnacceptedMoveKing(list<string> values);

    private slots:
        void on_tableViewEchiquier_clicked( const QModelIndex &index );
        void ActRegle();
        void ActDarkMode();
        void ActLightMode();
        void ActDocumentation();
        void ShowTime();
        void SetTimer();

public slots:
        void receiveData( int value );

private:
        Ui::MainWindow *ui;
        QStandardItemModel *model;
        ChessBoard e;
        PlayerWhite playerWhite;
        PlayerBlack  playerBlack;
        Piece *currentPiece = nullptr;
        int xBlackKing = 5;
        int yBlackKing = 8;
        int xWhiteKing = 5;
        int yWhiteKing = 1;
        bool whitePlay = true;
        list<string> picturesEatedWhitePieces;
        list<string> picturesEatedBlackPieces;
        std::vector<string> History;
        std::vector<string> HistoryPictures;
        std::vector<string> HistoryEat;
        std::vector<string> HistoryPicturesEat;
        int Hours = 0;
        int minutes = 0;
        int seconds = 0;
        QTimer *timer ;
};

#endif

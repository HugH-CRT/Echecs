/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de MainWindow
 * @file mainwindow.h
 * @date 26/10/2021
 * @version 1.0
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDialogButtonBox>
#include <QCloseEvent>

#include "Echiquier.h"
#include "Joueur.h"
#include "Piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void RefreshMatrice(QWidget *parent);
        void setColor( list<string>mlist );
        bool Echec ( int x , int y);
        bool IsEchecMat( list<string> );
        void displayEatPieces(list<string>,bool);
        void AddToHistory(Piece*,int,int);
        const char* ConvertToChar(string);
        void setColorBackGround(QColor, int , int ,QStandardItemModel*);
        void SetImage ( QPixmap , int, int, QStandardItemModel*);
        std::vector<std::string> SplitString( string, char);
        void EndGameDisplay();

    private slots:
        void on_tableViewEchiquier_clicked(const QModelIndex &index);
        void actRegle();
        void actDarkMode();
        void actLightMode();
        void actDocumentation();
        void showTime();
        void setTimer();
        void closeEvent(QCloseEvent *event);

private:
        Ui::MainWindow *ui;
        QStandardItemModel *model;
        Echiquier e;
        JoueurBlanc jb;
        JoueurNoir  jn;
        Piece *pieceEnCours = nullptr;
        int xRoiNoir = 5;
        int yRoiNoir = 8;
        int xRoiBlanc = 5;
        int yRoiBlanc = 1;
        bool WhitePlay = true;
        list<string> imagesPiecesMangeesBlanc;
        list<string> imagesPiecesMangeesNoir;
        std::vector<string> History;
        std::vector<string> HistoryPictures;
        std::vector<string> HistoryEat;
        std::vector<string> HistoryPicturesEat;
        int Heures = 0;
        int minutes = 0;
        int secondes = 0;
        QTimer *timer ;

};

#endif

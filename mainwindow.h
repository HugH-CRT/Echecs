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

    private slots:
        void on_tableViewEchiquier_clicked(const QModelIndex &index);

private:
        Ui::MainWindow *ui;
        QStandardItemModel *model;
        Echiquier e;
        JoueurBlanc jb;
        JoueurNoir  jn;
        Piece *pieceEnCours = nullptr;
        Piece *RoiBlanc;
        Piece *RoiNoir;
        bool WhitePlay = true;
};

#endif

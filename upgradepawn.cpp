#include "upgradepawn.h"
#include "ui_upgradepawn.h"
#include <iostream>

using namespace  std;

UpgradePawn::UpgradePawn(QWidget *parent,bool isWhite ) :
    QDialog(parent),
    ui(new Ui::UpgradePawn)
{
    ui->setupUi(this);
    connect( this ,SIGNAL( sendData(int) ), parent, SLOT( receiveData(int) ) );
    ui->pieceUpgrade->setIconSize( QSize( 110 , 200 ) );

    if (isWhite)
    {
        SetPicture( QPixmap ( ":/img/white/assets/white/rook.png" ) , 0 , 0 , monModel);
        SetPicture( QPixmap ( ":/img/white/assets/white/bishop.png" ) , 0 , 1 , monModel);
        SetPicture( QPixmap ( ":/img/white/assets/white/knight.png" ) , 0 , 2 , monModel);
        SetPicture( QPixmap ( ":/img/white/assets/white/queen.png" ) , 0 , 3 , monModel);
    }
    else
    {
        SetPicture( QPixmap ( ":/img/black/assets/black/rook.png" ) , 0 , 0 , monModel);
        SetPicture( QPixmap ( ":/img/black/assets/black/bishop.png" ) , 0 , 1 , monModel);
        SetPicture( QPixmap ( ":/img/black/assets/black/knight.png" ) , 0 , 2 , monModel);
        SetPicture( QPixmap ( ":/img/black/assets/black/queen.png" ) , 0 , 3 , monModel);
    }


    ui->pieceUpgrade->setModel(monModel);
}

/**
 * @brief Assigns the image, to the index cell, of the model provided as a parameter
 * @param QColor color -> color to assign
 * @param int i -> coordinate of the column of the cell targeted by the movement
 * @param int j -> coordinate of the cell line targeted by the movement
 * @param QStandardItemModel* model * -> Model on which applied the modifications
 */
void
UpgradePawn::SetPicture ( QPixmap monImage, int i , int j, QStandardItemModel* model )
{
    QIcon* m_icon = new QIcon();
    m_icon->addPixmap(monImage);

    QStandardItem *m_item = new QStandardItem();
    m_item->setIcon(*m_icon);

    model->setItem( i, j , m_item );
}

UpgradePawn::~UpgradePawn()
{
    delete ui;
}

void UpgradePawn::on_pieceUpgrade_doubleClicked(const QModelIndex &index)
{
     emit sendData( index.column() + 1  );
     this->close();
}


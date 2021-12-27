#ifndef UPGRADEPAWN_H
#define UPGRADEPAWN_H

#include <QDialog>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class UpgradePawn; }
QT_END_NAMESPACE

class UpgradePawn : public QDialog
{
    Q_OBJECT

public:
    explicit UpgradePawn(QWidget *parent = nullptr, bool iswhite = true);
    ~UpgradePawn();
    void SetPicture ( QPixmap , int, int, QStandardItemModel* );

private slots:
    void on_pieceUpgrade_doubleClicked(const QModelIndex &index);

signals:
    void sendData( int value );

private:
    Ui::UpgradePawn *ui;
    QStandardItemModel *monModel = new QStandardItemModel(1, 4) ;
};

#endif // UPGRADEPAWN_H

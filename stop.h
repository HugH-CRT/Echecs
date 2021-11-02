#ifndef STOP_H
#define STOP_H

#include <QDialog>

namespace Ui {
class stop;
}

class stop : public QDialog
{
    Q_OBJECT

public:
    explicit stop(QWidget *parent = nullptr);
    ~stop();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::stop *ui;
};

#endif // STOP_H

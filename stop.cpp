#include "stop.h"
#include "ui_stop.h"

/**
 * @brief stop::stop
 * @param parent
 */
stop::stop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stop)
{
    ui->setupUi(this);
}

/**
 * @brief stop::~stop
 */
stop::~stop()
{
    delete ui;
}

/**
 * @brief stop::on_buttonBox_accepted
 */
void
stop::on_buttonBox_accepted()
{
    // Fermer application
}


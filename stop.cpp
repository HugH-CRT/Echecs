#include "stop.h"
#include "ui_stop.h"

/**
 * @brief Constructeur de la page de fin
 * @param parent
 */
stop::stop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stop)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de l'UI
 */
stop::~stop() { delete ui; }

/**
 * @brief Méthode appellée sur le clic du bouton fermer, ferme la fenêtre
 */
void
stop::on_buttonBox_accepted() { this->close(); }


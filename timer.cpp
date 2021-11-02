#include "timer.h"
#include <QTimer>

/**
 * @brief timer::timer
 */
timer::timer(QWidget *parent): QLCDNumber(parent)

{
    // initialise la valeur du compteur de tic d’horloge
    m_valeur = 0;
    // instancie le timer (base de temps) de l’horloge
    m_timer = new QTimer(this);

    setDigitCount(5); /* Qt5 */

    // connecte le signal d’expiration (timeout) d’une période (top d’horloge) au slot tic()
    connect(m_timer, SIGNAL(timeout()), this, SLOT(tic()));
}

/**
 * @brief timer::~timer
 */
timer::~timer()
{
}

/**
 * @brief timer::getMinute
 * @return
 */
long
timer::getMinute()
{
    return (m_valeur%36000)/600;
}

/**
 * @brief timer::getHeure
 * @return
 */
long
timer::getHeure()
{
    return m_valeur/36000;
}

/**
 * @brief timer::fixer
 * @param h
 * @param m
 */
void
timer::fixer(int h, int m)
{
    m_valeur = h*36000 + m*600;
}

/**
 * @brief timer::update
 * @return
 */
QString
timer::update()
{
    QString heure, minute;
    // met à jour l’affichage de l’horloge
    if (getHeure() < 10)
    heure = "0" + QString::number(getHeure());
    else heure = QString::number(getHeure());
    if (getMinute() < 10)
    minute = "0" + QString::number(getMinute());
    else minute = QString::number(getMinute());
    QString text = heure + ":" + minute;
    return text;
}

/**
 * @brief timer::tic
 */
void
timer::tic()
{
    // incrémente le compteur de top d’horloge
    m_valeur++;
    // demande la mise à jour l’affichage de l’horloge
    update();
}

/**
 * @brief timer::demarrer
 */
void
timer::demarrer()
{
    m_timer->start(0);
}

/**
 * @brief timer::arreter
 */
void
timer::arreter()
{
    m_timer->stop();
}

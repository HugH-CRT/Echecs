#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QWidget>
#include <QtWidgets/QLCDNumber>

class timer: public QLCDNumber
{
public:
    timer(QWidget *parent=0);
    ~timer();

    long getMinute();
    long getHeure();
    void fixer(int h, int m);
    QString update();

    private:
    QTimer *m_timer;
    long m_valeur;


    private slots:
    void tic();

    public slots:
    void demarrer();
    void arreter();

};

#endif // TIMER_H

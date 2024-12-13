#include "mainview.h"
#include "ui_mainview.h"

class MainViewPrivate
{
    friend class MainView;
};

MainView::MainView(QWidget *parent)
    : IView(parent)
    , ui(new Ui::MainView)
    , d(new MainViewPrivate)
{
    ui->setupUi(this);
}

MainView::~MainView()
{
    if(ui)
    {
        delete ui;
        ui = nullptr;
    }
    if(d)
    {
        delete d;
        d = nullptr;
    }
}

void MainView::moveEvent(QMoveEvent *event)
{
    //
}

void MainView::resizeEvent(QResizeEvent *event)
{
    //
}

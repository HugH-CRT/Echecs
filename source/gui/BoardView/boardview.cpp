#include "boardview.h"
#include "ui_boardview.h"

class BoardViewPrivate
{
    friend class BoardView;
};

BoardView::BoardView(QWidget *parent)
    : IView(parent)
    , ui(new Ui::BoardView)
    , d(new BoardViewPrivate)
{
    ui->setupUi(this);
}

BoardView::~BoardView()
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

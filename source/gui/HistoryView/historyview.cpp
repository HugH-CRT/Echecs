#include "historyview.h"
#include "ui_historyview.h"

class HistoryViewPrivate
{
    friend class HistoryView;
};

HistoryView::HistoryView(QWidget *parent)
    : IView(parent)
    , ui(new Ui::HistoryView)
    , d(new HistoryViewPrivate)
{
    ui->setupUi(this);
}

HistoryView::~HistoryView()
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

#include "upgradeview.h"
#include "ui_upgradeview.h"

class UpgradeViewPrivate
{
    friend class UpgradeView;
};

UpgradeView::UpgradeView(QWidget *parent)
    : IView(parent)
    , ui(new Ui::UpgradeView)
    , d(new UpgradeViewPrivate)
{
    ui->setupUi(this);
}

UpgradeView::~UpgradeView()
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

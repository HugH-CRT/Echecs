#ifndef UPGRADEVIEW_H
#define UPGRADEVIEW_H

#include "IView.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class UpgradeView; }
QT_END_NAMESPACE

class UpgradeViewPrivate;

class UpgradeView final : public IView<QWidget>
{
    Q_OBJECT

public:
    explicit UpgradeView(QWidget* parent = nullptr);
    ~UpgradeView() override;

private:
    Ui::UpgradeView* ui = nullptr;
    UpgradeViewPrivate* d = nullptr;
    friend class UpgradeViewPrivate;
};

#endif // UPGRADEVIEW_H

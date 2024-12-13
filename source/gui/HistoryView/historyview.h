#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include "IView.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class HistoryView; }
QT_END_NAMESPACE

class HistoryViewPrivate;

class HistoryView final : public IView<QWidget>
{
    Q_OBJECT

public:
    explicit HistoryView(QWidget* parent = nullptr);
    ~HistoryView() override;

private:
    Ui::HistoryView* ui = nullptr;
    HistoryViewPrivate* d = nullptr;
    friend class HistoryViewPrivate;
};

#endif // HISTORYVIEW_H

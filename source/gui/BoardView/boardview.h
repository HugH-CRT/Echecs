#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "IView.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class BoardView; }
QT_END_NAMESPACE

class BoardViewPrivate;

class BoardView final : public IView<QWidget>
{
    Q_OBJECT

public:
    explicit BoardView(QWidget* parent = nullptr);
    ~BoardView() override;

private:
    Ui::BoardView* ui = nullptr;
    BoardViewPrivate* d = nullptr;
    friend class BoardViewPrivate;
};

#endif // BOARDVIEW_H

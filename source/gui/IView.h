#ifndef IVIEW_H
#define IVIEW_H

#include <QMainWindow>
#include <QDialog>

template<typename TypeHerit>
class IView : public TypeHerit
{
    static_assert(std::is_base_of<QWidget, TypeHerit>::value, "TypeHerit must be a QWidget or QMainWindow or QDialog");

public:
    explicit IView(QWidget *parent = nullptr) : TypeHerit(parent) {}
    virtual ~IView() = default;
};

#endif // IVIEW_H

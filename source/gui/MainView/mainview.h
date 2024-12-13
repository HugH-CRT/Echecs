#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "IView.h"

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainViewPrivate;

class MainView final : public IView<QMainWindow>
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent = nullptr);
    ~MainView() override;

private:
    Ui::MainView* ui = nullptr;
    MainViewPrivate* d = nullptr;
    friend class MainViewPrivate;

    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

#if WITH_MULTI_LANGUAGE
private:
    // Language
    QTranslator _translator;
    QString _currentLanguage;
    void createMenuLanguages(void);
    void switchLanguage(QTranslator& translator, const QString& language);
    void loadLanguage(const QString& language);
    //
private slots:
    void slotLanguageChanged(QAction* action);
#endif // WITH_MULTI_LANGUAGE

};

#endif // MAINVIEW_H

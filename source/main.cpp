#include "define.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationDisplayName(APP_NAME" "+APP_VERSION_QSTR);
    app.setApplicationVersion(APP_VERSION_QSTR);

    return app.exec();
}

#include "loginwidget.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWidget *loginWidget = new LoginWidget;
    loginWidget->show();

    return app.exec();
}

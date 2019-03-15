#include "mainwidget.h"
#include <QFontDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/font/FontAwesome");

    MainWidget w;
    w.show();

    return a.exec();
}

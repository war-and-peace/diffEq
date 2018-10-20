#include "mainwindow.h"
#include <QApplication>
#include "mproblem.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.showMaximized();
    return a.exec();
}

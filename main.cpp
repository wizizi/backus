#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStartDragDistance(10);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}

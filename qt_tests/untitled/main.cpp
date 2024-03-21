#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Dialog d;
    d.setModal(true);
    d.show();
    return a.exec();
}

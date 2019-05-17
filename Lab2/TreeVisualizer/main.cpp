#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

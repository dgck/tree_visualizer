#ifndef UICREATOR_H
#define UICREATOR_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>

class MainWindow;

class UiCreator//:public QObject
{
    //Q_OBJECT
public:
    UiCreator();
    UiCreator(QMainWindow*MainWindow);

    QLayout* CreateStartWidgets();
    QLayout* CreateTree();
    QLayout* CreateButtonsForTwoTrees();
private:
    QMainWindow*wnd;
};

#endif // UICREATOR_H

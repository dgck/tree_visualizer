#include "uicreator.h"
#include <QComboBox>
#include <QPushButton>
UiCreator::UiCreator()
{
    this->wnd = nullptr;
}

UiCreator::UiCreator(QMainWindow *MainWindow)
{
    this->wnd = MainWindow;
}

QLayout *UiCreator::CreateStartWidgets()
{
    QVBoxLayout*mainLayout = new QVBoxLayout;
    QComboBox*trees = new QComboBox;
    trees->addItem("RbTree");
    trees->addItem("BTree");
    trees->addItem("B+Tree");
    trees->addItem("SplayTree");
    trees->addItem("OBSTTree");
    QPushButton*createTrees = new QPushButton("Create new tree");
    //connect(createTrees,&QPushButton::clicked,wnd,&MainWindow::DrawImage);
    mainLayout->addWidget(trees);
    mainLayout->addWidget(createTrees);
    return mainLayout;
}


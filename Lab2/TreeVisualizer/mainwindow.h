#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tree.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_op1Btn_clicked();

    void on_op2Btn_clicked();

    void on_quitBtn_clicked();

    void on_insertBtn_clicked();

    void on_createBtn_clicked();

    void on_prevStep_clicked();

    void on_nextStep_clicked();

    void ShowImageGV();

private:
    Ui::MainWindow *ui;

    int index = 0;

    Tree*tree;
};

#endif // MAINWINDOW_H

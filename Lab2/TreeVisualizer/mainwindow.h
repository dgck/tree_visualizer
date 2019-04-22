#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RBTree.h"
#include <string>
#include <QTimer>

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

    void ShowSequenceOfImages();

    void DrawImage(const string&);
    void ShowStep(int new_index,int &current_index);
    void on_removeBtn_clicked();

private:
    Ui::MainWindow *ui;

    int overal_number_of_steps;
    int index_of_current_step;

    Tree*tree;

    const int TimePerStep;

    QTimer timer;
};

#endif // MAINWINDOW_H

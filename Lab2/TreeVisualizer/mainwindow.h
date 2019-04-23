#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RBTree.h"
#include <string>
#include <QTimer>
#include "imagewriter.h"

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

    void DrawImage(const int&w,const int&h,const QPixmap&pix);

    void on_removeBtn_clicked();

    void on_removeTreeBtn_clicked();

private:
    Ui::MainWindow *ui;

    Tree*tree;

    ImageWriter *writer;
};

#endif // MAINWINDOW_H

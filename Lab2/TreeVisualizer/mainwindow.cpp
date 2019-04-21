#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::ShowImageGV(){
    QImage *img = new QImage("graph.png");
    QPixmap pix(QPixmap::fromImage(*img));
    int w = pix.width();
    int h = pix.height();
    ui->image->resize(w,h);
    ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_op1Btn_clicked()
{

}

void MainWindow::on_op2Btn_clicked()
{

}

void MainWindow::on_quitBtn_clicked()
{
    QApplication::quit();
}

void MainWindow::on_insertBtn_clicked()
{
    tree->insert();
    ShowImageGV();
}

void MainWindow::on_createBtn_clicked()
{
}

void MainWindow::on_prevStep_clicked()
{


}

void MainWindow::on_nextStep_clicked()
{

}

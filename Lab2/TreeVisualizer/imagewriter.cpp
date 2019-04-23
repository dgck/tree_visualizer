#include "imagewriter.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QImage>

ImageWriter::ImageWriter():TimePerStep(1000)
{
    overal_number_of_steps = 0;
    index_of_current_step = 0;
}

void ImageWriter::ShowSequenceOfImages()
{
    index_of_current_step = overal_number_of_steps;

    int new_number_of_steps;
    QFile file("meta.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream read(&file);

        read >> new_number_of_steps;
        qDebug()<<new_number_of_steps;
    }
    else
    {
        new_number_of_steps = 0;
    }
    overal_number_of_steps = new_number_of_steps;

    connect(&timer,&QTimer::timeout,this,[=](){ShowStep(new_number_of_steps,this->index_of_current_step);});
    timer.start(TimePerStep);
    file.close();
}

void ImageWriter::ShowStep(int new_index, int &current_index)
{
    if(current_index!=new_index)
    {
        string filename = "step_" + QString::number(current_index).toStdString() + ".png";
        CreateImage(filename);
        current_index++;
    }
    else
    {
        timer.stop();
        disconnect(&timer,&QTimer::timeout,this,nullptr);
    }
    if(current_index == new_index)
    {
        current_index--;
        if(timer.isActive())
        {
            timer.stop();
            disconnect(&timer,&QTimer::timeout,this,nullptr);
        }
    }
}

bool ImageWriter::is_writing()
{
    return timer.isActive();
}

void ImageWriter::WritePrevStep()
{
    if(index_of_current_step - 1 >= 0)
    {
        string filename = "step_" + QString::number(--index_of_current_step).toStdString() + ".png";
        CreateImage(filename);
    }
}

void ImageWriter::WriteNextStep()
{
    if(index_of_current_step + 1 < overal_number_of_steps)
    {
        string filename = "step_" + QString::number(++index_of_current_step).toStdString() + ".png";
        CreateImage(filename);
    }
}

void ImageWriter::ResetSteps()
{
    DeleteImageFiles();

    overal_number_of_steps = index_of_current_step = 0;
    if(timer.isActive())
        timer.stop();
    QFile("meta.txt").remove();
}

void ImageWriter::DeleteImageFiles()
{
    for (int i = 0; i < overal_number_of_steps; i++)
    {
        string filenamePng = "step_" + QString::number(i).toStdString() + ".png";
        string filenameGv = "gr" + QString::number(i).toStdString() + ".dot";
        QFile(filenamePng.c_str()).remove();
        QFile(filenameGv.c_str()).remove();
    }
}

void ImageWriter::CreateImage(const string &filename)
{
    QImage *img = new QImage(filename.c_str());
    qDebug()<<filename.c_str();
    QPixmap pix(QPixmap::fromImage(*img));
    int w = pix.width();
    int h = pix.height();
    emit SendPictureInfo(w,h,pix);
}

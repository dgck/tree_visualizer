#include "imagewriter.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QImage>
#include "Trees/tree.h"

ImageWriter::ImageWriter(QCGView*view,Tree*tree):TimePerStep(1000)
{
    overal_number_of_steps = 0;
    index_of_current_step = 0;
    this->tree = tree;

    this->view = view;
}

void ImageWriter::ShowSequenceOfImages()
{
    index_of_current_step = overal_number_of_steps;

    int new_number_of_steps = tree->getScenes().size();

    overal_number_of_steps = new_number_of_steps;

    connect(&timer,&QTimer::timeout,this,[=](){ShowStep(new_number_of_steps,this->index_of_current_step);});
    timer.start(TimePerStep);
    //file.close();
}

void ImageWriter::ShowStep(int new_index, int &current_index)
{
    if(current_index!=new_index)
    {
        CreateImage(tree->getScenes()[current_index]);
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
        CreateImage(tree->getScenes()[--index_of_current_step]);
    }
}

void ImageWriter::WriteNextStep()
{
    if(index_of_current_step + 1 < overal_number_of_steps)
    {
        CreateImage(tree->getScenes()[++index_of_current_step]);
    }
}

void ImageWriter::ResetSteps()
{
    overal_number_of_steps = index_of_current_step = 0;
    tree = nullptr;
    if(timer.isActive())
        timer.stop();
}

void ImageWriter::SetNewTree(Tree *tree)
{
    ResetSteps();
    this->tree = tree;
}

void ImageWriter::CreateImage(QGraphicsScene*scene)
{
    emit SendPictureInfo(view,scene);
}

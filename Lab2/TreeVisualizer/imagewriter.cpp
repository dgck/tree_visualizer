#include "imagewriter.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QImage>
#include "Trees/tree.h"

ImageWriter::ImageWriter(QCGView*view,Tree*tree):TimePerStep(1500)
{
    overal_number_of_steps = 0;
    index_of_current_step = 0;
    this->tree = tree;

    this->view = view;
}

void ImageWriter::ShowSequenceOfImages(bool isTraversal)
{
    index_of_current_step = overal_number_of_steps;

    int new_number_of_steps;

    if(isTraversal)
        new_number_of_steps = tree->getTraversalScenes().size();
    else
        new_number_of_steps = tree->getScenes().size();

    overal_number_of_steps = new_number_of_steps;

    connect(&timer,&QTimer::timeout,this,[=](){ShowStep(new_number_of_steps,this->index_of_current_step,isTraversal);});
    timer.start(TimePerStep);
}

void ImageWriter::ShowStep(int new_index, int &current_index,bool isTraversal)
{
    if(current_index!=new_index)
    {
        if(isTraversal)
            CreateImage(tree->getTraversalScenes()[current_index]);
        else
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

void ImageWriter::WritePrevStep(bool isTraversal)
{
    if(index_of_current_step - 1 >= 0)
    {
<<<<<<< HEAD
        if(isTraversal)
            CreateImage(tree->getTraversalScenes()[--index_of_current_step]);
        else
            CreateImage(tree->getScenes()[--index_of_current_step]);
=======
        CreateImage(tree->getScenes()[--index_of_current_step]);
>>>>>>> 1752b595cf58ed30bd44acbaab9b135f5bf79428
    }
}

void ImageWriter::WriteNextStep(bool isTraversal)
{
    if(index_of_current_step + 1 < overal_number_of_steps)
    {
<<<<<<< HEAD
        if(isTraversal)
            CreateImage(tree->getTraversalScenes()[++index_of_current_step]);
        else
            CreateImage(tree->getScenes()[++index_of_current_step]);
=======
        CreateImage(tree->getScenes()[++index_of_current_step]);
>>>>>>> 1752b595cf58ed30bd44acbaab9b135f5bf79428
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

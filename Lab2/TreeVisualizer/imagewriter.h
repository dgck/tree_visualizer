#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <string>
#include <QTimer>
#include <string>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsScene>
#include <vector>
#include "qcgview.h"
class Tree;
using std::string;
using std::vector;
/*
 *
 создать интерфес Визуализатор
 создать для каждого дерева свой Визуализатор
 (для каждого дерева существует отдельный визуализатор который живет пока живет само деревот е пок ане нажнем деллит / поменяет тип дерева)

 что он делает:
 читать дерево, создавать сцену с отримованным деревом, сохранять сцену
 поддерживать массив из кьюграфиксвью и давать доступ к этому массив классу ImageWriter

 // У дерева будет визуализатор - т е его спецификация
 Визуализатор живет вместе со своим деревом
*/
/*!
    \brief Class which creates sequence of graphic scenes and sends it to the mainwindow
    \author Stas Dzunza
    \version 1.0
    \date May 2019

    At the beginning he receives tree with array of scenes and every time sends one of the scenes
    to the mainwindow
*/
class ImageWriter:public QObject
{
    Q_OBJECT
public:
    ImageWriter(QCGView*view,Tree*tree = nullptr);

    /*!
        *\brief Main method which starts timer and updates number of scenes every time
    */
    void ShowSequenceOfImages(bool isTraversal = false);

    void ShowStep(int new_index,int &current_index,bool isTraversal = false);

    /*!
        *\brief Method which sends previously scene to the mainwindow
    */
    void WritePrevStep(bool isTraversal = false);

    /*!
        *\brief Method which resets all information about current tree and their states
    */
    void WriteNextStep(bool isTraversal = false);

    /*!
        *\brief Method which sends on of the scenes to the mainwindow
    */
    void CreateImage(QGraphicsScene*scene);

    /*!
        *\brief Method which checks if writer is writing at the moment
    */
    bool is_writing();

    /*!
        *\brief Method which sends next scene to the mainwindow
    */
    void ResetSteps();

    /*!
        *\brief Method which sets new tree to this writer
    */
    void SetNewTree(Tree*tree);

    /*!
        *\brief Method which sends last step to the mainwindow
    */
    void ShowLastStep();





    ////////////////////////////////////////////////////////////////////////////////////////

    /*!
        *\brief Main method which starts timer and updates number of scenes every time
    */
    void ShowSequenceOfImagesBfsDfs();

    void ShowStepBfsDfs(int new_index,int &current_index);

    /*!
        *\brief Method which sends previously scene to the mainwindow
    */
    void WritePrevStepBfsDfs();

    /*!
        *\brief Method which resets all information about current tree and their states
    */
    void WriteNextStepBfsDfs();

    /*!
        *\brief Method which checks if writer is writing at the moment
    */

    void setTimeInterval(int timePerStep);

signals:
    /*!
        \brief Signal which sends a scene
    */
    void SendPictureInfo(QCGView*view,QGraphicsScene*scene);

private:
    int overal_number_of_steps;///< number of scenes
    int index_of_current_step;///< index of scene which we see at the moment
    int TimePerStep;///< constant time after what we send a scene
    QTimer timer;///< after every timeout of this timer we send a scene
    QCGView*view;///< view from the mainwindow(receive in constructor)
    Tree*tree;///< tree which have a scenes(receive in constructor)
};

#endif // IMAGEWRITER_H

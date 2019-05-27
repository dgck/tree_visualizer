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
class ImageWriter:public QObject
{
    Q_OBJECT
public:
    ImageWriter(QCGView*view,Tree*tree = nullptr);

    void ShowSequenceOfImages(bool isTraversal = false);
    void CreateImage(QGraphicsScene*scene);
    void ShowStep(int new_index,int &current_index,bool isTraversal = false);
    bool is_writing();
    void WritePrevStep(bool isTraversal = false);
    void WriteNextStep(bool isTraversal = false);
    void ResetSteps();
    void DeleteImageFiles();
    void SetNewTree(Tree*tree);

signals:
    void SendPictureInfo(QCGView*view,QGraphicsScene*scene);

private:
    int overal_number_of_steps;
    int index_of_current_step;
    const int TimePerStep;
    QTimer timer;
    QCGView*view;
    Tree*tree;
};

#endif // IMAGEWRITER_H

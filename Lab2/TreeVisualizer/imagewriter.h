#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <string>
#include <QTimer>
#include <string>
#include <QPixmap>
#include <QLabel>

using std::string;
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
    ImageWriter(QLabel*image);

    void ShowSequenceOfImages();
    void CreateImage(const string&);
    void ShowStep(int new_index,int &current_index);
    bool is_writing();
    void WritePrevStep();
    void WriteNextStep();
    void ResetSteps();
    void DeleteImageFiles();

signals:
    void SendPictureInfo(const int&w,const int&h,const QPixmap&pix,QLabel*image);

private:
    int overal_number_of_steps;
    int index_of_current_step;
    const int TimePerStep;
    QTimer timer;
    QLabel*image;
};

#endif // IMAGEWRITER_H

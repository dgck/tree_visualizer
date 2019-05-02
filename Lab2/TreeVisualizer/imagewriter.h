#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <string>
#include <QTimer>
#include <string>
#include <QPixmap>
#include <QLabel>

using std::string;

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

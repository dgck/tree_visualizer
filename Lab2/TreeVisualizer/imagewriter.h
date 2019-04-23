#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <string>
#include <QTimer>
#include <string>
#include <QPixmap>

using std::string;

class ImageWriter:public QObject
{
    Q_OBJECT
public:
    ImageWriter();

    void ShowSequenceOfImages();
    void CreateImage(const string&);
    void ShowStep(int new_index,int &current_index);
    bool is_writing();
    void WritePrevStep();
    void WriteNextStep();
    void ResetSteps();
    void DeleteImageFiles();

signals:
    void SendPictureInfo(const int&w,const int&h,const QPixmap&pix);

private:
    int overal_number_of_steps;
    int index_of_current_step;
    const int TimePerStep;
    QTimer timer;
};

#endif // IMAGEWRITER_H

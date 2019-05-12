#ifndef QCGVIEW_H
#define QCGVIEW_H

#include <QGraphicsView>

class QCGView : public QGraphicsView
{
    Q_OBJECT
public:
    QCGView(QWidget* parent);
    void fitInView_fixed(const QRectF &rect, Qt::AspectRatioMode aspectRatioMode);


protected:
    virtual void wheelEvent(QWheelEvent* event);
};

#endif // QCGVIEW_H

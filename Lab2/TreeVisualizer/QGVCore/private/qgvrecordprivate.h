#ifndef QGVRECORDPRIVATE_H
#define QGVRECORDPRIVATE_H

#include "QGVNodePrivate.h"

#include <graphviz/cgraph.h>

class QGVRecordPrivate : public QGVNodePrivate
{
public:
    QGVRecordPrivate(Agnode_t *node, Agraph_t *parent)
        : QGVNodePrivate(node, parent)
    {

    }
};



#endif // QGVRECORDPRIVATE_H

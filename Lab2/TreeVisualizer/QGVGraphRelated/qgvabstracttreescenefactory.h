#ifndef QGVABSTRACTTREESCENEFACTORY_H
#define QGVABSTRACTTREESCENEFACTORY_H

#include "Trees/tree.h"
#include "QGVScene.h"
#include "commons.h"

class QGVAbstractTreeSceneFactory
{
public:
    QGVAbstractTreeSceneFactory(shared_ptr <Tree> obj)
        :   m_obj(obj)
    {

    }

    virtual void run() = 0;

private:
    shared_ptr <Tree> m_obj;
    shared_ptr <QGVScene> m_scene;
};

#endif // QGVABSTRACTTREESCENEFACTORY_H

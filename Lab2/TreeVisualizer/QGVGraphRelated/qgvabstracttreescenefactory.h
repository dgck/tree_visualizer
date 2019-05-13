#ifndef QGVABSTRACTTREESCENEFACTORY_H
#define QGVABSTRACTTREESCENEFACTORY_H

#include "Trees/tree.h"
#include "QGVScene.h"
#include <QMainWindow>
#include "commons.h"
#include "Trees/binarytree.h"

class QGVAbstractTreeSceneFactory
{
public:
    QGVAbstractTreeSceneFactory(Tree* obj, QMainWindow* parent_ptr)
        :
          m_obj{obj},
          m_parent{parent_ptr}
    {
    }

    QGVAbstractTreeSceneFactory(){}

    virtual ~QGVAbstractTreeSceneFactory()
    {

    }

    virtual QGVScene* construct_scene() = 0;

    QGVScene* get_scene()
    {
        m_scene = construct_scene();

        //maybe do some building here before returning the pointer
        return m_scene;
    }

protected:
    Tree* m_obj;
    QGVScene* m_scene;
    QMainWindow* m_parent;
};

#endif // QGVABSTRACTTREESCENEFACTORY_H

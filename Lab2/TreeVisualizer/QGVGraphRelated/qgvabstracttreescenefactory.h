#ifndef QGVABSTRACTTREESCENEFACTORY_H
#define QGVABSTRACTTREESCENEFACTORY_H

#include "Trees/tree.h"
#include "QGVCore/QGVScene.h"
#include <QMainWindow>
#include "commons.h"
#include "Trees/binarytree.h"

class QGVAbstractTreeSceneFactory
{
public:
    QGVAbstractTreeSceneFactory(Tree* tree_ptr, QObject* parent_ptr = 0)
        :
          m_tree_ptr{tree_ptr},
          m_parent{parent_ptr}
    {
    }

    virtual ~QGVAbstractTreeSceneFactory()
    {

    }

    virtual QGVScene* construct_scene() = 0;

    QGVScene* get_scene()
    {
        m_scene = construct_scene();
        m_scene -> applyLayout();

        //maybe do some building here before returning the pointer
        return m_scene;
    }

protected:
    Tree* m_tree_ptr;
    QGVScene* m_scene;
    QObject* m_parent;
};

#endif // QGVABSTRACTTREESCENEFACTORY_H

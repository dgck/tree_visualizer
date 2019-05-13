#ifndef QGVABSTRACTTREESCENEFACTORY_H
#define QGVABSTRACTTREESCENEFACTORY_H

#include "Trees/tree.h"
#include "QGVScene.h"
#include <QMainWindow>
#include "commons.h"

class QGVAbstractTreeSceneFactory
{
public:
    QGVAbstractTreeSceneFactory(Tree* obj, QMainWindow* parent_ptr)

    {
        m_parent = shared_ptr <QMainWindow> (parent_ptr);
        m_obj = shared_ptr <Tree> (obj);
    }

    virtual ~QGVAbstractTreeSceneFactory()
    {

    }

    virtual shared_ptr<QGVScene> construct_scene() = 0;

    shared_ptr <QGVScene> get_scene()
    {
        m_scene = construct_scene();

        //maybe do some building here before returning the pointer
        return m_scene;
    }

protected:
    shared_ptr <Tree> m_obj;
    shared_ptr <QGVScene> m_scene;
    shared_ptr <QMainWindow> m_parent;
};

#endif // QGVABSTRACTTREESCENEFACTORY_H

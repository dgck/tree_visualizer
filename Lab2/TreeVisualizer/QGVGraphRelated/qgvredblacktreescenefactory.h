#ifndef QGVREDBLACKTREESCENEFACTORY_H
#define QGVREDBLACKTREESCENEFACTORY_H

#include "qgvabstracttreescenefactory.h"
#include "commons.h"
#include "Trees/rbtree.h"

#include <QDebug>

class QGVRedBlackTreeSceneFactory : public QGVAbstractTreeSceneFactory
{
public:

    QGVRedBlackTreeSceneFactory(Tree* obj, QMainWindow* parent_ptr)
        : QGVAbstractTreeSceneFactory(obj, parent_ptr)
    {

    }

    shared_ptr <QGVScene> construct_scene() override
    {
        shared_ptr <QGVScene> scene_ptr = make_shared<QGVScene>(QString("rbt"), m_parent.get());
        serialize(scene_ptr);
        return scene_ptr;
    }

private:

    void serialize(shared_ptr <QGVScene> scene_ptr)
    {

        scene_ptr.get() -> applyLayout();
    }

    void walk_and_write(shared_ptr <Node> cur)
    {
        if (!cur)
            return;
        if (cur -> get_left())
        {
            qDebug() << cur -> get_key() << ' ' << cur -> get_left() -> get_key();
            walk_and_write(shared_ptr<Node> (cur -> get_left()));
        }
        if (cur -> get_right())
        {
            qDebug() << cur -> get_key() << ' ' << cur -> get_right() -> get_key();
            walk_and_write(shared_ptr<Node> (cur -> get_left()));
        }
    }

};

#endif // QGVREDBLACKTREESCENEFACTORY_H

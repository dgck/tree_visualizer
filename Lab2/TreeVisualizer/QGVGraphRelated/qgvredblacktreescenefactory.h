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

    QGVScene* construct_scene() override
    {
        QGVScene* ret = new QGVScene(QString("rbt"), m_parent);
        serialize(ret);
        return ret;
    }

private:

    void serialize(QGVScene* scene_ptr)
    {

        scene_ptr -> applyLayout();
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

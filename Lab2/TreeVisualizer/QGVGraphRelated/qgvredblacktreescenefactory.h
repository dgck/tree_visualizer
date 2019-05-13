#ifndef QGVREDBLACKTREESCENEFACTORY_H
#define QGVREDBLACKTREESCENEFACTORY_H

#include "qgvabstracttreescenefactory.h"
#include "commons.h"
#include "Trees/rbtree.h"

#include <QDebug>

class QGVRebBlackSceneFactory : public QGVAbstractTreeSceneFactory
{
public:
    explicit QGVRebBlackSceneFactory(BinaryTree* tree, QObject* parent)
    {
        m_scene = new QGVScene("name", parent);
        m_tree = tree;
    }

    QGVScene* construct_scene() override
    {
        walk(m_tree -> get_root());
        return m_scene;
    }

    void walk(Node *cur)
    {
        qDebug() << "--";
        if (!cur)
            return;
        if (cur -> get_left())
        {
            qDebug() << cur -> get_left() -> get_key();
            auto child = m_scene -> addNode(QString::number(cur -> get_left() -> get_key())),
                 parent = m_scene -> addNode(QString::number(cur -> get_key()));
            m_scene -> addEdge(parent, child);
        }
        if (cur -> get_right())
        {
            qDebug() << cur -> get_right() -> get_key();
            auto child =  m_scene -> addNode(QString::number(cur -> get_right() -> get_key())),
                 parent = m_scene -> addNode(QString::number(cur -> get_key()));
            m_scene -> addEdge(parent, child);
        }
    }

private:
    BinaryTree* m_tree;
};

#endif // QGVREDBLACKTREESCENEFACTORY_H

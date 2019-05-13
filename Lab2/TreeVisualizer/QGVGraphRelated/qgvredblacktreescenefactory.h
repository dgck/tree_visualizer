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

    void walk(Node *cur, QGVNode* pa = nullptr)
    {
        qDebug() << "--";
        if (!cur)
            return;

        QGVNode* cur_node = m_scene -> addNode(QString::number(cur -> get_key()));
        if (pa)
            m_scene -> addEdge(pa, cur_node);

        if (cur -> get_left())
        {
            walk(cur -> get_left(), cur_node);
        }
        if (cur -> get_right())
        {
            walk(cur -> get_right(), cur_node);
        }
    }

private:
    BinaryTree* m_tree;
};

#endif // QGVREDBLACKTREESCENEFACTORY_H

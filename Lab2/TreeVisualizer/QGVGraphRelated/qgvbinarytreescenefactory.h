#ifndef QGVBINARYTREESCENEFACTORY_H
#define QGVBINARYTREESCENEFACTORY_H

#include "QGVGraphRelated/qgvabstracttreescenefactory.h"
#include "commons.h"
#include "Trees/binarytree.h"

#include <QDebug>

class QGVBinaryTreeSceneFactory : public QGVAbstractTreeSceneFactory
{
public:
     QGVBinaryTreeSceneFactory(BinaryTree* tree, QObject* parent = 0)
        : QGVAbstractTreeSceneFactory(tree, parent)
    {
        m_scene = new QGVScene("name", parent);
        m_bin_tree_ptr = tree;
    }

    virtual QGVScene* construct_scene()
    {
        walk(m_bin_tree_ptr -> get_root());
        return m_scene;
    }

    void walk(Node *cur, QGVNode* pa = nullptr)
    {
        qDebug() << "--";
        if (!cur)
            return;

        QGVNode* cur_node = m_scene -> addNode(QString::number(cur -> get_key()));
        if (!cur -> get_is_black())
        {
            cur_node -> setAttribute(QString("fillcolor"), QString("red"));
            cur_node -> setAttribute(QString("style"), QString("filled"));
        }
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


    QGVScene* generate_traversal_scene(Node* node)
    {
       color_traversal(node);
       m_scene->applyLayout();
       return m_scene;
    }

    void color_traversal(Node* ptr_to_compare)
    {
        color_walk(m_bin_tree_ptr -> get_root(),nullptr, ptr_to_compare);
    }

    void color_walk(Node * cur, QGVNode* pa, Node* ptr_to_compare)
    {
        qDebug() << "--";
        if (!cur)
            return;

        QGVNode* cur_node = m_scene -> addNode(QString::number(cur -> get_key()));

        if (cur == ptr_to_compare)
        {
            cur_node -> setAttribute(QString("fillcolor"), QString("blue"));
            cur_node -> setAttribute(QString("style"), QString("filled"));
        }

        if (pa)
            m_scene -> addEdge(pa, cur_node);

        if (cur -> get_left())
        {
            color_walk(cur -> get_left(), cur_node, ptr_to_compare);
        }
        if (cur -> get_right())
        {
            color_walk(cur -> get_right(), cur_node, ptr_to_compare);
        }
    }



private:
    BinaryTree* m_bin_tree_ptr;
};

#endif // QGVBINARYTREESCENEFACTORY_H

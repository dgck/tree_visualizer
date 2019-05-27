#ifndef QGVBINARYTREESCENEFACTORY_H
#define QGVBINARYTREESCENEFACTORY_H

#include "QGVGraphRelated/qgvabstracttreescenefactory.h"
#include "commons.h"
#include "Trees/binarytree.h"

#include <QDebug>

/*!
 * \brief The QGVBinaryTreeSceneFactory class
 *
 * An override of QGVAbstractTreeSceneFactory.
 */

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


    // the next lines of code are to color a set of nodes in a graph and render them to a qgvscene object

    bool is_member_of_set(Node* to_be_tested, vector <Node*> set)
    {
        bool ans = false;
        for (auto i : set)
        {
            if (i == to_be_tested)
            {
                ans = true;
                break;
            }
        }
        return ans;
    }

    void color_walk_set(Node * cur, QGVNode* pa, vector <Node*> set)
    {
        qDebug() << "--";
        if (!cur)
            return;

        QGVNode* cur_node = m_scene -> addNode(QString::number(cur -> get_key()));

        if (is_member_of_set(cur, set))
        {
            cur_node -> setAttribute(QString("fillcolor"), QString("blue"));
            cur_node -> setAttribute(QString("style"), QString("filled"));
        }

        if (pa)
            m_scene -> addEdge(pa, cur_node);

        if (cur -> get_left())
        {
            color_walk_set(cur -> get_left(), cur_node, set);
        }
        if (cur -> get_right())
        {
            color_walk_set(cur -> get_right(), cur_node, set);
        }
    }

    void color_traversal_set(vector <Node*> set)
    {
        color_walk_set(m_bin_tree_ptr -> get_root(),nullptr, set);
    }

    QGVScene* generate_traversal_scene(vector <Node*> to_be_highlited)
    {
        color_traversal_set(to_be_highlited);
        m_scene -> applyLayout();
        return m_scene;
    }


private:
    BinaryTree* m_bin_tree_ptr;
};

#endif // QGVBINARYTREESCENEFACTORY_H

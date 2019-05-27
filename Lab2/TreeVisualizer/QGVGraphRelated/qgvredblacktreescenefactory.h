#ifndef QGVREDBLACKTREESCENEFACTORY_H
#define QGVREDBLACKTREESCENEFACTORY_H

#include "qgvabstracttreescenefactory.h"
#include "commons.h"
#include "Trees/rbtree.h"

#include <QDebug>

/*!
 * \brief The QGVRebBlackSceneFactory class
 * Colors nodes in red depending on their color value.
 */

class QGVRebBlackSceneFactory : public QGVAbstractTreeSceneFactory
{
public:
     QGVRebBlackSceneFactory(BinaryTree* tree, QObject* parent = 0)
        : QGVAbstractTreeSceneFactory(tree, parent)
    {
        m_scene = new QGVScene("name", parent);
        m_bin_tree_ptr = tree;
    }

    QGVScene* construct_scene() override
    {
        walk(m_bin_tree_ptr -> get_root());
        return m_scene;
    }

    /*!
     * \brief walk
     * \param cur
     * \param pa
     *
     * This is called when we need to walk through the tree and record its nodes and
     * edges to a QGVScene
     */
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
       m_scene -> applyLayout();
       return m_scene;
    }

    /*!
     * \brief color_traversal
     * \param ptr_to_compare
     *
     * This is a driver function which calls color_walk method
     */
    void color_traversal(Node* ptr_to_compare)
    {
        color_walk(m_bin_tree_ptr -> get_root(),nullptr, ptr_to_compare);
    }

    /*!
     * \brief color_walk
     * \param cur
     * \param pa
     * \param ptr_to_compare
     *
     * This is a modified version of walk() to walk and color nodes
     */
    void color_walk(Node * cur, QGVNode* pa, Node* ptr_to_compare)
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

#endif // QGVREDBLACKTREESCENEFACTORY_H

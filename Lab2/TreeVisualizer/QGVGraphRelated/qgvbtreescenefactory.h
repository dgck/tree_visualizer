#ifndef QGVBTREESCENEFACTORY_H
#define QGVBTREESCENEFACTORY_H

#include "commons.h"
#include "qgvabstracttreescenefactory.h"
#include "Trees/bplustree.h"

#include <QDebug>

/*!
 * \brief The QGVBTreeSceneFactory class
 *
 *  Uses record-shaped nodes from QGVCore library
 */

class QGVBTreeSceneFactory : public QGVAbstractTreeSceneFactory
{
public:
     QGVBTreeSceneFactory(BplusTree* tree, QObject* parent = 0)
        :
          QGVAbstractTreeSceneFactory(tree, parent)
    {
        m_scene = new QGVScene("name", parent);
        m_b_tree_node = tree;
        prepare();
    }

    QGVScene* construct_scene() override
    {
        walk(m_b_tree_node -> getRoot(), std::make_pair(nullptr, 0));
        return m_scene;
    }
    /*!
     * \brief walk
     * \param cur
     * \param coords
     *
     * This walks the tree and writes the nodes and edges to the scene to be returned
     */
    void walk(BNode *cur, std::pair <QGVNode*, int> coords)
    {
        qDebug() << "--";
        std::vector <int> cur_keys;
        std::vector <BNode*> cur_children;

        for (auto i : cur -> value)
        {
            if (i >= std::numeric_limits<int>::max())
                break;
            cur_keys.push_back(i);
        }

        for (auto i : cur -> child)
        {
            if (!i)
                break;
            cur_children.push_back(i);
        }

        QGVNode* node = write(cur_keys, coords);
        for (int i = 0; i < cur_children.size(); i++)
        {
            walk(cur_children[i], std::make_pair(node, i));
        }
    }

    QGVNode* write(std::vector <int> &cur_keys, std::pair <QGVNode*, int> coords)
    {

        QString label;


        /*
         * for (int i = 0; i < cur_keys.size(); i++)
        {
            label += "<";
            QString num_qstr;
            int num = cur_keys[i];
            int digits = digit_cnt(num);
            for (int i = 0; i < m_bucket_size - digits; i++)
            {
                num_qstr += QString::number(0);
            }
            num_qstr += QString::number(num);

            label += "f";
            label += QString::number(i);
            label += ">";

            label += num_qstr;
            if (i != cur_keys.size() - 1)
                label += "|";
        }
        */

        for (int i = 0; i < cur_keys.size(); i++)
        {
            QString num_qstr;
            int num = cur_keys[i];
            int digits = digit_cnt(num);
            for (int i = 0; i < m_bucket_size - digits; i++)
            {
                num_qstr += QString::number(0);
            }
            num_qstr += QString::number(num);

            label += "<";
            label += "f";
            label += QString::number(i);
            label += ">";

            label += num_qstr;
            if (i != cur_keys.size() - 1)
                label += "|";
        }

        label += "|<f";
        label += QString::number(cur_keys.size());
        label += ">";
        for (int i = 0; i < m_bucket_size; i++)
        {
            label += "+";
        }

        QGVNode* node = m_scene -> addNode(label);
        node -> setAttribute("shape", "record");

        if (coords.first)
        {
            QGVEdge* edge = m_scene -> addEdge(coords.first, node);
            QString port = "f";
            port += QString::number(coords.second);
            edge -> setAttribute("tailport", port);
        }

        return node;
    }

    /*!
     * \brief prepare
     *
     * This is a driver function to prepare member variables for tree rendering
     */
    void prepare()
    {
        walk_cp(m_b_tree_node -> root);
        m_bucket_size = digit_cnt(m_bucket_maxnum);
    }

    /*!
     * \brief digit_cnt
     * \param num
     * \return
     *
     * This returns the number of digits of a number
     */
    int digit_cnt(int num)
    {
        int p10 = 1;
        int res = 0;
        while (num / p10)
        {
            res++;
            p10 *= 10;
        }
        return res;
    }

    /*!
     * \brief walk_cp
     * \param cur
     *
     * This stores the maximum number in a tree in member variable
     */
    void walk_cp(BNode *cur)
    {
        qDebug() << "--";
        std::vector <int> cur_keys;
        std::vector <BNode*> cur_children;

        for (auto i : cur -> value)
        {
            if (i >= std::numeric_limits<int>::max())
                break;
            cur_keys.push_back(i);
        }

        for (auto i : cur -> child)
        {
            if (!i)
                break;
            cur_children.push_back(i);
        }

        for (int i = 0; i < cur_keys.size(); i++)
        {
            m_bucket_maxnum = max(m_bucket_maxnum, cur_keys[i]);
        }

        for (int i = 0; i < cur_children.size(); i++)
        {
            walk_cp(cur_children[i]);
        }
    }

    // this is temporary
    QGVScene* generate_traversal_scene(Node*)
    {
        return new QGVScene("temp");
    }

private:
    BplusTree* m_b_tree_node;

    // for internal sturcture of records
    int m_bucket_maxnum = 0;
    int m_bucket_size = 0;
};

#endif // QGVBTREESCENEFACTORY_H

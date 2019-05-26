#ifndef QGVBTREESCENEFACTORY_H
#define QGVBTREESCENEFACTORY_H

#include "commons.h"
#include "qgvabstracttreescenefactory.h"
#include "Trees/bplustree.h"

#include <QDebug>

class QGVBTreeSceneFactory : public QGVAbstractTreeSceneFactory
{
public:
    explicit QGVBTreeSceneFactory(BplusTree* tree, QObject* parent)
        :
          QGVAbstractTreeSceneFactory(tree, parent)
    {
        m_scene = new QGVScene("name", parent);
        m_b_tree_node = tree;
    }

    QGVScene* construct_scene() override
    {
        walk(m_b_tree_node -> getRoot(), std::make_pair(nullptr, 0));
        return m_scene;
    }

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

    // impl this
    QGVNode* write(std::vector <int> &cur_keys, std::pair <QGVNode*, int> coords)
    {


        for (int i = 0; i < cur_keys.size(); i++)
        {
            label += " <";
            label += QString::number(i);
            label += "> ";
            label += QString::number(i);
            if (i != cur_keys.size() - 1)
                label += " |";
        }

        QGVNode* node = m_scene -> addNode(label);
        node -> setAttribute("shape", "record");

        if (coords.first)
        {
            QGVEdge* edge = m_scene -> addEdge(coords.first, node);
            edge -> setAttribute("tailport", QString::number(coords.second));
        }

        return node;
    }


private:
    BplusTree* m_b_tree_node;
    int bucket_counter = 0;
};

#endif // QGVBTREESCENEFACTORY_H

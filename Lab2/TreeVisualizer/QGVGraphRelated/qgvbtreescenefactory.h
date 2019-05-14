#ifndef QGVBTREESCENEFACTORY_H
#define QGVBTREESCENEFACTORY_H

#include "commons.h"
#include "qgvabstracttreescenefactory.h"
#include "Trees/bplustree.h"

class QGVBTreeSceneFactory : public QGVAbstractTreeSceneFactory
{
public:
    explicit QGVBTreeSceneFactory(BplusTree* tree, QObject* parent)
        :
          QGVAbstractTreeSceneFactory(tree, parent)
    {
        m_b_tree_node = tree;
    }

    QGVScene* construct_scene() override
    {
        walk(m_b_tree_node -> getRoot());
        return m_scene;
    }

    void walk(BNode *cur, QGVNode* pa = nullptr)
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

        write(cur_keys, cur_children);
        for (auto i : cur_children)
        {
            walk(i);
        }
    }

    // impl this
    void write(std::vector <int> &cur_keys, std::vector <BNode*> &cur_children)
    {

    }


private:
    BplusTree* m_b_tree_node;
};

#endif // QGVBTREESCENEFACTORY_H

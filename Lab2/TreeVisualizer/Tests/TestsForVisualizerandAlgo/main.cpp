#include<gtest/gtest.h>
#include "Trees/bplustree.h"
#include "Trees/obst.h"
#include "Trees/rbtree.h"
#include "Trees/splaytree.h"
#include "algorithm"
#include <QDebug>

TEST(SimpleTree,insert_delete_search)
{
    Tree*t = new BinaryTree;
    for (int i = 0; i < 50; i++)
    {
        t->insert(i);
    }
    BinaryTree*new_tree = dynamic_cast<BinaryTree*>(t);
    for (int i = 0; i < 50; i++)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n->key,i)<<"key " << i << " not found\n";
    }
    for (int i = 0; i < 50; i+=2)
    {
        t->deleteNode(i);
    }
    for (int i = 0; i < 50; i+=2)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n,nullptr)<<"key " << i << " was deleted\n";
    }
}

TEST(SimpleTree,center)
{
    Tree*t = new BinaryTree;
    t->insert(10);//root
    t->insert(11);
    t->insert(7);//should be a center
    t->insert(8);
    t->insert(4);
    t->insert(5);
    t->insert(3);
    vector<int>center = t->center();
    auto vertices = dynamic_cast<BinaryTree*>(t)->getVertices();
    EXPECT_EQ(center.size(),1);
    for (auto el:vertices)
    {
        if(get<0>(el) == center.at(0))
        {
            EXPECT_EQ(get<1>(el)->key,7);
        }
    }
}

TEST(SimpleTree,diametr)
{
    Tree*t = new BinaryTree;
    t->insert(10);//root
    t->insert(11);
    t->insert(7);
    t->insert(8);
    t->insert(4);
    t->insert(5);
    t->insert(3);
    vector<int>diametr = t->diameter();
    auto vertices = dynamic_cast<BinaryTree*>(t)->getVertices();
    EXPECT_EQ(diametr.size(),5);//11-10-7-4-3
    auto it = find_if(vertices.begin(),vertices.end(),[=](tuple<int, Node *> t)
    {
        return get<0>(t) == diametr.at(0);
    });
    EXPECT_EQ(get<1>((*it))->key,11);


    it = find_if(vertices.begin(),vertices.end(),[=](tuple<int, Node *> t)
    {
        return get<0>(t) == diametr.at(1);
    });
    EXPECT_EQ(get<1>((*it))->key,10);

    it = find_if(vertices.begin(),vertices.end(),[=](tuple<int, Node *> t)
    {
        return get<0>(t) == diametr.at(2);
    });
    EXPECT_EQ(get<1>((*it))->key,7);

    it = find_if(vertices.begin(),vertices.end(),[=](tuple<int, Node *> t)
    {
        return get<0>(t) == diametr.at(3);
    });
    EXPECT_EQ(get<1>((*it))->key,4);

    it = find_if(vertices.begin(),vertices.end(),[=](tuple<int, Node *> t)
    {
        return get<0>(t) == diametr.at(4);
    });
    EXPECT_EQ(get<1>((*it))->key,3);
}

TEST(RbTree,insert_delete_search)
{
    Tree*t = new RBTree;
    for (int i = 0; i < 50; i++)
    {
        t->insert(i);
    }
    RBTree*new_tree = dynamic_cast<RBTree*>(t);
    for (int i = 0; i < 50; i++)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n->key,i)<<"key " << i << " not found\n";
    }
    for (int i = 0; i < 50; i+=2)
    {
        t->deleteNode(i);
    }
    for (int i = 0; i < 50; i+=2)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n,nullptr)<<"key " << i << " was deleted\n";
    }

}
TEST(RbTree,merge)
{
    Tree*t1 = new RBTree;
    Tree*t2 = new RBTree;
    for (int i = 0,k = 50;i<50;i++,k++)
    {
        t1->insert(i);
        t2->insert(k);
    }
    t1->merge(t2);
    RBTree*new_tree = dynamic_cast<RBTree*>(t1);
    for (int i = 0; i < 100; i++)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n->key,i)<<"key " << i << " not found\n";
    }
}

TEST(RbTree,Intersection)
{
    Tree*t1 = new RBTree;
    Tree*t2 = new RBTree;
    for (int i = 0;i<50;i++)
    {
        t1->insert(i);
    }
    for (int i = 0;i<50;i+=2)
    {
        t2->insert(i);
    }
    vector<int> intersection = t1->intersection(t2);
    EXPECT_EQ(intersection.size(),25);
    for (int i = 0,k = 0; i<50; i+=2,k++)
    {
        EXPECT_EQ(intersection.at(k),i);
    }
}

TEST(Splay,insert_delete_search)
{
    Tree*t = new SplayTree;
    for (int i = 0; i < 50; i++)
    {
        t->insert(i);
    }
    SplayTree*new_tree = dynamic_cast<SplayTree*>(t);
    for (int i = 0; i < 50; i++)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n->key,i)<<"key " << i << " not found\n";
    }
    for (int i = 1; i < 50; i+=10)
    {
        t->deleteNode(i);
    }
    for (int i = 1; i < 50; i+=10)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n,nullptr)<<"key " << i << " was deleted\n";
    }
}
TEST(OBST,insert_delete_search)
{
    vector<string> s{"one","two","three"};
    vector<int> i{1,2,3};

    OBST tree(s,i);
    vector<int> v = tree.getElements();
    EXPECT_EQ(3,v.size());

    tree.deleteNode(1);
    Node*n = tree.search(1);
    EXPECT_EQ(n,nullptr);
}

TEST(BPlus,insert_delete_search)
{
    Tree*t = new BplusTree;
    for (int i = -20; i < 50; i++)
    {
        t->insert(i);
    }
    BplusTree*new_tree = dynamic_cast<BplusTree*>(t);
    for (int i = -20; i < 50; i++)
    {
        bool isInTree = new_tree->search(i);
        EXPECT_TRUE(isInTree)<<"key " << i << " not found\n";
    }
    for (int i = 0; i < 2; i++)
    {
        new_tree->deleteNode(i);
    }
    for (int i = 0; i < 2; i++)
    {
        bool isInTree = new_tree->search(i);
        EXPECT_FALSE(isInTree)<<"key " << i << " was deleted\n";
    }

}

TEST(BPlus,merge)
{
    Tree*t1 = new BplusTree;
    Tree*t2 = new BplusTree;
    for (int i = 0,k = 50;i<50;i++,k++)
    {
        t1->insert(i);
        t2->insert(k);
    }
    t1->merge(t2);
    BplusTree*new_tree = dynamic_cast<BplusTree*>(t1);
    for (int i = 0; i < 100; i++)
    {
        bool isInTree = new_tree->search(i);
        EXPECT_TRUE(isInTree)<<"key " << i << " not found\n";
    }
}

TEST(BPlus,Intersection)
{
    Tree*t1 = new BplusTree;
    Tree*t2 = new BplusTree;
    for (int i = 0;i<50;i++)
    {
        t1->insert(i);
    }
    for (int i = 0;i<50;i+=2)
    {
        t2->insert(i);
    }
    vector<int> intersection = t1->intersection(t2);
    EXPECT_EQ(intersection.size(),25);
    for (int i = 0,k = 0; i<50; i+=2,k++)
    {
        EXPECT_EQ(intersection.at(k),i);
    }
}



int main(int argc,char*argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

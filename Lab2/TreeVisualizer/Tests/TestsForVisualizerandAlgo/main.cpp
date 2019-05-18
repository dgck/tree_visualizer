#include<gtest/gtest.h>
#include "Trees/bplustree.h"
#include "Trees/obst.h"
#include "Trees/rbtree.h"
#include "Trees/splaytree.h"

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
    Tree*t = new OBST;
    for (int i = -20; i < 50; i++)
    {
        t->insert(i);
    }
    OBST*new_tree = dynamic_cast<OBST*>(t);
    for (int i = -20; i < 50; i++)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n->key,i)<<"key " << i << " not found\n";
    }
    for (int i = -10; i < 50; i+=5)
    {
        t->deleteNode(i);
    }
    for (int i = -10; i < 50; i+=5)
    {
        Node *n = new_tree->search(i);
        EXPECT_EQ(n,nullptr)<<"key " << i << " was deleted\n";
    }
    vector<string> s{"one","two","three"};
    vector<int> i{1,2,3};

    OBST tree(s,i);
    vector<int> v = tree.getElements();
    EXPECT_EQ(3,v.size());
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


int main(int argc,char*argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

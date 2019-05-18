#include<gtest/gtest.h>
#include "Trees/bplustree.h"
#include "Trees/obst.h"
#include "Trees/rbtree.h"
#include "Trees/splaytree.h"

TEST(SimpleTree,insert)
{
    Tree*t = new BinaryTree;
    t->insert(100);
    t->insert(1);
    t->insert(5);
    t->insert(2);
    t->insert(3);
    t->insert(55);
    t->insert(0);
    BinaryTree*new_tree = dynamic_cast<BinaryTree*>(t);
    EXPECT_EQ(new_tree->root->right,nullptr)<<"Right son of binary tree should be null, but isn`t\n";
}
TEST(RbTree,merge)
{
    Tree*t1 = new RBTree;
    Tree*t2 = new RBTree;
    t1->insert(1);
    t2->insert(2);
    t1->merge(t2);
}


int main(int argc,char*argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

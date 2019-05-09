#ifndef TREEALGORITHMS_H
#define TREEALGORITHMS_H
#include "rbtree.h"
#include <tuple>
#include <iostream>
#include <algorithm>

using namespace std;

class TreeAlgorithms
{
public:
    TreeAlgorithms();
    void dsf(RBTree t){
        vector<vector<tuple<int, int>>> adj = t.convertToGraph();
        vector<vector<tuple<int, int>>> v = {
                {make_tuple(0,1),make_tuple(1,5)},
             {make_tuple(1,5),make_tuple(0,1),make_tuple(2,7),make_tuple(3,10)},
            {make_tuple(2,7),make_tuple(1,5)},
            {make_tuple(3,10),make_tuple(1,5),make_tuple(6,15)},
            {make_tuple(4,11),make_tuple(5,13)},
            {make_tuple(5,13),make_tuple(4,11),make_tuple(6,15)},
            {make_tuple(6,15),make_tuple(5,13),make_tuple(7,20),make_tuple(3,10)},
            {make_tuple(7,20),make_tuple(6,15)}
            };
        vector<bool> used(v.size(), false);
        vector<int> path;
        dfs (0, v, used, path);
        cout<<"dfs"<<endl;

        for (int i=0;i<path.size();i++) {
            cout<<path[i];
        }

    }

    void dfs(int v,vector<vector<tuple<int, int>>> g, vector<bool>& used, vector<int>& path){

            used[v] = true;
            cout<<v<<endl;
            path.push_back(v);
            for(int i=0; i<g[v].size(); i++){
                if (!used[get<0>(g[v][i])]) dfs(get<0>(g[v][i]), g, used,path);
            }
    }

    vector<int> intersection(RBTree t1, RBTree t2){
        vector<int> v1=t1.getElements(), v2=t2.getElements(), inters;
        inters = intersection(v1,v2);
        return inters;
    }

    vector<int> intersection(vector<int> v1, vector<int> v2){
        vector<int> inters;
        for (int i=0;i<v1.size();i++)
            if(find(v2.begin(), v2.end(), v1[i]) != v2.end())
                inters.push_back(v1[i]);
        return inters;
    }

    tuple<bool,int> inclusion(RBTree t1, RBTree t2){
        vector<int> v1=t1.getElements(), v2=t2.getElements(), inters;
        inters = intersection(v1,v2);
        if(v1.size()==v2.size()&& v2.size()==inters.size())
            return make_tuple(true,0); //trees are equal
        if(v1.size()<v2.size()&& v1.size()==inters.size())
            return make_tuple(true,1); //second tree includes first
        if(v1.size()>v2.size()&& v2.size()==inters.size())
            return make_tuple(true,2); //first tree includes second
        return make_tuple(false, 0);
    }
};


#endif // TREEALGORITHMS_H

//
// Created by Omer Oz on 02/06/2023.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H
#include "utilesWet2.h"

class UFNode{
public:
    int m_id;
    UFNode* m_father;
    int m_rank;
    int m_r;
    int m_height;
    int m_tower_height;

    //UFNode() {};
    explicit UFNode(int id, int height):m_id(id),m_father(nullptr),m_rank(0),m_r(0),m_height(height),m_tower_height(height){};
};

class UnionFind{
public:
    UFNode* m_leaf;
    UFNode** UFArray;
    int* columnsArr;

    int find(int recordId);
    StatusType Union(int id1,int id2);

    UnionFind(UFNode** array,int* columnsArr): UFArray(array), columnsArr(columnsArr){};

private:
  int topRecHigh(int recordId);
};









#endif //WET2_UNIONFIND_H

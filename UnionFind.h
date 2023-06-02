//
// Created by Omer Oz on 02/06/2023.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

class UFNode{
public:
    int m_id;
    UFNode* m_father;
    int m_rank;
    int m_toSubtract;
    int m_height;

    UFNode();
    explicit UFNode(int id):m_id(id),m_father(nullptr),m_rank(0),m_toSubtract(0),m_height(0){};
};

class UnionFind{
public:
    UFNode* m_leaf;
};









#endif //WET2_UNIONFIND_H

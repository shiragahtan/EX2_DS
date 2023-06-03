//
// Created by Omer Oz on 02/06/2023.
//

#include <cassert>
#include "UnionFind.h"


int UnionFind::find(int recordId) {
    //important!!!! i assume that when calling this function you already made sure that this id exists
    auto root= UFArray[recordId];
    if(root->m_father== nullptr){
        return root->m_id;
    }
    int sum=0;
    int toSubtract=0;
    int tempSum=0;
    auto currentNode=UFArray[recordId];
    while(root->m_father!= nullptr){
        sum+=root->m_r;
        root=root->m_father;
    }
    UFNode* temp;
    while(currentNode->m_father!=root){
        temp=currentNode;
        tempSum=currentNode->m_r;
        currentNode->m_r=sum-toSubtract;
        toSubtract+=tempSum;
        currentNode=currentNode->m_father;
        temp->m_father=root;
        assert(currentNode->m_father!= nullptr);
    }
    return root->m_id;

}
StatusType UnionFind::Union(int id1, int id2) {
    //important!!!! i assume that when calling this function you already made sure that this id exists
    int root1= find(id1);
    int root2= find(id2);
    if (root1==root2){
        return StatusType::FAILURE;
    }
    auto rootNode1= UFArray[root1];
    auto rootNode2= UFArray[root2];
    rootNode1->m_height+= rootNode2->m_tower_height;

    if (rootNode1->m_rank<=rootNode2->m_rank){
        rootNode1->m_father=rootNode2;
        rootNode2->m_rank+=rootNode1->m_rank;
        if (rootNode1->m_rank==0){
            rootNode2->m_rank++;
        }
        rootNode1->m_r+= (rootNode2->m_tower_height-rootNode2->m_r);
        rootNode2->m_tower_height+=rootNode1->m_tower_height;
    }
    else{
        rootNode2->m_father=rootNode1;
        rootNode1->m_rank+=rootNode2->m_rank;
        if (rootNode2->m_rank==0){
            rootNode1->m_rank++;
        }
        rootNode1->m_r+= rootNode2->m_tower_height;
        rootNode2->m_r-=rootNode1->m_r;
        rootNode1->m_tower_height+=rootNode2->m_tower_height;

    }
    return StatusType::SUCCESS;
}
/*
int UnionFind::topRecHigh(int recordId) {
    //important!!!! i assume that when calling this function you already made sure that this id exists
    return UFArray[find(recordId)]->m_height;
}
*/
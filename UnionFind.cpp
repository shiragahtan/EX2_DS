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
    auto currentNode=UFArray[recordId];
    while(root->m_father!= nullptr){
        root=root->m_father;
    }
    UFNode* temp;
    while(currentNode->m_father!=root){
        temp=currentNode;
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
    if (rootNode1->m_rank<=rootNode2->m_rank){
        rootNode1->m_father=rootNode2;
        rootNode2->m_rank+=rootNode1->m_rank;
        if (rootNode1->m_rank==0){
            rootNode2->m_rank++;
        }
        return StatusType::SUCCESS;
    }
    else{
        rootNode2->m_father=rootNode1;
        rootNode1->m_rank+=rootNode2->m_rank;
        if (rootNode2->m_rank==0){
            rootNode1->m_rank++;
        }
        return StatusType::SUCCESS;
    }
}


//
// Created by Omer Oz on 02/06/2023.
//

#include "UnionFind.h"


UFNode* UnionFind::find(int recordId) {
    //important!!!! i assume that when calling this function you already made sure that this id exists
    auto root= UFArray[recordId];
    if(root->m_father== nullptr){
        return root;
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
    }
    return root;

}
StatusType UnionFind::Union(int id1, int id2) {
    //important!!!! i assume that when calling this function you already made sure that this id exists
    UFNode* root1= find(id1);
    UFNode* root2= find(id2);
    if (root1->m_id==root2->m_id){
        return StatusType::FAILURE;
    }
    if (root1->m_rank<=root2->m_rank){
        root1->m_father=root2;
        root2->m_rank+=root1->m_rank;
        if (root2->m_rank==0){
            root2->m_rank++;
        }
        return StatusType::SUCCESS;
    }
    else{
        root2->m_father=root1;
        root1->m_rank+=root2->m_rank;
        return StatusType::SUCCESS;
    }
}


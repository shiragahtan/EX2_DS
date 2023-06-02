//
// Created by shira on 01/06/2023.
//
#include "AvlTree.h"
#include "recordsCompany.h"
#ifndef EX2_DS_STRUCTURES_H
#define EX2_DS_STRUCTURES_H


class HashTable{
    int m_size;
    int numMembers;
    int factor;
    AvlTree<int,Costumer> **costumerArr; //an array that points to AVLTREE objects

    int hashFunction(int key) const;
    void hashTableDoubling();
    void hashTableShrinking();
    void reHashing(int keyBefore);

public:
    HashTable();
    ~HashTable();
    void insertCostumer(Costumer newCostumer);
    Costumer search(int key) const;
};

static int START_SIZE = 50;

int main(){
    HashTable hash1;
    Costumer costumer1(1,1);
    hash1.insertCostumer(costumer1);
}

#endif //EX2_DS_STRUCTURES_H

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
    AvlTree<int,Costumer> **costumerArr; //an array that points to AVLTREE objects

    int hashFunction(int key) const;
    void hashTableDoubling();
    void hashTableShrinking(); //TODO: CHECK IF NEEDED
    void reHashing(int sizeBefore);

public:
    HashTable();
    ~HashTable();
    void insertCostumer(Costumer newCostumer);
    Costumer search(int key) const;
};

static int START_SIZE = 2;
static int EXPAND_RATE = 2;

int main(){
    HashTable hash1;
    Costumer costumer1(1,1);
    Costumer costumer2(2,1);
    Costumer costumer3(3,1);
    Costumer costumer4(4,1);
    Costumer costumer9(9,1);

    hash1.insertCostumer(costumer1);
    hash1.insertCostumer(costumer2);
    Costumer searching = hash1.search(2);
    hash1.insertCostumer(costumer3);
    hash1.insertCostumer(costumer4);
    hash1.insertCostumer(costumer9);
}

#endif //EX2_DS_STRUCTURES_H

//
// Created by shira on 01/06/2023.
//
#ifndef EX2_DS_STRUCTURES_H
#define EX2_DS_STRUCTURES_H

#include "Classes.h"
#include "AvlTree.h"

//class HashTable;

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

#endif //EX2_DS_STRUCTURES_H

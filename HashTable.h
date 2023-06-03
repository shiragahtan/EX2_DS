//
// Created by shira on 01/06/2023.
//
#ifndef EX2_DS_STRUCTURES_H
#define EX2_DS_STRUCTURES_H

#include "Classes.h"
#include "AvlTree.h"

//class HashTable;

class HashTable{

public:
    int m_size;
    int numMembers;
    AvlTree<int,Costumer> **costumerArr; //an array that points to AVLTREE objects

    int hashFunction(int key) const;
    void hashTableDoubling();
    void reHashing(int sizeBefore);

    //TODO: move to private all up

    HashTable();
    ~HashTable();
    StatusType_t insertCostumer(Costumer newCostumer);
    void makeMember(int key);
    Costumer search(int key) const;
    int searchIfExists(int key) const;
};

static int START_SIZE = 2;
static int EXPAND_RATE = 2;
static int NOT_IN_HASH = -1;

#endif //EX2_DS_STRUCTURES_H

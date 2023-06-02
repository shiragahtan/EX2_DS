//
// Created by shira on 01/06/2023.
//

#include "HashTable.h"

/*
 *
 * class HashTable{
    int m_size;
    int numMembers;
    int factor;
    AvlTree *arr;
 */


HashTable::HashTable() :m_size(START_SIZE), numMembers(0), factor(0) {
    costumerArr = new AvlTree<int,Costumer> [m_size];
    for (int i=0; i<m_size; i++){
        costumerArr[i] = NULL;
    }
}

HashTable::~HashTable() {
    for (int i=0; i<m_size; i++){
        if (costumerArr[i]){
            ~costumerArr[i];
        }
    }
    delete[] costumerArr;
}

void HashTable::insertCostumer(Costumer *newCostumer) {
    numMembers++;
    factor = numMembers/m_size;
    if (factor >= 1){
        hashTableDoubling();
    }
    int indexOfNew = hashFunction(newCostumer->m_c_id);
    if (costumerArr[indexOfNew] == nullptr){
        AvlTree<int,Costumer> *newAvl = new AvlTree<int,Costumer>();
        costumerArr[indexOfNew] = newAvl;
    }
    *(costumerArr[indexOfNew]).insert(newCostumer->m_c_id, newCostumer);
}




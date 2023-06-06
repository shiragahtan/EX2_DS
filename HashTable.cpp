//
// Created by shira on 01/06/2023.
//

#include "HashTable.h"

HashTable::HashTable() :m_size(START_SIZE), numMembers(0) {
    try {
        costumerArr = new AvlTree<int, Costumer> *[m_size];
        for (int i = 0; i < m_size; i++) {
            costumerArr[i] = nullptr;
        }
    }
    catch (const std::bad_alloc&){
        throw;
    }
}

HashTable::~HashTable() {
    for (int i=0; i<m_size; i++){
        if (costumerArr[i] != nullptr){
            delete costumerArr[i];
        }
    }
    delete[] costumerArr;
}


StatusType_t HashTable::insertCostumer(Costumer newCostumer) {
    numMembers++;
    if (numMembers == m_size){ //check if the factor is 1
        hashTableDoubling();
    }
    int indexOfNew = hashFunction(newCostumer.m_c_id);
    if (costumerArr[indexOfNew] == nullptr){
        try {
            costumerArr[indexOfNew] = new AvlTree<int, Costumer>();
            if (costumerArr[indexOfNew]->insert(newCostumer.m_c_id, newCostumer) == ALLOCATION_ERROR){
                return ALLOCATION_ERROR;
            }
        }
        catch (std::exception &exe){
            return ALLOCATION_ERROR;
        }
    }
    return SUCCESS;

}


int HashTable::hashFunction(int key) const{
    return (key % m_size);
}

Costumer HashTable::search(int key) const{
    int indexOfMember = hashFunction(key);
    Node<int,Costumer> *costumerNode = costumerArr[indexOfMember]->find(key);
    return costumerNode->m_info;
}

int HashTable::searchIfExists(int key) const{
    int indexOfMember = hashFunction(key);
    if (costumerArr[indexOfMember] == nullptr){
        return NOT_IN_HASH;
    }
    Node<int,Costumer> *costumerNode = costumerArr[indexOfMember]->find(key);
    if (costumerNode == nullptr){
        return NOT_IN_HASH;
    }
    return costumerNode->m_info.m_phoneNum;
}

void HashTable::makeMember(int key){
    int indexOfMember = hashFunction(key);
    costumerArr[indexOfMember]->find(key)->m_info.clubMember = true;
}


void HashTable::reHashing(int sizeBefore) {
    try {
        AvlTree<int, Costumer> **newCostumerArr = new AvlTree<int, Costumer> *[m_size];
        for (int i = 0; i < m_size; i++) {
            newCostumerArr[i] = nullptr;
        }
        for (int i = 0; i < sizeBefore; i++) {
            while (costumerArr[i] != nullptr && costumerArr[i]->m_size > 0) {
                Node<int, Costumer> *NodeToAdd = costumerArr[i]->getMax();
                int newIndex = hashFunction(NodeToAdd->m_key);
                if (newCostumerArr[newIndex] == nullptr) {
                    newCostumerArr[newIndex] = new AvlTree<int, Costumer>();
                }
                newCostumerArr[newIndex]->insert(NodeToAdd->m_key, NodeToAdd->m_info);
                costumerArr[i]->remove(NodeToAdd->m_key);
            }
            delete costumerArr[i];
        }
        delete[] costumerArr;
        this->costumerArr = newCostumerArr;
    }
    catch (const std::bad_alloc&){
        throw;
    }
};

void HashTable::hashTableDoubling(){
    int sizeBeforeChange = m_size;
    m_size *=EXPAND_RATE;
    reHashing(sizeBeforeChange);
}



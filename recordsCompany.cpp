//
// Created by shira on 01/06/2023.
//

#include "recordsCompany.h"


Costumer::Costumer(int c_id, int phone) : m_c_id(c_id), m_phoneNum(phone), clubMember(false) {};

Record::Record(int r_id, int numCopies, int numPurchases) : m_r_id(r_id), m_numCopies(numCopies), m_numPurchases(numPurchases) {};

/*
StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    UFNode* UFArray= new UFNode[number_of_records];
    for(int i=0;i<number_of_records;i++){
        UFArray[i]=UFNode(i);
    }

}*/

RecordsCompany::RecordsCompany(){
    HashTable recordsHash();
}
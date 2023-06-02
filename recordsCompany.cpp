//
// Created by shira on 01/06/2023.
//

#include "recordsCompany.h"

RecordsCompany::RecordsCompany() : membersTree() , membersHash(){};

StatusType RecordsCompany::addCostumer(int c_id, int phone) {
    if (c_id < 0 || phone < 0){
        return INVALID_INPUT;
    }
    if (membersHash.searchIfExists(c_id) == DOESNT_EXIST){
        return ALREADY_EXISTS;
    }

}



Costumer::Costumer(int c_id, int phone) : m_c_id(c_id), m_phoneNum(phone) {};

Record::Record(int r_id, int numCopies, int numPurchases) : m_r_id(r_id), m_numCopies(numCopies), m_numPurchases(numPurchases) {};

RecordsCompany::RecordsCompany() {};
RecordsCompany::~RecordsCompany() {};

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    auto UFArray= new UFNode*[number_of_records];
    for(int i=0;i<number_of_records;i++){
        UFArray[i]=new UFNode(i);
    }
    UF=new UnionFind(UFArray);

}
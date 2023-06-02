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

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    auto UFArray= new UFNode*[number_of_records];
    for(int i=0;i<number_of_records;i++){
        UFArray[i]=new UFNode(i,records_stocks[i]);
        columnsArr[i]=i;
}
UF=new UnionFind(UFArray);
recordNum=number_of_records;

}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if (r_id1<0 || r_id2<0){
        return StatusType::INVALID_INPUT;
    }
    if (r_id1>=recordNum || r_id2>=recordNum){
        return StatusType::DOESNT_EXISTS;
    }
    if (UF->Union(r_id1,r_id2)==StatusType::FAILURE)
    {
        return StatusType::FAILURE;
    }
    int root= UF->find(r_id1);
    columnsArr[root]=columnsArr[r_id2];
}
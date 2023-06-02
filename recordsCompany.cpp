//
// Created by shira on 01/06/2023.
//

#include "recordsCompany.h"

RecordsCompany::RecordsCompany() : membersTree() , membersHash(){};

StatusType RecordsCompany::addCostumer(int c_id, int phone) {
    if (c_id < 0 || phone < 0){
        return INVALID_INPUT;
    }
    if (membersHash.searchIfExists(c_id) != NOT_IN_HASH){
        return ALREADY_EXISTS;
    }
    Costumer newCostumer(c_id, phone);
    if (membersHash.insertCostumer(newCostumer) == ALLOCATION_ERROR){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id){
    if (c_id < 0){
        return INVALID_INPUT;
    }
    int searchAnswer = membersHash.searchIfExists(c_id);
    if (searchAnswer == NOT_IN_HASH){
        return Output_t<int>(DOESNT_EXISTS);
    }
    return Output_t<int>(searchAnswer);
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    auto UFArray= new UFNode*[number_of_records];
    for(int i=0;i<number_of_records;i++){
        UFArray[i]=new UFNode(i,records_stocks[i]);
        columnsArr[i]=i;
}
UF=new UnionFind(UFArray);
recordNum=number_of_records;

Output_t<bool> RecordsCompany::isMember(int c_id){
    if (c_id < 0){
        return INVALID_INPUT;
    }
    int searchAnswer = membersHash.searchIfExists(c_id);
    if (searchAnswer == NOT_IN_HASH){
        return Output_t<bool>(DOESNT_EXISTS);
    }
    Costumer costumer = membersHash.search(c_id);
    return Output_t<bool>(costumer.clubMember);
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
    costumerToUpdate.clubMember = true;
    //TODO: add the member to the tree
    return SUCCESS;
}
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
        UFArray[i]=new UFNode(i);
    }
    UF=new UnionFind(UFArray);
    //TODO: to update about money of members in AVLTREE
}

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

StatusType RecordsCompany::makeMember(int c_id) {
    if (c_id < 0){
        return INVALID_INPUT;
    }
    int searchAnswer = membersHash.searchIfExists(c_id);
    if (searchAnswer == NOT_IN_HASH){
        return DOESNT_EXISTS;
    }
    Costumer costumerToUpdate = membersHash.search(c_id);
    if (costumerToUpdate.clubMember){
        return ALREADY_EXISTS;
    }
    membersHash.makeMember(c_id);
    //TODO: add the member to the memberstree
    return SUCCESS;
}

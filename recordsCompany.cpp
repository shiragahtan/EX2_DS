//
// Created by shira on 01/06/2023.
//

#include "recordsCompany.h"

RecordsCompany::RecordsCompany() : membersTree() , membersHash(),numberOfPurchases(nullptr){};//TODO: update with new fields


RecordsCompany:: ~RecordsCompany(){ //update the dctor
    membersHash.~HashTable();
    membersTree.~AvlTree();
    if (isNewMonth){
        delete[] columnsArr;
        delete UF;
    }

}

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
    int searchAnswer = membersHash.searchIfExists(c_id); //searchAnswer has the phone number of the costumer
    if (searchAnswer == NOT_IN_HASH){
        return Output_t<int>(DOESNT_EXISTS);
    }
    return Output_t<int>(searchAnswer);
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records) {
    if (number_of_records<0){
        return StatusType::INVALID_INPUT;
    }
    try {
        auto UFArray = new UFNode *[number_of_records];
        columnsArr = new int[number_of_records];
        numberOfPurchases = new int[number_of_records];
        for (int i = 0; i < number_of_records; i++) {
            UFArray[i] = new UFNode(i, records_stocks[i]);
            columnsArr[i] = i;
            numberOfPurchases[i] = 0;
        }
        UF = new UnionFind(UFArray,number_of_records);
    }
    catch (std::exception &exe){
        return ALLOCATION_ERROR;
    }
    isNewMonth= true;
    recordNum = number_of_records;
    return StatusType::SUCCESS;
    //TODO: TO UPDATE ALL THE VALUES OF THE COSTUMERS TO 0
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id) {
    if (c_id < 0 || r_id < 0) {
        return StatusType::INVALID_INPUT;
    }
    if (membersHash.searchIfExists(c_id) == NOT_IN_HASH || r_id >= recordNum) {
        return StatusType::DOESNT_EXISTS;
    }
    if (membersHash.search(c_id).clubMember) {
        membersTree.find(c_id)->m_info.selfSaleAmount -= (100 + numberOfPurchases[r_id]);
    }
    numberOfPurchases[r_id]++;
    return (StatusType::SUCCESS);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2) {
    if (r_id1 < 0 || r_id2 < 0) {
        return StatusType::INVALID_INPUT;
    }
    if (r_id1 >= recordNum || r_id2 >= recordNum) {
        return StatusType::DOESNT_EXISTS;
    }
    int root1 = UF->find(r_id1);
    int root2 = UF->find(r_id2);
    if (UF->Union(r_id1, r_id2) == StatusType::FAILURE) {
        return StatusType::FAILURE;
    }

    columnsArr[root1] = columnsArr[root2];

    return SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight) {
    if(r_id<0 || column== nullptr || hight== nullptr){ //TODO: make sure it catches nullptrs
        return StatusType::INVALID_INPUT;
    }
    if (r_id>=recordNum){
        return StatusType::DOESNT_EXISTS;
    }

        auto currentNode=UF->UFArray[r_id];

        int sum=0;
        while(currentNode->m_father!= nullptr){
            sum+=currentNode->m_r;
            currentNode=currentNode->m_father;
        }
        sum+=currentNode->m_r;
        *hight=sum;
        *column=columnsArr[currentNode->m_id];
    return StatusType ::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id){
    if (c_id < 0){
        return INVALID_INPUT;
    }
    int searchAnswer = membersHash.searchIfExists(c_id);
    if (searchAnswer == NOT_IN_HASH){
        return Output_t<bool>(DOESNT_EXISTS);
    }
    Costumer costumer = membersHash.search(c_id); //we know that the costumer is in the hash
    return Output_t<bool>(costumer.clubMember);
}

Output_t<double> RecordsCompany::getExpenses(int c_id){
    if (c_id < 0){
        return Output_t<double>(INVALID_INPUT);
    }
    if (membersTree.find(c_id) == 0){
        return Output_t<double>(DOESNT_EXISTS);
    }
    return Output_t<double>(membersTree.AvlTree<int, clubMember>::getExpensesOfCostumer(c_id));
}


StatusType RecordsCompany::makeMember(int c_id) {
    if (c_id < 0){
        return INVALID_INPUT;
    }
    int searchAnswer = membersHash.searchIfExists(c_id);
    if (searchAnswer == NOT_IN_HASH){
        return DOESNT_EXISTS;
    }
    Costumer costumerToUpdate = membersHash.search(c_id); //we know that the costumer is in the hash
    if (costumerToUpdate.clubMember){
        return ALREADY_EXISTS; //he is already a member
    }
    membersHash.makeMember(c_id); //update hash
    clubMember newClubMember(c_id, 0, 0);
    membersTree.insert(newClubMember);
    return SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount) {
    if (c_id1<0 || c_id1>c_id2 || amount<=0){
        return StatusType ::INVALID_INPUT;
    }
  membersTree.add(membersTree.root,c_id2,-amount);
  membersTree.add(membersTree.root,c_id1,amount);

  return StatusType ::SUCCESS;

}
//
// Created by shira on 02/06/2023.
//

#ifndef EX2_DS_CLASSES_H
#define EX2_DS_CLASSES_H

class clubMember{
public:
    clubMember(int c_id, int treeSaleAmount, int selfSaleAmount);
    int m_c_id;
    int treeSaleAmount;
    int selfSaleAmount;
};

class Costumer{
public:
    Costumer(int c_id, int phone);
    int m_c_id;
    int m_phoneNum;
    bool clubMember;
};

class Record{
public:
    Record(int r_id, int numCopies, int numOrders);
    int m_r_id;
    int m_numCopies;
    int m_numPurchases;
};


#endif //EX2_DS_CLASSES_H

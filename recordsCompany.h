#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "AvlTree.h"
#include "UnionFind.h"


class clubMember;
class Costumer;
class Record;

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
    clubMember* m_clubMember; //a ptr to his node in the tree
};

class Record{
public:
    Record(int r_id, int numCopies, int numOrders);
    int m_r_id;
    int m_numCopies;
    int m_numPurchases;
};




class RecordsCompany {
  private:
    AvlTree<int,clubMember> membersTree;


  public:
    UFNode** UFArray;
    UnionFind* UF;
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif

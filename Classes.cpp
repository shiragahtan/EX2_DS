//
// Created by shira on 02/06/2023.
//

#include "Classes.h"

Costumer::Costumer(int c_id, int phone) : m_c_id(c_id), m_phoneNum(phone), clubMember(false) {};

Record::Record(int r_id, int numCopies, int numPurchases) : m_r_id(r_id), m_numCopies(numCopies), m_numPurchases(numPurchases) {};

clubMember::clubMember(int c_id, int treeSaleAmount, int selfSaleAmount) : m_c_id(c_id), treeSaleAmount(0), selfSaleAmount(0){};

//
// Created by shira on 01/06/2023.
//

#include "recordsCompany.h"


Costumer::Costumer(int c_id, int phone) : m_c_id(c_id), m_phoneNum(phone), m_clubMember(nullptr) {};

Record::Record(int r_id, int numCopies, int numPurchases) : m_r_id(r_id), m_numCopies(numCopies), m_numPurchases(numPurchases) {};


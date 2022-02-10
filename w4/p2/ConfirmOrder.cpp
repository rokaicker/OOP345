/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "ConfirmOrder.h"

namespace sdds{

    ConfirmOrder::ConfirmOrder(const ConfirmOrder& src){
        *this = src;
    }

    ConfirmOrder::ConfirmOrder(ConfirmOrder&& src){
        *this = std::move(src);
    }

    ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& src){
        if(this != &src){
            delete [] m_orderArray;
            m_numOfConfirms = src.m_numOfConfirms;
            m_orderArray = new const Toy*[m_numOfConfirms];
            for (size_t i = 0; i < m_numOfConfirms; i++){
                m_orderArray[i] = src.m_orderArray[i];
            }
        }
        return *this;
    }

    ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& src){
        if(this != &src){
            delete [] m_orderArray;
            m_orderArray = src.m_orderArray;
            m_numOfConfirms = src.m_numOfConfirms;
            src.m_orderArray = nullptr;
            src.m_numOfConfirms = 0;
        }
        return *this;
    }

    ConfirmOrder::~ConfirmOrder(){
        delete [] m_orderArray;
    }


    ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy){
        bool check = false;
        for (size_t i = 0; i < m_numOfConfirms; i++){
            if (m_orderArray[i] == &toy){
                check = true;
            }
        }
        if(check == false){
            const Toy** temp = new const Toy*[m_numOfConfirms + 1];
            for (size_t i = 0; i < m_numOfConfirms; i++){
                temp[i] = m_orderArray[i];
            }
            delete [] m_orderArray;
            m_orderArray = temp;
            m_orderArray[m_numOfConfirms++] = &toy;
        }
        return *this;

    }

    ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy){
        bool check = false;
        size_t index{};
        for (size_t i = 0; i < m_numOfConfirms; i++){
            if (m_orderArray[i] == &toy){
                check = true;
                index = i;
            }
        }
        if (check == true){
            const Toy** temp = new const Toy*[m_numOfConfirms-1];
            for (size_t i = 0; i < m_numOfConfirms; i++){
                if (i < index){
                    temp[i] = m_orderArray[i];
                }
                if(i > index){
                    temp[i-1] = m_orderArray[i]; 
                }
            }
            delete [] m_orderArray;
            m_orderArray = temp;
            --m_numOfConfirms;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ConfirmOrder& CO){
    os << "--------------------------" << std::endl;
    os << "Confirmations to Send" << std::endl;
    os << "--------------------------" << std::endl;
    if (CO.m_numOfConfirms == 0){
        os << "There are no confirmations to send!" << std::endl;
    } else {
        for (size_t i = 0; i < CO.m_numOfConfirms; i++){
            os << CO.m_orderArray[i];
        }
    }
    os << "--------------------------" << std::endl;
    return os;
    }
}
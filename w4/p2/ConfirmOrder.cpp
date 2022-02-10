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
            m_orderArray = new Toy*[m_numOfConfirms];
            for (int i = 0; i < m_numOfConfirms; i++){
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

    }

    ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy){

    }

    std::ostream& operator<<(std::ostream& os, const ConfirmOrder& CO){
    os << "--------------------------" << std::endl;
    os << "Confirmations to Send" << std::endl;
    os << "--------------------------" << std::endl;
    if (){
        os << "There are no confirmations to send!" << std::endl;
    } else {
        for (int i = 0; i < ; i++){

        }
    }
    os << "--------------------------" << std::endl;
    return os;
    }
}
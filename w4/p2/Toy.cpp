/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "Toy.h"

namespace sdds{
    Toy::Toy(const std::string& toy){
        int endPos = 0;
        std::string tempStr = toy;
        std::string delim = ":";
        std::string innerTempStr;
        for (int i = 0; i < 4; i++){
            endPos = tempStr.find(delim);
            innerTempStr = tempStr.substr(0,endPos);
            if(innerTempStr[0] == ' ' ){
                innerTempStr.erase(0,1);
            } else if (innerTempStr.back() == ' '){
                innerTempStr.pop_back();
            }
            switch(i){
                case 0:
                    m_orderID = std::stoi(innerTempStr);
                    break;
                case 1:
                    m_name = innerTempStr;
                    break;
                case 2:
                    m_numItems = std::stoi(innerTempStr);
                    break;
                case 3:
                    int finalPos = innerTempStr.find('\n');
                    m_price = std::stod(innerTempStr.substr(0,finalPos));
                    break;
            }
            tempStr.erase(0,endPos + 1);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Toy& T){
        double subTot = T.m_price * T.m_numItems;
        double tax = T.m_tax * subTot;
        double total = tax + subTot;
        os.setf(std::ios::fixed);
        os.precision(2);
        os << "Toy";
        os.width(8);
        os << T.m_orderID << ":";
        os.width(18);
        os << T.m_name;
        os.width(3);
        os << T.m_numItems << " items";
        os.width(8);
        os << T.m_price << "/item subtotal:";
        os.width(7);
        os << subTot << " tax:";
        os.width(6);
        os << tax << " total:";
        os.width(7);
        os << total << std::endl;
        return os;
    }
}
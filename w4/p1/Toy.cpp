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

        for (int i = 0; i < 4; i++){
            endPos = tempStr.find(delim);
            switch(i){
                case 0:
                    m_orderID = std::stoi(tempStr.substr(0,endPos));
                    std::cout << m_orderID;
                    break;
                case 1:
                    m_name = tempStr.substr(0,endPos);
                    std::cout << m_name;
                    break;
                case 2:
                    m_numItems = std::stoi(tempStr.substr(0,endPos));
                    std::cout << m_numItems;
                    break;
                case 3:
                    int finalPos = tempStr.find('\n');
                    m_price = std::stod(tempStr.substr(0,finalPos));
                    std::cout << m_price;
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
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
        int begPos = 0;
        int endPos = 0;
        std::string subStr{};
        std::string delim = ":";

        for (int i = 0; i < 3; i++){
            endPos = toy.find(delim,begPos);
            switch(i){
                case 0:
                    m_orderID = std::stoi(toy.substr(begPos,endPos));
                    break;
                case 1:
                    m_name = toy.substr(begPos,endPos);
                    break;
                case 2:
                    m_numItems = std::stoi(toy.substr(begPos,endPos));
                    break;
                case 3:
                    m_price = std::stod(toy.substr(begPos,endPos));
                    break;
            }
            begPos = endPos + 1;
        }
    }

    std::ostream& operator<<(std::ostream& os, const Toy& T){

    }
}
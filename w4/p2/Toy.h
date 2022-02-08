/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef TOY_H
#define TOY_H
#include <string>
#include <iostream>

namespace sdds{
    const double hstTax{0.13};
    class Toy {
        unsigned m_orderID{};
        std::string m_name{};
        unsigned m_numItems{};
        double m_price{};
        double m_tax{hstTax};
    public:
        Toy(){};
        Toy(const std::string& toy);
        void update(int numItems) { m_numItems = numItems; };
        friend std::ostream& operator<<(std::ostream& os, const Toy& T);
    };

}

#endif
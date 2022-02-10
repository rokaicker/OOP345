/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef CONFIRMORDER_H
#define CONFIRMORDER_H
#include "Child.h"

namespace sdds{

    class ConfirmOrder{
        const sdds::Toy** m_orderArray{nullptr};
        size_t m_numOfConfirms{};

    public:
        ConfirmOrder(){};
        ConfirmOrder(const ConfirmOrder& src);
        ConfirmOrder(ConfirmOrder&& src);
        ConfirmOrder& operator=(const ConfirmOrder& src);
        ConfirmOrder& operator=(ConfirmOrder&& src);
        ~ConfirmOrder();
        ConfirmOrder& operator+=(const Toy& toy);
        ConfirmOrder& operator-=(const Toy& toy);
        friend std::ostream& operator<<(std::ostream& os, const ConfirmOrder& CO);

    };

}

#endif
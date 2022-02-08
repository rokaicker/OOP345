/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef CHILD_H
#define CHILD_H
#include "Toy.h"

namespace sdds{
    class Child{
        std::string m_name{};
        unsigned age{};
        const sdds::Toy** m_childArray{};
        static unsigned CALL_CNT;
    public:
        Child(std::string name, int age, const Toy* toys[], size_t count);
        size_t size() const;
        friend std::ostream& operator<<(std::ostream& os, const Child& C);

    };
}

#endif
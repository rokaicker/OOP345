/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "Child.h"

namespace sdds{
    Child::Child(std::string name, int age, const Toy* toys[], size_t count) : m_name{name}, m_age{age}, m_numOfToys{count}
    {
        m_childToyArray = new Toy*[m_numOfToys];
        for (int i = 0; i < m_numOfToys; i++){
            m_childToyArray[i] = toys[i];
        }
    }

    Child::Child(const Child& src){
        *this = src;
    }

    Child::Child(Child&& src){
        *this = std::move(src);
    }

    Child& Child::operator=(const Child& src){
        if(this != &src){
            delete [] m_childToyArray;
            m_name = src.m_name;
            m_age = src.m_age;
            m_numOfToys = src.m_numOfToys;
            for (int i = 0; i < m_numOfToys; i++){
                m_childToyArray[i] = src.m_childToyArray[i];
            }
        }
        return *this;
    }

    Child& Child::operator=(Child&& src){
        if (this != & src){
            delete [] m_childToyArray;
            m_childToyArray = src.m_childToyArray;
            m_name = src.m_name;
            m_age = src.m_age;
            m_numOfToys = src.m_numOfToys;
            src.m_childToyArray = nullptr;
            src.m_name = "";
            src.m_age = 0;
            src.m_numOfToys = 0;
        }
        return *this;
    }

    Child::~Child(){
        delete [] m_childToyArray;
    }
    
    std::ostream& operator<<(std::ostream& os, const Child& C){
        static unsigned CALL_CNT{};
        os << "--------------------------" << std::endl;
        os << "Child " << ++CALL_CNT << ": " << C.m_name << " " << C.m_age << " years old:" << std::endl;
        os << "--------------------------" << std::endl;
        if (C.m_numOfToys == 0){
            os << "This child has no toys!" << std::endl;
        } else {
            for (int i = 0; i < C.m_numOfToys; i++){
                os << C.m_childToyArray[i];
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }
}
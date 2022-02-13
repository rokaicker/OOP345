/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 13, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "CentralUnit.h"

namespace sdds{
    class Processor{
        CentralUnit<Processor>* m_host {nullptr};
        std::string m_brand{};
        std::string m_code{};
        size_t m_power{};
        Job* m_current{nullptr};
    public:
        Processor(CentralUnit<Processor>* host, std::string brand, std::string code, size_t power) : m_host{host}, m_brand{brand}, m_code{code}, m_power{power} {};

        void run();
        explicit operator bool() const;
        Processor& operator+=(Job*&);
        Job* get_current_job() const;
    };
}

#endif
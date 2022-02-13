/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef CENTRALUNIT_H
#define CENTRALUNIT_H
#include "Job.h"
namespace sdds{
    template <typename T>
    class CentralUnit{
        std::string m_type{};
        T** m_items{nullptr};
        Job* m_jobs[4];
        size_t m_size{};
        size_t m_count{};
    public:
        std::ostream& log{std::cout};
        CentralUnit(std::string type, char* fileName);
        CentralUnit(const CentralUnit& src)=delete;
        CentralUnit& operator=(const CentralUnit& src)=delete;

        CentralUnit& operator+=(std::string jobTitle);
        void run();
        bool has_jobs()const;
        int get_available_units()const;
    };
}

#endif
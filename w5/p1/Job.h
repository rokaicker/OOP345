/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef JOB_H
#define JOB_H
#include <iostream>

namespace sdds{
    class Job {
        std::string m_jobTitle{};   // Description of Job
        size_t m_workUnits{};       // Units of work to be done to finish job
        size_t m_remWorkUnits{};    // Remaining units of work to be done
        bool m_active{};            // Whether or not the current job is active
    public:
        Job() : m_jobTitle{""}, m_workUnits{0}, m_remWorkUnits{0}, m_active{false}{}
        Job(std::string title);
        
        bool is_active()const{return m_active;};
        bool is_complete()const{return m_remWorkUnits == 0;};
        std::string name()const{return m_jobTitle;};
        void display(std::ostream& os = std::cout)const;
        void operator()(size_t workUnits);
    };
    std::ostream& operator<<(std::ostream& os, const Job& J);
}

#endif
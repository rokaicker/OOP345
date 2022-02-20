/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "CentralUnit.h"
#include "Job.h"
#include <functional>

namespace sdds{
    class Processor{
        CentralUnit<Processor>* m_host{};   // Address of hosting central unit
        std::string m_brand{};                      // Name of brand of microprocessor aka unit type
        std::string m_code{};                       // Text description of microprocessor aka unit name                     
        size_t m_power{};                           // Number of work units microprocessor can proces for job in single run 
        Job* m_current{nullptr};                    // Address of job currently assigned to microprocessor to be processed

        void (*m_endFunc)(CentralUnit<Processor>& host,Processor* processor){nullptr}; // Stores address of funtion that will run once job finishes processing
        // void = return type of function, m_endFunc = name of pointer to function

        std::function<void(Processor* processor)> m_errFunc;                  // Function object that targets function to be run when an error occurs

    public:
        Processor(CentralUnit<Processor>* host, std::string brand, std::string code, size_t power) : m_host{host}, m_brand{brand}, m_code{code}, m_power{power} {};

        void run();
        explicit operator bool() const {return m_current != nullptr;};  // True if microprocessor has a job assigned to it
        Processor& operator+=(Job*& newJob);                            // Assigns a job to processor
        Job* get_current_job() const {return m_current;};               // Returns current job assigned to processor

        void on_complete(void (*endFunc)(CentralUnit<Processor>& host,Processor* processor));
        void on_error(std::function<void(Processor* processor)> errFunc);

        void Processor::operator()();
        Job* free();
        void display(std::ostream& os = std::cout)const;
    };
    std::ostream& operator<<(std::ostream& os, const Processor& P){
        P.display(os);
        return os;
    };
}

#endif
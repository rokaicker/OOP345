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
    class Processor;
    typedef CentralUnit<Processor> Host;
    using endFunc = void(Host::*)(Host&,Processor*);
    using errFunc = std::function<void(Processor*)>;

    class Processor{
        Host* m_host{};                     // Address of hosting central unit
        std::string m_brand{};              // Name of brand of microprocessor aka unit type
        std::string m_code{};               // Text description of microprocessor aka unit name                     
        size_t m_power{};                   // Number of work units microprocessor can proces for job in single run 
        Job* m_current{nullptr};            // Address of job currently assigned to microprocessor to be processed

        // Stores address of funtion that will run once job finishes processing
        // void = return type of function, m_endFunc = name of pointer to function
        // can also use void (Host::*m_endFunc)(Host& host,Processor* processor){nullptr};
        endFunc m_endFunc{nullptr}; // instantiate a variable of type endFunc, and assign it to nullptr

        // The below Function object that targets function to be run when an error occurs
        // can also use std::function<void(Processor* processor)> m_errFunc;     
        errFunc m_errFunc{nullptr}; // instantiate a variable of type errFunc, and assign it to nullptr

    public:
        Processor(Host* host, std::string brand, std::string code, size_t power) : m_host{host}, m_brand{brand}, m_code{code}, m_power{power} {};


        // Modifiers
        void run();
        Processor& operator+=(Job*& newJob);    // Assigns a job to processor
        void operator()();                      // Similar to run()
        Job* free();
        /* 
            The below member function sets m_endFunc to the function pointer passed. 
            Can also use void on_complete(void (Host::*endFunc)(Host& host,Processor* processor)){m_endFunc = endFunc;};
        */
        void on_complete(endFunc func){m_endFunc = func;};

        /*
            The below function sets m_errFunc to the function object passed
            Can also use void on_error(std::function<void(Processor* processor)> errFunc){m_errFunc = errFunc;};
        */
        void on_error(errFunc func){m_errFunc = func;};

        // Queries
        Job* get_current_job() const {return m_current;};               // Returns current job assigned to processor
        explicit operator bool() const {return m_current != nullptr;};  // True if microprocessor has a job assigned to it
        void display(std::ostream& os = std::cout)const;
    };

    std::ostream& operator<<(std::ostream& os, const Processor& P);
}

#endif
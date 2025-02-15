/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "Processor.h"
#include <string>

namespace sdds{
    void Processor::run(){
        if (m_host != nullptr && m_current != nullptr){
            if (m_current->is_complete()){
                delete m_current;
                m_current = nullptr;
            } else {
                try{
                    (*m_current)(m_power);
                } catch (...) {
                    std::cout << "Processed over quota for " << *m_current;
                    delete m_current;
                    m_current = nullptr;
                }
            }
        } 
    }

    Processor& Processor::operator+=(Job*& newJob){
        if(m_current != nullptr){
            throw std::exception();
        } else {
            //m_current = new Job(newJob->name());
            m_current = newJob;
        }
        return *this;
    }


    void Processor::operator()(){
        if (!(m_current->is_complete())){
            try{
                (*m_current)(m_power);

            } catch (...) {
                m_errFunc(this);
                // NOTE: The syntax m_host->*m_errFunc would have caused an error here because we are not calling a function that is a member function of m_host. m_errFunc was simply a function that was passed
                return;
            }
            if(m_current->is_complete()){
                if(m_endFunc != nullptr){
                    (m_host->*m_endFunc)(*m_host, this);
                    // NOTE: m_host->*m_endFunc syntax is required because we are calling a function that is a member function of the host type (CentralUnit). We need to use the ->* syntax because m_host is a pointer to type CentralUnit<Processor> and m_endFunc is a function pointer
                }
            }
        }
    }

    Job* Processor::free(){
        Job* temp = m_current;
        m_current = nullptr;
        return temp;
    }

    void Processor::display(std::ostream& os) const {
        os << "(" << m_power << ") " << m_brand << " " << m_code;
        if(m_current != nullptr){
            os <<" processing " << *m_current;
        }
    }
  
    std::ostream& operator<<(std::ostream& os, const Processor& P){
        P.display(os);
        return os;
    };
}
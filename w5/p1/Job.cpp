/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "Job.h"
#include <exception>
namespace sdds{
    Job::Job(std::string title) : m_jobTitle{title}, m_active{true} {
        m_workUnits = (m_jobTitle.length()%10) + 1;
        m_remWorkUnits = m_workUnits;
    }

    std::ostream& operator<<(std::ostream& os, const Job& J){
        J.display(os);
        return os;
    }

    void Job::display(std::ostream& os)const{
        os << "`" << m_jobTitle << "` ";
        os.fill('0');
        os <<  "[";
        os.width(2);
        os << m_remWorkUnits;
        os << "/";
        os.width(2);
        os << m_workUnits;
        os << " remaining]" << std::endl;
    }

    void Job::operator()(size_t workUnits){
        if(m_remWorkUnits < workUnits){
            m_remWorkUnits = 0;
            m_active = false;
            throw std::underflow_error("more work assigned than remaining");
        }
        else {
            m_remWorkUnits -= workUnits;
            if (is_complete()) m_active = false;
        }

    }
}
// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: March 22, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
namespace sdds
{
    // Global Variable Declaration
    extern std::deque<CustomerOrder> g_pending;         // this is worked on by ms3.cpp
    extern std::deque<CustomerOrder> g_completed;       // this is worked on by attemptToMoveOrder()
    extern std::deque<CustomerOrder> g_incomplete;      // this is worked on by attemptToMoveOrder()

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{nullptr};
    public:
        // 1-arg constructor
        Workstation(std::string& str) : Station(str){};

        // Modifiers
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation& operator+=(CustomerOrder&& newOrder);
        
        // Queries
        Workstation* getNextStation() const {return m_pNextStation;};
        void display(std::ostream& os) const;

    };


}

#endif // SDDS_WORKSTATION_H
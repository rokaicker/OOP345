// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds
{
    // Fills front order if m_orders is not empty
    void Workstation::fill(std::ostream& os)
    {
        if (!m_orders.empty()){
            m_orders.front().fillItem(*this, os);
        }
    }

    // Move front order at front to next station.
    //      If order requires no more service/ can't be filled do nothing
    //      If there is no next station, move it either into g_completed or g_incomplete
    //      If order was moved, return true, false otherwise.
    bool Workstation::attemptToMoveOrder()
    {
        std::string workstationItemName = getItemName();        // The item that the current workstation handles
        size_t workstationQuantity = getQuantity();             // Remaining quantity of item at current workstation
        bool orderMoved = false;
        bool nextStationExists = (m_pNextStation != nullptr);   // True if the nextStation exists

        if (!m_orders.empty()){
            if (((m_orders.front().isItemFilled(workstationItemName)) || workstationQuantity == 0) && nextStationExists){
                // move to next station, use operator += overload (pass order as r-value reference)
                // std::move returns rvalue reference of argument
                *m_pNextStation += std::move(m_orders.front());
                orderMoved = true;
            }
            else if (m_orders.front().isItemFilled(workstationItemName) && !nextStationExists){
                // move to g_completed
                g_completed.push_back(std::move(m_orders.front()));
                orderMoved = true;
            }
            else if (workstationQuantity == 0 && !nextStationExists){
                // move to g_incomplete
                g_incomplete.push_back(std::move(m_orders.front()));
                orderMoved = true;
            }
        }
        return orderMoved;
    }

    // Store address of next station in m_pNextStation
    void Workstation::setNextStation(Workstation* station)
    {
        m_pNextStation = station;
    }

    // Moves referenced CustomerOrder to back of queue
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

    void Workstation::display(std::ostream& os) const
    {
        os << getItemName() << " --> ";
        if (m_pNextStation == nullptr){
            os << "End of Line";
        } else {
            os << m_pNextStation->getItemName();
        }
        os << std::endl;
    }

    

}
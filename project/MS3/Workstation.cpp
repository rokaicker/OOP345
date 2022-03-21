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
                // move to next station
                orderMoved = true;
            }
            else if (m_orders.front().isItemFilled(workstationItemName) && !nextStationExists){
                // move to g_completed
                orderMoved = true;
            }
            else if (workstationQuantity == 0 && !nextStationExists){
                // move to g_incomplete
                orderMoved = true;
            }

        }
        return orderMoved;
    }
}
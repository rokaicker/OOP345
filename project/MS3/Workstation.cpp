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
        bool orderMoved = false;
        if (!m_orders.empty()){
            if (m_pNextStation != nullptr){
                
            } else if (m_orders.front().isOrderFilled() && m_pNextStation == nullptr){

            } else if (!(m_orders.front().isOrderFilled()) && m_pNextStation == nullptr){

            }
        }
        return orderMoved;
    }
}
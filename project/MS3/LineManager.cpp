// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <fstream>
#include "LineManager.h"

namespace sdds
{
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {

    }

    // Reorders workstations in m_activeLine to be in sequential order
    void LineManager::reorderStations()
    {

    }

    // Performs one iteration of operationson all workstations in m_activeLine
    bool LineManager::run(std::ostream& os)
    {

    }

    // Displays all active stations on assembly line in current order
    void LineManager::display(std::ostream& os) const
    {
        for (auto& e : m_activeLine){
            e->display(os);
        }
    }
}
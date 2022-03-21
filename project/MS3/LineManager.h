// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: 
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include "CustomerOrder.h"
#include "Workstation.h"

namespace sdds
{
    class LineManager
    {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{nullptr};
    public:
        // 2-arg constructor
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        // Modifiers
        void reorderStations();
        bool run(std::ostream& os);

        // Queries
        void display(std::ostream& os) const;
    };
}

#endif // SDDS_LINEMANAGER_H
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
        Utilities util{};
        bool more = true;
        size_t pos = 0u;
        std::string inputLine{};
        std::string innerInput{};

        char currentDelim = Utilities::getDelimiter();  // Storing current delimiter, will reset delimiter once constructor complete
        Utilities::setDelimiter('|');                   // Set delimiter to '|' as indicated in AssemblyLine.txt format

        Workstation* nextStation{nullptr};
        Workstation* firstStation{nullptr};

        std::ifstream fs(file);
        if(!fs.is_open()){
            throw std::string("Can't Open File " + file);
        }

        while(getline(fs, inputLine))
        {

        }

        Utilities::setDelimiter(currentDelim);
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
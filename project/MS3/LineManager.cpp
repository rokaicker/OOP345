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
        Workstation* inputWorkstation{nullptr};
        std::string nextStationStr{};
        std::string firstStationStr{};
        std::string inputWorkstationStr{};


        std::ifstream fs(file);
        if(!fs.is_open()){
            throw std::string("Can't Open File " + file);
        }
        // Read each line, get name of a workstation and it's next workstation (if it has a next workstation)
        //      need to find which workstation in the stations vector has the same name
        while(getline(fs, inputLine))
        {
            inputWorkstationStr = util.extractToken(inputLine, pos, more);
            inputWorkstation = *(std::find_if(stations.begin(), stations.end(),
                [inputWorkstationStr](const Workstation* src){return src->getItemName() == inputWorkstationStr;}));
            if (more == true) {
                nextStationStr = util.extractToken(inputLine, pos, more);
                nextStation = *(std::find_if(stations.begin(), stations.end(), 
                    [nextStationStr](const Workstation* src){return src->getItemName() == nextStationStr;}));
                inputWorkstation->setNextStation(nextStation);
            }
            // Pushing inputted work station to active line vector
            m_activeLine.push_back(inputWorkstation);
        }

        // Look for first station (first station will not be the "next station" for any other station)
        Workstation* currentIteration{nullptr};

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
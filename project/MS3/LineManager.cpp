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
        //  Create a vector of all "next stations"
        std::vector<std::string> nextStations;
        for_each(m_activeLine.begin(), m_activeLine.end(), 
            [&nextStations](Workstation* src){
                if (src->getNextStation() != nullptr){
                    nextStations.push_back(src->getNextStation()->getItemName());
                }
            });
        // Compare m_activeLine names to nextStations, any name that doesn't exist in nextStations will be the first station
        // Below the program goes through every workstation in m_activeLine and compares the workstation name to the vector of names in nextStations. 
        // If the none of the elements in nextStations have a name equal to the current workstation iteration in m_activeLine, this means that workstation must be the first station. 
        for_each(m_activeLine.begin(), m_activeLine.end(), 
            [&](Workstation* wrkstn){
                if(std::none_of(nextStations.begin(), nextStations.end(), 
                    [&](std::string name){
                        return name == wrkstn->getItemName();
                    })){
                        m_firstStation = wrkstn;
                    }
            });

        Utilities::setDelimiter(currentDelim);  // reset delimiter to original delimiter

        // ms3.cpp moves all orders to g_pending right before construction of the line manager
        m_cntCustomerOrder = g_pending.size();
    }

    // Reorders workstations in m_activeLine to be in sequential order
    void LineManager::reorderStations()
    {
        std::vector<Workstation*> temp;
        temp.push_back(m_firstStation);
        Workstation* currentStation = m_firstStation->getNextStation();
        do {
            temp.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }while (currentStation != nullptr);
        m_activeLine = temp;
    }

    // Performs one iteration of operations all workstations in m_activeLine
    bool LineManager::run(std::ostream& os)
    {
        bool check = false;
        static int currentIteration = 1;
        os << "Line Manager Iteration: " << currentIteration++ << std::endl;
        if (!g_pending.empty()){
            *m_firstStation += std::move(g_pending.front());
            g_pending.erase(g_pending.begin()); // need to erase the moved position
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&](Workstation* src){
                src->fill(os);
            });
        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&](Workstation* src){
                src->attemptToMoveOrder();
            });
        /*if (g_pending.size() == 0){
            check = true;
        }*/
        /* objects containing customer orders include:
                1) g_pending
                2) g_completed
                3) g_incomplete
                4) each workstation also has m_orders
            total customer orders = m_cntCustomerOrder (lineManager membervariable)
            at the end of the program all customer orders should be in g_completed and g_incomplete (their final destinations, they never move out of there)
        */
        if ((g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder){
            check = true;
        }
        return check;
    }

    // Displays all active stations on assembly line in current order
    void LineManager::display(std::ostream& os) const
    {
        for (auto& e : m_activeLine){
            e->display(os);
        }
    }
}
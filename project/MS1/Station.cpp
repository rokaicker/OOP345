// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"

namespace sdds{
    // Static Class Variables initialization
    int Station::id_generator = 0;
    size_t Station::m_widthField = 0;

    Station::Station(const std::string& inputLine){
        // delimiter used by utilities object already set by client code
        m_stationID = ++id_generator;
        Utilities util{};
        bool more = true; 
        size_t pos = 0u;

        // Extracting name
        m_itemName = util.extractToken(inputLine, pos, more);

        // Extracting serial number, need to convert string to integer
        m_nextSerial = std::stoi(util.extractToken(inputLine, pos, more));

        // Extracting items in stock, need to convert string to integer then cast size_t
        m_itemsInStock = static_cast<size_t>(std::stoi(util.extractToken(inputLine, pos, more)));

        //Updating station::m_widthField
        if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();

        // Extracting Description
        m_stationDescription = util.extractToken(inputLine, pos, more);
    }

    void Station::display(std::ostream& os, bool full) const{
        os << std::setw(3) << std::right << std::setfill('0') << m_stationID << " | ";
        os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_itemName << " | ";
        os << std::setw(6) << std::right << std::setfill('0') << m_nextSerial << " | " << std::setfill(' ') ;
        if (full){
            os << std::setw(4) << std::right << m_itemsInStock << " | ";
            os << std::left << m_stationDescription;
        }
        os << std::endl;
    }
}

// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: March , 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>
#include <iomanip>

namespace sdds{
    class Station {
        // Instance Variables  
        int m_stationID{};           
        std::string m_itemName{};               // Name of item handled by station
        std::string m_stationDescription{}; 
        unsigned int m_nextSerial{};            // Next serial number to be assigned to item
        size_t m_itemsInStock{};                // Number of items in stock
    public:
        // Class Variables
        static size_t m_widthField;             // Max characters required to print itemName
        static int id_generator;                // Generates new IDs, increments by 1 each time new instance created

        Station(const std::string& inputLine);  // 1-arg constructor

        // Modifiers
        size_t getNextSerialNumber(){return m_nextSerial++;};
        void updateQuantity() {if (m_itemsInStock > 0) m_itemsInStock--;};


        // Queries
        const std::string& getItemName() const{return m_itemName;};
        size_t getQuantity() const {return m_itemsInStock;};
        void display(std::ostream& os, bool full)const;
    };
}


#endif
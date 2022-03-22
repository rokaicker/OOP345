// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: March 22, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
#include <algorithm>
#include <iostream>

namespace sdds{
    // Initialize static variable
    char Utilities::m_delimiter{};

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more){
        
        size_t delimPos = str.find(m_delimiter, next_pos);
        if (delimPos == std::string::npos || delimPos == next_pos) {
            more = false;
        }
        else {
            more = true;
        }

        std::string returnStr{};

        if (delimPos == std::string::npos) {
            returnStr = str.substr(next_pos);
        }
        else {
            returnStr = str.substr(next_pos, delimPos - next_pos);
        }
        // Exception thrown if delimiter found at next_pos
        if (delimPos == next_pos) {
            throw std::string("Delimiter found at next position");
        }

        returnStr = trim(returnStr);

        if (returnStr.size() > m_widthField){
            m_widthField = returnStr.size();
        }

        next_pos = (size_t)(delimPos + 1);
        return returnStr;
    }
}
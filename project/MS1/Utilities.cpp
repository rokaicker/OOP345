// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds{
    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more){

        // Exception thrown if delimiter found at next_pos
        if (str.at(next_pos) == m_delimiter){
            throw std::string("Delimiter found at next position");
        }

        size_t delimPos = str.find_first_of(str, next_pos);
        std::string returnStr = str.substr(next_pos, delimPos - next_pos);
        if (returnStr.size() > m_widthField){
            m_widthField = returnStr.size();
        }

        return returnStr;
    }
}
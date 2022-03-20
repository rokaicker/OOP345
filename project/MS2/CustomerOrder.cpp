// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: March , 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include "CustomerOrder.h"

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& str)
    {
        Utilities util{};   // Local utilities object to extract tokens from str
        bool more = true;
        size_t pos = 0u;

        // Extracting customer name
        m_name = util.extractToken(str, pos, more);

        // Extracting order/ product name
        m_product = util.extractToken(str, pos, more);

        // Instantiating/ Filling dynamic array of Item pointers
        // Number of items = number of delimiters + 1
        m_cntItem = std::count(str.begin(), str.end(), util.getDelimiter()) + 1;
        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0u; i < m_cntItem; i++){
            std::string itemName = util.extractToken(str,pos,more);
            m_lstItem[i] = new Item(itemName);
        }

        // Updating CustomerOrder::m_widthField
        if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();
    }

}
// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: 
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <iomanip>
#include <vector>
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
        // Number of items = number of delimiters - 1
        m_cntItem = std::count(str.begin(), str.end(), util.getDelimiter()) - 1;
        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0u; i < m_cntItem; i++){
            std::string itemName = util.extractToken(str,pos,more);
            m_lstItem[i] = new Item(itemName);
        }

        // Updating CustomerOrder::m_widthField
        if (m_widthField < util.getFieldWidth()) m_widthField = util.getFieldWidth();
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
    {
        *this = std::move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
    {
        if (this != &src){
            // Deallocate current resources
            for (size_t i = 0u; i < m_cntItem; i++){
                delete m_lstItem[i];
            }
            delete [] m_lstItem;
            m_lstItem = src.m_lstItem;
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;

            src.m_lstItem = nullptr;
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0u;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0u; i < m_cntItem; i++){
                delete m_lstItem[i];
        }   
        delete [] m_lstItem;
    }

    // isOrderFilled() returns true if all items in order have been filled
    bool CustomerOrder::isOrderFilled() const
    {
        bool check = true;
        for (size_t i = 0u; i < m_cntItem; i++){
            if (m_lstItem[i]->m_isFilled == false){
                check = false;
                break;
            }
        }
        return check;
    }

    // isItemFilled() returns true if items specified by itemName have been filled, or if itemName can't be found.
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        bool check = true;
        for (size_t i = 0u; i < m_cntItem; i++){
            if (m_lstItem[i]->m_itemName == itemName){
                if (m_lstItem[i]->m_isFilled == false){
                    check = false;
                    break;
                }
            }
        }
        return check;
    }

    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0u; i < m_cntItem; i++){
            os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
            if (m_lstItem[i]->m_isFilled){
                os << "FILLED";
            } else {
                os << "TO BE FILLED";
            }
            os << std::endl;
        }
    }

    // fillItem() fills ONE item in current order that station handles
    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        std::vector<std::string> itemsFilledOnce;   // vector that keeps track of which items have been filled in the current run of fillItem()
        for (size_t i = 0u; i < m_cntItem; i++){
            if ((station.getItemName() == m_lstItem[i]->m_itemName) && (station.getQuantity() > 0))
            {
                if (std::find(itemsFilledOnce.begin(), itemsFilledOnce.end(), station.getItemName()) == itemsFilledOnce.end())
                {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    itemsFilledOnce.push_back(station.getItemName());
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                }
            }
            else if ((station.getItemName() == m_lstItem[i]->m_itemName) && (station.getQuantity() == 0))
            {
                os << "Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
            }
        }
    }

}
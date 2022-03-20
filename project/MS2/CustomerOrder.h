// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: March , 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>

namespace sdds
{
    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};
        Item(const std::string& src) : m_itemName(src){};
    };

    class CustomerOrder
    {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{nullptr};
    public:
        static size_t m_widthField;

        CustomerOrder(){};                      // Default Constructor
        CustomerOrder(const std::string& str);  // 1-arg constructor

        // Rule of Five - Note that copy operations are not allowed, thus the copy operator throws an exception and the copy assignment operator has been deleted
        CustomerOrder(const CustomerOrder& src){throw std::string("Not allowed to perform copy operations");};
        CustomerOrder& operator=(const CustomerOrder& src) = delete;
        CustomerOrder(CustomerOrder&& src) noexcept;
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;
        ~CustomerOrder();

        // Query Functions
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void display(std::ostream& os) const;

        // Modifier Functions
        void fillItem(Station& station, std::ostream& os);
    };

}

#endif // SDDS_CUSTOMERORDER_H
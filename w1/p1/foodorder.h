/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: January 23, 2022
*/
#ifndef FOODORDER_H
#define FOODORDER_H
#include <iostream>
#include <fstream>
extern double g_taxrate;							// Tax rate
extern double g_dailydiscount;						// Discount 

namespace sdds {
	class FoodOrder {
		char m_customer[10]{};						// Customer name
		char* m_foodDescription = nullptr;			// Description of food
		double m_price;								// Price of food
		bool m_dailySpecial;						// True if order is a daily special
	public:
		FoodOrder();								// Default Constructor
		FoodOrder(const FoodOrder& FO);				// Copy Constructor
		FoodOrder& operator=(const FoodOrder& FO);	// Copy Assignment Operator
		~FoodOrder();								// Destructor
		void read(std::istream& is);
		void display()const;
	};

}
#endif

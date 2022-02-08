/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: January 23, 2022
*/
#include "foodorder.h"
#include <cstring>
#include <string>
#include <iomanip>

double g_taxrate;
double g_dailydiscount;

namespace sdds {
	// Default FoodOrder Constructor
	FoodOrder::FoodOrder()
		: m_price{-1}, m_dailySpecial{false}
	{
	}

	// Destructor
	FoodOrder::~FoodOrder() {
		delete[] m_foodDescription;
	}

	// Copy Constructor
	FoodOrder::FoodOrder(const FoodOrder& FO) {
		if (FO.m_customer != nullptr && FO.m_customer[0] != '\0' && FO.m_foodDescription != nullptr && FO.m_foodDescription[0] != '\0') {
			delete[] m_foodDescription;
			m_foodDescription = nullptr;
			m_foodDescription = new char[strlen(FO.m_foodDescription) + 1];
			strcpy(m_foodDescription, FO.m_foodDescription);
			strcpy(m_customer, FO.m_customer);
			m_price = FO.m_price;
			m_dailySpecial = FO.m_dailySpecial;
		}
		else {
			delete[] m_foodDescription;
			m_foodDescription = nullptr;
			m_customer[0] = '\0';
			m_price = -1;
			m_dailySpecial = false;
		}
	}

	// Copy Assignment Overload
	FoodOrder& FoodOrder::operator=(const FoodOrder& FO) {
		if (this != &FO) {
			if (FO.m_customer != nullptr && FO.m_customer[0] != '\0' && FO.m_foodDescription != nullptr && FO.m_foodDescription[0] != '\0') {
				delete[] m_foodDescription;
				m_foodDescription = nullptr;
				m_foodDescription = new char[strlen(FO.m_foodDescription) + 1];
				strcpy(m_foodDescription, FO.m_foodDescription);
				strcpy(m_customer, FO.m_customer);
				m_price = FO.m_price;
				m_dailySpecial = FO.m_dailySpecial;
			}
			else {
				delete[] m_foodDescription;
				m_foodDescription = nullptr;
				m_customer[0] = '\0';
				m_price = -1;
				m_dailySpecial = false;
			}
		}
		return *this;
	}

	void FoodOrder::read(std::istream& is) {
		// Resetting "this" instance member variables to default values
		m_customer[0] = '\0';
		delete[] m_foodDescription;
		m_foodDescription = nullptr;
		m_price = -1;
		m_dailySpecial = false;

		// Setting up temporary variables to store data before confirmation
		char tempCustomer[10];
		std::string tempFoodDescription;
		double tempPrice = -1;
		char tempDailySpecial = '\0'; // Variable to compare whether incoming daily special status is a 'Y' or a 'N'

		is.get(tempCustomer, 10, ',');
		is.ignore();
		getline(is, tempFoodDescription, ',');
		is >> tempPrice;
		is.ignore();
		is >> tempDailySpecial;

		if (is.good()) {
			strcpy(m_customer, tempCustomer);
			m_foodDescription = new char[strlen(tempFoodDescription.c_str()) + 1];
			strcpy(m_foodDescription, tempFoodDescription.c_str());
			m_price = tempPrice;
			if (tempDailySpecial == 'Y') {
				m_dailySpecial = true;
			}
			else {
				m_dailySpecial = false;
			}
		}
	}
	void FoodOrder::display()const {
		static int counter = 0;
		counter++;
		double priceWTax = (1.00 + g_taxrate) * m_price;
		double specialPrice = priceWTax - g_dailydiscount;

		if (m_customer[0] == '\0') {
			std::cout.setf(std::ios::left);
			std::cout.width(2);
			std::cout << counter << ". No Order" << std::endl;
		}
		else {
			std::cout.setf(std::ios::left);
			std::cout.width(2);
			std::cout << counter << ". ";
			std::cout.width(10);
			std::cout << m_customer << "|";
			std::cout.width(25); 
			std::cout << m_foodDescription << "|";
			std::cout.width(12);
			std::cout.setf(std::ios::fixed);
			std::cout.precision(2);
			std::cout << priceWTax << "|";
			if (m_dailySpecial == true) {
				std::cout.unsetf(std::ios::left);
				std::cout.width(13);
				std::cout << specialPrice;
			}
			std::cout << std::endl;
		}

	}

}
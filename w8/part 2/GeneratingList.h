/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: March 18, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {

	// Generating List is a templated class that retrieves list of records in a file, holds elements in VECTOR, and then provides access to them by index and displays elements to output stream
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:
		// Default constructor (empty)
		GeneratingList(){}

		// 1-arg Constructor takes file name and opens file. 
		// If no exception thrown, it will assume that the templated type has a member function called load() which it will use to fill up the member vector "list"
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }

		// Index operator overload to return the value at that position in the list vector
		const T& operator[](size_t i) const { return list[i]; }


		// The logic for the Luhn algorithm was taken from the wikipedia page https://en.wikipedia.org/wiki/Luhn_algorithm#Example_for_validating_check_digit
		bool luhn(std::string sin){
			int numOfDigits = sin.length();
			int sum = sin[numOfDigits-1] - '0';	
			// The sum is initiailzed to the second last digit in the SIN (since the check number is already included we have to ignore the last number)
			int parity = (numOfDigits - 2) % 2; 		// Basically this variable will help us in determining which digits need to be multiplied by 2
			for (int i = 0; i <= numOfDigits -2; i++){
				int digit = sin[i] - '0';
				if (i % 2 == parity){
					digit = digit * 2;
				}
				if (digit > 9){
					digit = digit - 9;
				}
				sum = sum + digit;
			}
			return ((sum % 10) == 0);
		}

		// Function below receives an address to a T object (RAW POINTER). Then it pushes the object to the end of the list vector.
		void operator+=(T* newObj){
			list.push_back(*newObj);
		}

		// Function below receives an address to a T object (SMART POINTER). Then it pushes the object to the end of the list vector.
		void operator+=(std::shared_ptr<T> newObj){
			list.push_back(*newObj);
		}




		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H

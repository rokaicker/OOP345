/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: January 30, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef PROTEINDATABASE_H
#define PROTEINDATABASE_H
#include <string>
#include <fstream>

namespace sdds {

	class ProteinDatabase {

		size_t m_proteinCount{};			// tracks size of array

		std::string* m_proteinArray{};	// Dynamically alloacted array of strings


	public:
		ProteinDatabase();								// 0-arg default constructor
		ProteinDatabase(const std::string fileName);	// 1-arg constructor

		ProteinDatabase(const ProteinDatabase& PD);		// Copy constructor

		ProteinDatabase& operator=(const ProteinDatabase& PD); // copy assignment operator overload
		
		ProteinDatabase(ProteinDatabase&& PD)noexcept;			// Move Constructor

		ProteinDatabase& operator=(ProteinDatabase&& PD)noexcept;	// Move Assignment operator


		size_t size() const;							// query that returns number of protein sequences in the current object
		
		std::string operator[](size_t index) const;			// query that returns copy of protein sequence at index received by parameter (if valid index)
		
		~ProteinDatabase();								// Destructor
	};

}

#endif 
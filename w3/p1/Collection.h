/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 6, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef COLLECTION_H
#define COLLECTION_H
#include "Pair.h"
#include <iostream>

namespace sdds {

	template<typename T, unsigned CAPACITY>
	class Collection {
		T m_array[CAPACITY]{};
		size_t m_count{};
		T m_dummy{};

	public:
		size_t size() const { return m_count; }
		void display(std::ostream& os = std::cout) const {
			os << "----------------------" << std::endl << "| Collection Content |" << std::endl << "----------------------" << std::endl;
			for (unsigned i = 0; i < size(); i++) {
				os << m_array[i] << std::endl;
			}
			os << "----------------------" << std::endl;
		};

		bool add(const T& item) {
			if (m_count == CAPACITY) { return false; }
			m_array[m_count++] = item;
			return true;
		};

		T& operator[](unsigned index) {
			if (index < 0 || index >= m_count) { return m_dummy; }
			return m_array[index];
		};
	};

	template<>
	class Collection<Pair, 100> {
		Pair m_array[100];
		size_t m_count{};
		Pair m_dummy{};


	public:
		size_t size() const { return m_count; }
		void display(std::ostream& os = std::cout) const {
			os << "----------------------" << std::endl << "| Collection Content |" << std::endl << "----------------------" << std::endl;
			for (unsigned i = 0; i < m_count; i++) {
				os << m_array[i] << std::endl;
			}
			os << "----------------------" << std::endl;
		};

		bool add(const Pair& item) {
			if (m_count == 100) { return false; }
			m_array[m_count++] = item;
			return true;
		};

		Pair& operator[](unsigned index) {
			if(index < 0 || index >= m_count) { return m_dummy;}
			return m_array[index];
		};

		Collection() : m_dummy("No Key", "No Value") {};

	};
}

#endif


/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 6, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SET_H
#define SET_H
#include <cmath>
#include "Collection.h"

namespace sdds {
	template <typename T>
	class Set : public Collection<T, 100> {
	public:
		bool add(const T& item) {
			if (this->m_count == 100) { return false; }
			for (unsigned i = 0; i < this->m_count; i++) {
				if (this->m_array[i] == item) {
					return false;
				}
			}
			return Collection<T, 100>::add(item);
		}
	};

	template<>
	class Set<double> : public Collection<double, 100> {
	public:
		bool add(const double& item) {
			if (this->m_count == 100) { return false; }
			for (unsigned i = 0; i < this->m_count; i++) {
				if (fabs(this->m_array[i] - item) < 0.01) {
					return false;
				}
			}
			return Collection<double, 100>::add(item);
		}
	};
}

#endif
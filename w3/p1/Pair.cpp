/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 6, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "Pair.h"
namespace sdds {

	void Pair::displayPair(std::ostream& os) const {
		os.width(20);
		os << m_key << ": ";
		os.setf(std::ios::left);
		os << m_value;
		os.unsetf(std::ios::left);
	}

	std::ostream& operator<<(std::ostream& os, const Pair& P) {
		P.displayPair(os);
		return os;
	}
}
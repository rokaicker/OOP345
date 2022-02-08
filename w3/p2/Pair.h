/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 6, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef PAIR_H
#define PAIR_H
#include <string>
#include <iostream>
namespace sdds {
	
	class Pair {
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() const { return m_key; }
		const std::string& getValue() const { return m_value; }
		Pair() {};
		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};
		void displayPair(std::ostream& os)const;
		bool operator==(const Pair& P)const;
	};
	std::ostream& operator<<(std::ostream& os, const Pair& P);


}

#endif
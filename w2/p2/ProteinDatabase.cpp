/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: January 30, 2022
* 
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "ProteinDatabase.h"
#include <iostream>
#include <utility>

namespace sdds {

	ProteinDatabase::ProteinDatabase() {
		m_proteinArray = nullptr;
		m_proteinCount = 0;
	}

	ProteinDatabase::ProteinDatabase(const std::string fileName) {
		m_proteinCount = 0;
		m_proteinArray = nullptr;
		int innerCount = 0;
		std::ifstream fin;
		std::string inputLine;
		fin.open(fileName);
		if (fin.is_open()) {
			while (fin.good()) {
				std::getline(fin, inputLine);
				if (inputLine[0] == '>') {
					++m_proteinCount;
				}
			}
			m_proteinArray = new std::string[m_proteinCount];
			fin.clear();	// clears EOF flag
			fin.seekg(0);	// returns to top of file
			while (fin.good()) {
				std::string concatProteinSeq;
				std::string inputString;
				if (fin.peek() == '>') {
					fin.ignore(200, '\n');
				}
				else {
					while (fin.peek() != '>') {
						std::getline(fin, inputString);
						concatProteinSeq += inputString;
						if (fin.peek() == EOF) {
							break;
						}
					}
					m_proteinArray[innerCount] = concatProteinSeq;
					concatProteinSeq = "";
					++innerCount;
				}
			}
		}
		fin.close();
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& PD) {
		delete[] m_proteinArray;
		m_proteinArray = nullptr;
		m_proteinCount = 0;
		*this = PD;
	}


	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& PD) {
		if (this != &PD) {
			delete[] m_proteinArray;
			m_proteinCount = PD.size();
			m_proteinArray = new std::string[m_proteinCount];
			for (size_t i = 0; i < m_proteinCount; i++) {
				m_proteinArray[i] = PD[i];
			}
		}
		return *this;
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& PD) noexcept {
		*this = std::move(PD);

	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& PD) noexcept {
		if (this != &PD) {
			delete[] m_proteinArray;
			m_proteinArray = PD.m_proteinArray;
			PD.m_proteinArray = nullptr;
			m_proteinCount = PD.m_proteinCount;
			PD.m_proteinCount = 0;
		}
		return *this;
	}


	ProteinDatabase::~ProteinDatabase() {
		delete[] m_proteinArray;
	}

	size_t ProteinDatabase::size()const {
		return m_proteinCount;
	}

	std::string ProteinDatabase::operator[](size_t index)const {
		std::string returnString;
		if (index < 0 || index > (m_proteinCount - 1) || m_proteinArray == nullptr) {
			returnString = "";
		}
		else {
			returnString = m_proteinArray[index];
		}
		return returnString;
	}
}
#ifndef SDDS_EMPPROFILE_H
#define SDDS_EMPPROFILE_H

#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>

namespace sdds {
	// Employee struct that holds employee id and name.
	struct Employee {
		std::string id;
		std::string name;

		// Load function takes file stream, and from file stream it stores id and name values in object.
		bool load(std::ifstream& f) {
			f >> id >> name;
			return f.good();
		}

		// Prints id and name 
		void print(std::ostream& os) const {
			os << std::setw(10) << id << std::setw(7) << name << std::endl;
		}
	};
	
	// Salary struct holds employee id and salary.
	struct Salary {
		std::string id;
		double salary;

		// Load function takes file stream and from file stream it loads id and salary values into object.
		bool load(std::ifstream& f) {
			f >> id >> salary;
			return f.good();
		}

		// Prints id and salary.
		void print(std::ostream& os) const {
			os << std::setw(10) << id << std::setw(10) << salary << std::endl;
		}
	};

	
	struct EmployeeWage {
		std::string name{};
		double m_salary{};
		int m_counter{};
		static int recCount;
		static bool Trace;

		// Default Constructor increments static variable recCount to keep track of number of employees, then it stores this value in m_counter.
		// If the boolean variable "TRACE" is true, it will output the value of m_counter.
		EmployeeWage() {
			m_counter = ++recCount;
			if (Trace)
			{
				std::cout << "Default Constructor [" << m_counter << "]" << std::endl;
			}
		}

		// 2-arg constructor receives a string and a double that represent the employee name and salary respectively. 
		// Again, static variabl recCount is incremented and value stored in m_counter.
		// value of m_counter is then outputted. 
		EmployeeWage(const std::string& str, double sal)
		{
			this->name = str;
			this->m_salary = sal;
			m_counter = ++recCount;
			if (Trace)
			{
				std::cout << "Ovdrloaded Constructor"<<std::setw(6)<<"[" << m_counter << "]" << std::endl;
			}
		}

		// Copy Constructor
		EmployeeWage(const EmployeeWage& copyEmpProf) {
			this->name = copyEmpProf.name;
			this->m_salary = copyEmpProf.m_salary;
			m_counter = ++recCount;
			if (Trace)
			{
				std::cout << "Copy Constructor "<< std::setw(11) << "[" << m_counter << "] from [" << copyEmpProf.m_counter <<"]" << std::endl;
			}
		}

		// Destructor
		~EmployeeWage() {
			if (Trace)
			{
				std::cout << "Destructor "<< std::setw(17) << "[" << m_counter << "]" << std::endl;
			}
		}
		
		//Validates that the employee salary is within the range of 0 to 9999 (inclusive). 
		//Reports an exception otherwise.
		void rangeValidator() {
			if (m_salary < 0 || m_salary > 99999){
				throw std::string("*** Employees salaray range is not valid");
			}
		}

		// Prints the employe name and salary
		void print(std::ostream& os)const {
			os << std::setw(15) << name << std::setw(10) << m_salary<<std::endl;
		}

	};
}
#endif // !SDDS_EMPPROFILE_H

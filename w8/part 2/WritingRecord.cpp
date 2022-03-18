#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		// Validate salary using rangeValidator()
		// Validate SIN using luhn()
		// Recall that generatinglist objects have had index operator overloaded and size() returns the size of the vector member

		for (size_t i = 0; i < emp.size(); i++) {
			for (size_t j = 0; j < sal.size(); j++){
				if (emp[i].id == sal[j].id){
					
					// If same id exists, create new dynamic employee wage
					EmployeeWage* tempD = new EmployeeWage(emp[i].name, sal[j].salary);

					// Validation of EmployeeWage based on salary
					try {
						tempD->rangeValidator();
					} catch (...) {
						delete tempD;
						tempD = nullptr;
						throw;	// continue throwing so that the main() function can deal with the caught exception
					}

					// Validation of EmployeeWage based on SIN
					if(activeEmp.luhn(emp[i].id)){
						activeEmp += tempD;
					} else {
						delete tempD;
						tempD = nullptr;
						throw std::string ("The employee SIN did not pass the Luhn algorithm");
					}
					delete tempD;
					tempD = nullptr;
					break;	// break down to get out of the inner for loop and move onto the next iteration in the outer for loop
				}
			}
		}
		return activeEmp;
	}

		GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		// TODO: Add your code here to build a list of employees
		//         using smart pointers
		
		for (size_t i = 0; i < emp.size(); i++){
			for (size_t j = 0; j < sal.size(); j++){
				if (emp[i].id == sal[j].id){
					std::shared_ptr<EmployeeWage> tempD(new EmployeeWage(emp[i].name, sal[j].salary));
					tempD->rangeValidator();
					if (activeEmp.luhn(emp[i].id)){
						activeEmp += tempD;
					} else {
						throw std::string ("The employee SIN did not pass the Luhn algorithm");
					}
					break;
				}
			}
		}
		return activeEmp;
	}


}
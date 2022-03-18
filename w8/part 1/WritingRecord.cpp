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
					EmployeeWage* temp = new EmployeeWage(emp[i].name, sal[j].salary);
					// Validation of EmployeeWage based on salary and SIN(ID)
					temp->rangeValidator();	// This returns nothing, but if validation fails an exception will be thrown and the below code won't be executed
					if(activeEmp.luhn(emp[i].id)){
						activeEmp += temp;
					} else {
						throw std::string ("The employee SIN did not pass the Luhn algorithm");
					}
					delete temp;
					temp = nullptr;
					break;	// break down to get out of the inner for loop and move onto the next iteration in the outer for loop
				}
			}
		}
		return activeEmp;
	}
}
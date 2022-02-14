/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: February 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef CENTRALUNIT_H
#define CENTRALUNIT_H
#include "Job.h"
#include <fstream>
namespace sdds{
    template <typename T>
    class CentralUnit{
        std::string m_type{};
        T** m_items{nullptr};
        Job* m_jobs[4];
        size_t m_size{};
        size_t m_count{};
    public:
        std::ostream& log{std::cout};
        CentralUnit(std::string type, char* fileName);
        CentralUnit(const CentralUnit& src)=delete;
        CentralUnit(CentralUnit&& src)=delete;
        CentralUnit& operator=(const CentralUnit& src)=delete;
        CentralUnit& operator=(CentralUnit&& src)=delete;

        CentralUnit& operator+=(std::string jobTitle);
        void run();
        bool has_jobs()const;
        int get_available_units()const;
    };

    template<typename T>
    CentralUnit<T>::CentralUnit(std::string type, char* fileName) : m_type{type} {
        std::string inputLine;
        std::string innerInput;
        int endPos{};

        std::string unitType;
        std::string unitName;
        std::string workCapacityStr;
        size_t workCapacity;

        ifstream fs(fileName);
        while(getline(fs, inputLine)){
            for (int i = 0; i < 3; i++){
                switch(i){
                    case 0:
                        endPos = inputLine.find('|');
                        innerInput = inputLine.substr(0,endPos)
                        unitType = innerInput.erase(std::remove(innerInput.begin(), innerInput.end(), ' '), innerInput.end());
                        break;
                    case 1:
                        endPos = inputLine.find('|');
                        innerInput = inputLine.substr(0,endPos)
                        unitName = innerInput.erase(std::remove(innerInput.begin(), innerInput.end(), ' '), innerInput.end());
                        break;
                    case 2:
                        endPos = inputLine.find('\n');
                        innerInput = inputLine.substr(0,endPos)
                        workCapacityStr = innerInput.erase(std::remove(innerInput.begin(), innerInput.end(), ' '), innerInput.end());
                        break;
                }
                inputLine.erase(0,endPos+1);
            }
        }
    }
}






#endif
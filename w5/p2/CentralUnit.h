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
#include <string>
#include <iostream>
#include <iomanip>
#include <functional>

namespace sdds{

    #define MAX_JOBS 4                  // Max jobs that can be queued up in static m_jobs array

    template <typename T>
    class CentralUnit{
        std::string m_type{};           // Describes type of work central unit will coordinate
        T** m_items{nullptr};           // Dynamically allocated array of pointers to indivdual units of type T
        Job* m_jobs[MAX_JOBS]{};        // Statically allocated array of pointers to jobs that are queued up
        size_t m_size{};                // Number of units hosted by central unit (number in m_items array)
        size_t m_count{};               // Number of jobs queued up and waiting to be handled (number in m_jobs array)
    public:
        // Public data members
        std::ostream& log{std::cout};   // Stores reference to ostream object, used for logging information


        // Rule of 5, note that copy constructor will throw an exception, and copy assignment operator has been deleted to prevent copy operations
        CentralUnit(std::string type, std::string fileName);                           
        CentralUnit(const CentralUnit& src);            
        CentralUnit(CentralUnit&& src);
        CentralUnit& operator=(const CentralUnit& src) = delete; 
        CentralUnit& operator=(CentralUnit&& src);
        ~CentralUnit();

        // Modifiers
        CentralUnit& operator+=(const std::string jobTitle);    // Adds job to m_jobs queue, if space available
        CentralUnit& operator+=(T* unit);                       // Adds unit to m_items dynamic array
        void run();                                             // Runs cycle for each unit in m_items array
        void complete_job(CentralUnit& CU,T* unit);             // Called memory allocated for job once unit has completed the job

        // Queries
        bool has_jobs()const;                                   // TRUE if units in m_items have a job or if m_jobs has jobs queued up
        size_t get_available_units()const;                      // Returns number of units in m_items that do not have a job
        T* operator[](const std::string jobTitle)const;         // Searches through m_items array to see if there is a unit with the matching jobTitle, returns pointer to unit if found. Otherwise throws an error. 
        void display()const;                                    // Displays central unit's current state 

        /*
        ltrim(), rtrim(), and trim() work in conjunction to remove leading and trailing spaces from a string that has been passed to them. 
        If a string is passed to these functinos that only contains "spaces", an empty string will be returned.
        */
        std::string ltrim(const std::string &str){
            size_t start = str.find_first_not_of(" ");
            return (start == std::string::npos) ? "" : str.substr(start);
        }

        std::string rtrim(const std::string &str){
            size_t end = str.find_last_not_of(" ");
            return (end == std::string::npos) ? "" : str.substr(0,end + 1);
        }

        std::string trim(const std::string &str){
            return rtrim(ltrim(str));
        }

    };

    template<typename T>
    CentralUnit<T>::CentralUnit(std::string type, std::string fileName) : m_type{type} {
        std::string inputLine{};
        std::string innerInput{};
        std::string unitType;
        std::string unitName;
        std::string workCapacityStr;

        size_t endPos{};
        size_t count{0};
        size_t workCapacity{};

        // Open file based on passed fileName string. If open, count the number of lines (aka number of units)
        std::ifstream fs(fileName);
        if (!fs.is_open()){
            throw std::invalid_argument("File cannot be opened.");
        }
        
        do {
            std::getline(fs,inputLine);
            ++count;
        }while(fs);

        // Dynamically allocate m_items to be an array of T pointers to a size of count
        m_items = new T*[count];
        count = 0;

        // Clear error flags in file, and go back to beginning
        fs.clear();
        fs.seekg(std::ios::beg);

        /*
            The below code will go through each line of the file. For each line it will run 3 iterations to pull the unit type, unit name, and work capacity. If the work capacity is unable to convert from a string to an integer, it will be assigned a default value of "1".

            Then, a new T object in the m_items array will be dynamically allocated using a 4-arg constructor, that we assume has been defined for an object of type T. 

            We then pass call back functions in the form of a function pointer and a function object to the T object, which we assume to have members "on_complete" and "on_error".
        */

        while(getline(fs, inputLine)){
            for (int i = 0; i < 3; i++){
                switch(i){
                    case 0:
                        endPos = inputLine.find('|');
                        innerInput = inputLine.substr(0,endPos);
                        unitType = trim(innerInput);
                        break;
                    case 1:
                        endPos = inputLine.find('|');
                        innerInput = inputLine.substr(0,endPos);
                        unitName = trim(innerInput);
                        break;
                    case 2:
                        endPos = inputLine.find('\n');
                        innerInput = inputLine.substr(0,endPos);
                        workCapacityStr = trim(innerInput);
                        break;
                }
                inputLine.erase(0,endPos+1);
            }
            try{
                workCapacity = stoi(workCapacityStr);   
            } catch(...){
                workCapacity = 1;
            }
            m_items[m_size++] = new T(this, unitType, unitName, workCapacity);
            m_items[m_size-1]->on_complete(&CentralUnit<T>::complete_job);
            std::function<void(T*)> lambda = [this](T* unit){
                Job* temp = unit->free();
                log << "Failed to complete job " << temp->name() << std::endl;
                log << get_available_units() << " units available." << std::endl;
                delete temp;
            };
            m_items[m_size-1]->on_error(lambda);
        }
    }

    // Throwing exception when copy constructor called 
    template<typename T>
    CentralUnit<T>::CentralUnit(const CentralUnit& src){
        throw std::exception();
    }

    // Move constructor
    template<typename T>
    CentralUnit<T>::CentralUnit(CentralUnit<T>&& src){
        *this = std::move(src);
    }

    // Move assignment operator
    template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator=(CentralUnit<T>&& src){
        if (this != &src){
            for (size_t i = 0; i < m_size; i++){
                delete m_items[i];
            }
            delete [] m_items;
            m_items = src.m_items;
            m_type = src.m_type;
            m_jobs = src.m_jobs;
            m_size = src.m_size;
            m_count = src.m_count;
            src.m_items = nullptr;
            src.m_type = "";
            src.m_jobs = nullptr;
            src.m_size = 0;
            src.m_count = 0;
        }
        return *this;
    }

    // The CentralUnit destructor first goes through the m_items array, and deallocates each unit. Then the dynamic array itself is deallocated. 
    template<typename T>
    CentralUnit<T>::~CentralUnit(){
        for (size_t i = 0; i < m_size; i++){
            delete m_items[i];
        }
        delete [] m_items;
    }

    template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator+=(const std::string jobTitle){
        if (m_count == MAX_JOBS){
            throw std::string("Job Queue Full");
        }
        m_jobs[m_count++] = new Job(jobTitle);
        return *this;
    }

    /* 
    Below a new T unit is added to the dynamic array m_items.
    A temporary dynamic array of type T* must be first be created, by incrementing m_size by 1. 
    The contents of the old array are then copied into the new array. 
    The old dynamic array is then deallocated, and set to the value of the new one. 
    The last position in the array is then set to to the incoming Unit. 
    The subsequent call-back functions are then assigned to the incoming unit, as was done in the constructor
    */
    template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator+=(T* unit){
        T** m_newItems = new T*[m_size+1];
        for (size_t i = 0; i < m_size; i++){
            m_newItems[i] = m_items[i];
        }
        delete [] m_items;
        m_items = m_newItems;
        m_items[m_size] = unit;
        m_items[m_size]->on_complete(&CentralUnit<T>::complete_job);
        std::function<void(T*)> lambda = [this](T* unit){
            Job* temp = unit->free();
            log << "Failed to complete job " << temp->name() << std::endl;
            log << get_available_units() << " units available." << std::endl;
            delete temp;
        };
        m_items[m_size]->on_error(lambda);
        m_size++;
        return *this;
    }

    template<typename T>
    void CentralUnit<T>::run(){
        for (size_t i = 0; i < m_size; i++){
            if (m_items[i]->get_current_job() != nullptr) {
                (*m_items[i])();        // Functor notation, but can also use m_items[i]->run()
            }
            else {
                if (m_count > 0) {
                    *m_items[i] += m_jobs[--m_count];
                    (*m_items[i])();    // Functor notation, but can also use m_items[i]->run()
                }
            }
        } 
    }

    template<typename T>
    void CentralUnit<T>::complete_job(CentralUnit<T>& CU,T* unit){
        Job* temp = unit->free();
        size_t availUnits = CU.get_available_units();
        CU.log << "[COMPLETE] " << *temp << " using " << *unit << std::endl << availUnits << " units available." << std::endl;
        delete temp;
    }

    template<typename T>
    bool CentralUnit<T>::has_jobs()const{
        bool queueCheck = m_count > 0;
        bool unitCheck = false;
        for (size_t i = 0; i < m_size; i++){
            if (m_items[i]->get_current_job() != nullptr){
                unitCheck = true;
            }
        }
        return (queueCheck || unitCheck);
    }

    template<typename T>
    size_t CentralUnit<T>::get_available_units()const{
        size_t count{};
        for (size_t i = 0; i < m_size; i++){
            if (m_items[i]->get_current_job() == nullptr){
                count++;
            }
        }
        return count;
    }
    
    template<typename T>
    T* CentralUnit<T>::operator[](const std::string jobTitle)const{
        for (size_t i = 0; i < m_size; i++){
            if (m_items[i]->get_current_job() != nullptr){
                if (m_items[i]->get_current_job()->name() == jobTitle){
                    return m_items[i];
                }
            }
        }
        throw std::out_of_range("Job is not being handled by a unit.");
        return nullptr;
    }

    template<typename T>
    void CentralUnit<T>::display()const{
        log << "Central " << m_type << " Unit list" << std::endl;
        for (size_t i = 0; i < m_size; i++){
            log << "[";
            log.width(4);
            log.fill('0');
            log << i + 1 << "] ";
            std::cout << *m_items[i] << std::endl;
        }
    }
}

#endif
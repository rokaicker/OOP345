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

namespace sdds{
    template <typename T>
    class CentralUnit{
        std::string m_type{};           // Describes type of work central unit will coordinate
        T** m_items{nullptr};           // Dynamically allocated array of pointers to indivdual units of type T
        Job* m_jobs[4]{};               // Statically allocated array of pointers to jobs that are queued up
        size_t m_size{};                // Number of units hosted by central unit (number in m_items array)
        size_t m_count{};               // Number of jobs queued up and waiting to be handled (number in m_jobs array)
    public:
        std::ostream& log{std::cout};
        CentralUnit(std::string type, std::string fileName);                           //char* fileName);
        CentralUnit(const CentralUnit& src);            // Should throw exception - NO COPYING
        CentralUnit(CentralUnit&& src);
        //CentralUnit& operator=(const CentralUnit& src); // Should throw exception - NO COPYING
        CentralUnit& operator=(CentralUnit&& src);

        CentralUnit& operator+=(const std::string jobTitle);
        void run();
        bool has_jobs()const;
        size_t get_available_units()const;
    };

    template<typename T>
    CentralUnit<T>::CentralUnit(std::string type, std::string fileName) : m_type{type} {               //char* fileName) : m_type{type} {
        std::string inputLine;
        std::string innerInput;
        int endPos{};
        size_t firstPos{};
        size_t lastPos{};
        size_t count{0};
        std::string unitType;
        std::string unitName;
        std::string workCapacityStr;
        size_t workCapacity;

        
        std::ifstream fs(fileName);
        if (!fs.is_open()){
            throw std::invalid_argument("File cannot be opened.");
        }
        
        do {
            std::getline(fs,inputLine);
            ++count;
        }while(fs);

        m_items = new T*[count];
        count = 0;

        fs.clear();
        fs.seekg(std::ios::beg);

        while(getline(fs, inputLine)){
            for (int i = 0; i < 3; i++){
                switch(i){
                    
                    case 0:
                        endPos = inputLine.find('|');
                        innerInput = inputLine.substr(0,endPos);
                        /*unitType = innerInput.erase(std::remove(innerInput.begin(), innerInput.end(), ' '), innerInput.end());*/
                        firstPos = innerInput.find_first_not_of(" ");
                        innerInput.substr(firstPos);
                        lastPos = innerInput.find_last_not_of(" ");
                        innerInput.substr(0, lastPos+1);
                        break;
                    case 1:
                        endPos = inputLine.find('|');
                        innerInput = inputLine.substr(0,endPos);
                        /*unitName = innerInput.erase(std::remove(innerInput.begin(), innerInput.end(), ' '), innerInput.end());*/
                        firstPos = innerInput.find_first_not_of(" ");
                        innerInput.substr(firstPos);
                        lastPos = innerInput.find_last_not_of(" ");
                        innerInput.substr(0, lastPos+1);
                        break;
                    case 2:
                        endPos = inputLine.find('\n');
                        innerInput = inputLine.substr(0,endPos);
                        /*workCapacityStr = innerInput.erase(std::remove(innerInput.begin(), innerInput.end(), ' '), innerInput.end());*/
                        firstPos = innerInput.find_first_not_of(" ");
                        innerInput.substr(firstPos);
                        lastPos = innerInput.find_last_not_of(" ");
                        innerInput.substr(0, lastPos+1);
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
        }
    }

    // Throwing exception when copy constructor called 
    template<typename T>
    CentralUnit<T>::CentralUnit(const CentralUnit& src){
        throw std::exception();
    }

    // Throwing exception when copy assignment operator called 
    /*template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator=(const CentralUnit& src){
        throw std::exception();
    }*/

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


    template<typename T>
    CentralUnit<T>& CentralUnit<T>::operator+=(const std::string jobTitle){
        if (m_count == 4){
            throw std::string("Job Queue Full");
        }
        m_jobs[m_count++] = new Job(jobTitle);
        return *this;
    }

    template<typename T>
    void CentralUnit<T>::run(){
        for (size_t i = 0; i < m_size; i++){
            if (m_items[i]){
                if(m_items[i]->get_current_job()->is_active()){
                    m_items[i]->run();
                } else {
                    if (m_count > 0){
                        *m_items[i] += m_jobs[--m_count];
                        m_items[i]->run();
                    }
                }
            }
        } 
    }

    template<typename T>
    bool CentralUnit<T>::has_jobs()const{
        bool queueCheck = m_count > 0;
        bool unitCheck = false;
        for (size_t i = 0; i < m_size; i++){
            if (m_items[i]->get_current_job() != nullptr){
                unitCheck = true;
                break;
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
}

#endif
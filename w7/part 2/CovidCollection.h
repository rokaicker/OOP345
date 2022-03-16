/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: March 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

namespace sdds
{
    struct Covid
    {
        std::string m_country{};
        std::string m_city{};
        std::string m_variant{};
        int m_numCases{};
        int m_year{};
        int m_deaths{};
    };

    class CovidCollection
    {
        std::vector<Covid> m_covid{};
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

    public:
        CovidCollection(const std::string fileName);
        void display(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const Covid& theCovid);

        // Part 2 functions
        void sort(const std::string field);                                     // Sort based on field passed
        void cleanList();                                                       // Remove [None] from variant field
        bool inCollection(const std::string variant) const;                     // Return true if any city contains variant
        std::list<Covid> getListForCountry(const std::string country) const;    // Receive country name, return covid list of country
        std::list<Covid> getListForVariant(const std::string variant) const;    // Receive variant name, return covid list of variants
    };
    std::ostream& operator<<(std::ostream& os, const Covid& theCovid);
}


#endif
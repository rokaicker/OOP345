/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date: March 20, 2022
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "CovidCollection.h"

namespace sdds
{

    CovidCollection::CovidCollection(const std::string fileName)
    {
        std::ifstream fs(fileName);
        if(!fs.is_open())
        {
            throw std::string("Can't Open File" + fileName);
        }

        std::string inputLine{};
        std::string innerInput{};
        Covid temp;

        while(getline(fs,inputLine))
        {
            temp.m_country = trim(inputLine.substr(0,25));
            temp.m_city = trim(inputLine.substr(25,25));
            temp.m_variant = trim(inputLine.substr(50,25));
            temp.m_year = stoi(trim(inputLine.substr(75,5)));
            temp.m_numCases = stoi(trim(inputLine.substr(80,5)));
            temp.m_numDeaths = stoi(trim(inputLine.substr(85,5)));
            m_covid.push_back(temp);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Covid& theCovid)
    {
        os << "| " << std::left << std::setw(20) << theCovid.m_country;
        os << "  | " << std::left << std::setw(15) << theCovid.m_city;
        os << " | " << std::left << std::setw(20) << theCovid.m_variant;
        if (theCovid.m_year > 0)
        {
            os << " | " << std::right << std::setw(6) << theCovid.m_year;
        }
        else
        {
            os << " |       ";
        }
        os << " | " << std::right << std::setw(4) << theCovid.m_numCases;
        os << " | " << std::right << std::setw(3) << theCovid.m_numDeaths << " |";
        return os;
    }

    void CovidCollection::display(std::ostream& os) const
    {
        for_each(m_covid.begin(), m_covid.end(), [&os](Covid covid){os << covid << std::endl;});
    }

}
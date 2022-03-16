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
            temp.m_deaths = stoi(trim(inputLine.substr(85,5)));
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
        os << " | " << std::right << std::setw(3) << theCovid.m_deaths << " |";
        return os;
    }

    void CovidCollection::display(std::ostream& os) const
    {
        int totalCases{};
        int totalDeaths{};
        for_each(m_covid.begin(), m_covid.end(), [&os, &totalCases, &totalDeaths](Covid covid)
        {
            totalCases += covid.m_numCases;
            totalDeaths += covid.m_deaths;
            os << covid << std::endl;
        });

        os << "----------------------------------------------------------------------------------------" << std::endl;
        os << "|                                                 Total Cases Around the World:" << std::right << std::setw(7) << totalCases << " |" << std::endl;
        os << "|                                                Total Deaths Around the World:" << std::right << std::setw(7) << totalDeaths << " |" << std::endl;
    }

    void CovidCollection::sort(const std::string field)
    {
        if (field == "country")
        {
            std::sort(m_covid.begin(), m_covid.end(), [](const Covid& cov1, const Covid& cov2){return cov1.m_country < cov2.m_country;});
        }
        else if (field == "variant")
        {
            std::sort(m_covid.begin(), m_covid.end(), [](const Covid& cov1, const Covid& cov2){return cov1.m_variant < cov2.m_variant;});
        }
        else if (field == "cases")
        {
            std::sort(m_covid.begin(), m_covid.end(), [](const Covid& cov1, const Covid& cov2){return cov1.m_numCases < cov2.m_numCases;});
        }
        else if (field == "deaths")
        {
            std::sort(m_covid.begin(), m_covid.end(), [](const Covid& cov1, const Covid& cov2){return cov1.m_deaths < cov2.m_deaths;});
        }
    }

    void CovidCollection::cleanList()
    {
        std::transform(m_covid.begin(), m_covid.end(),m_covid.begin(), [](Covid& cov){ 
            if (cov.m_variant == "[None]")
            {
                cov.m_variant = "";
            }
            return cov;
        });
    }

    bool CovidCollection::inCollection(const std::string variant) const
    {
        return std::any_of(m_covid.begin(), m_covid.end(), [variant](const Covid& cov){return cov.m_variant == variant;});
    }

    std::list<Covid> CovidCollection::getListForCountry(const std::string country) const
    {
        std::list<Covid> covidList{};
        std::copy_if(m_covid.begin(), m_covid.end(), std::back_inserter(covidList),[country](const Covid& cov){return cov.m_country == country;});
        return covidList;
    }

    std::list<Covid> CovidCollection::getListForVariant(const std::string variant) const
    {
        std::list<Covid> covidList{};
        std::remove_copy_if(m_covid.begin(), m_covid.end(), std::back_inserter(covidList), [variant](const Covid& cov){return cov.m_variant != variant;});
        return covidList;
    }

}
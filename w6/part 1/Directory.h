/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date:
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include "Resource.h"

namespace sdds{
    class Directory : public Resource {
        std::vector<Resource*> m_contents{};

    public:
        // Custom Constructor
        Directory(std::string name){m_name = (name);};


        // Rule of 5 - deleted copy/ move operations
        Directory(const Directory& src) = delete;
        Directory(Directory&& src) = delete;
        Directory& operator=(const Directory& src) = delete;
        Directory& operator=(Directory&& src) = delete;
        ~Directory(){};

        // Modifier
        void update_parent_path(const std::string& path);

        // Queries
        NodeType type() const {return NodeType::DIR;};
        std::string path() const{return (m_parent_path + m_name);};
        std::string name() const{return m_name;};
        int count() const{return m_contents.size();};
        size_t size() const;

        Directory& operator+=(Resource* newRes);
        Resource* find(const std::string&, const std::vector<OpFlags>& = {});


    };
}

#endif
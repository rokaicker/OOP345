/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date:
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include "Resource.h"

namespace sdds{
    class File : public Resource {
        std::string m_contents{};
    public:

        // Custom Constructor
        File(std::string name, std::string contents = "") : m_contents(contents){m_name = name;};

        // Modifier
        void update_parent_path(const std::string& path){m_parent_path = path;};

        // Queries 
        NodeType type() const {return NodeType::FILE;};
        std::string path() const{return (m_parent_path + m_name);};
        std::string name() const{return m_name;};
        int count () const{return -1;};
        size_t size() const{return m_contents.length();};
    }; 
}

#endif
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
        File(std::string name, std::string contents = "");

        void update_parent_path(const std::string& path);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count () const;
        size_t size() const;

    }; 
}

#endif
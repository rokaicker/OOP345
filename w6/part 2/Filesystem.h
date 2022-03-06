/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date:
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include "Directory.h";
#include "File.h";

namespace sdds{
    class Filesystem {
        Directory* m_root{nullptr};
        Directory* m_current{nullptr};

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
        // Custom Constructor
        Filesystem(std::string fileName, std::string root = "");

        // Rule of 5 - deleted copy/ operations
        Filesystem(const Filesystem& src) = delete;
        Filesystem(Filesystem&& src);
        Filesystem& operator=(const Directory& src) = delete;
        Filesystem& operator=(Directory&& src);
        ~Filesystem();

        // Modifiers
        Filesystem& operator+=(Resource* newRsrc);
        Directory* change_directory(const std::string& dirName);


        // Queries
        Directory* get_current_directory() const{return m_current;};

    };
}

#endif
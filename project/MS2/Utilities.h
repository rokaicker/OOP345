// Name: Rohan Kaicker
// Seneca Student ID: 119070217
// Seneca email: rkaicker@myseneca.ca
// Date of completion: March , 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>


namespace sdds{
    class Utilities {
        size_t m_widthField = 1;    // Instance Variable - specifies length of token extracted, defaulted to "1"

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
        static char m_delimiter;    // Class Variable - separates token in given string based on delimiter character. All Utilities objects have same delimiter.

        // Member Functions
        void setFieldWidth(size_t newWidth) { m_widthField = newWidth; };
        size_t getFieldWidth() const { return m_widthField; };
        std::string extractToken(const std::string &str, size_t &next_pos, bool &more);

        // Class Functions
        static void setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; };
        static char getDelimiter() { return m_delimiter; }; 
    };
}


#endif
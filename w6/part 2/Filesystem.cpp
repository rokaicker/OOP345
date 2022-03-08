/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date:
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <algorithm>
#include "Filesystem.h"

namespace sdds{
    Filesystem::Filesystem(std::string fileName, std::string root){
        std::vector<sdds::OpFlags> oflags;
        oflags.push_back(sdds::OpFlags::RECURSIVE);

        m_root = new Directory(root);
        m_current = m_root;
        std::string inputLine{};
        std::string innerInput{};
        std::string prevDir{};
        std::ifstream fs(fileName);

        size_t endPos{};

        while(getline(fs,inputLine)){
            if (inputLine.find('|') == std::string::npos)
            { // if the character '|' is not found, the line is a directory
                inputLine = trim(inputLine);
                size_t dCount = std::count(inputLine.begin(), inputLine.end(), '/');
                for (size_t i = 0; i < dCount; i++){
                    endPos = inputLine.find('/');
                    innerInput = inputLine.substr(0,endPos);
                    inputLine.erase(0,endPos+1);
                    if (!m_root->find(prevDir, oflags)){
                        *m_root += new Directory(innerInput);
                        //prevDir = innerInput;
                    } else {
                        *dynamic_cast<Directory*>(m_root->find(prevDir, oflags)) += new Directory(innerInput);
                        //prevDir = innerInput;
                    }
                    if (i = dCount - 1){
                        prevDir = "";
                    } else {
                        prevDir = innerInput;
                    }
                }
            }
            else
            {   // Block Executed if line is a file path

            }
        }

    }
}
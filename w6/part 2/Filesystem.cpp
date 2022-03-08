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

    // 2-arg Constructor 
    Filesystem::Filesystem(std::string fileName, std::string root){
        std::vector<sdds::OpFlags> oflags;
        oflags.push_back(sdds::OpFlags::RECURSIVE);

        m_root = new Directory(root);
        m_current = m_root;
        std::string inputLine{};
        std::string innerInput{};
        std::string prevDir{};

        std::string filePath{};
        std::string fileContents{};
        
        std::ifstream fs(fileName);

        size_t dEndPos{};
        size_t fEndPos{};

        while(getline(fs,inputLine)){
            if (inputLine.find('|') == std::string::npos)
            { // if the character '|' is not found, the line is a directory
                inputLine = trim(inputLine);
                size_t dCount = std::count(inputLine.begin(), inputLine.end(), '/');
                for (size_t i = 0; i < dCount; i++){
                    dEndPos = inputLine.find('/');
                    innerInput = inputLine.substr(0,dEndPos + 1);
                    inputLine.erase(0,dEndPos+1);
                    if (!m_root->find(prevDir, oflags)){
                        *m_root += new Directory(innerInput);
                        //prevDir = innerInput;
                    } else {
                        *dynamic_cast<Directory*>(m_root->find(prevDir, oflags)) += new Directory(innerInput);
                        //prevDir = innerInput;
                    }
                    prevDir = innerInput;
                }
                prevDir = "";
            }
            else
            {   // Block Executed if line is a file path
                fEndPos = inputLine.find('|');
                filePath = inputLine.substr(0, fEndPos);
                filePath = trim(filePath);
                fileContents = inputLine.substr(fEndPos + 1);
                fileContents = trim(fileContents);

                // Checking/ Creating Directories
                size_t dCount = std::count(filePath.begin(), inputLine.end(), '/');
                for (size_t i = 0; i < dCount; i++){
                    dEndPos = filePath.find('/');
                    innerInput = filePath.substr(0,dEndPos + 1);
                    filePath.erase(0,dEndPos+1);
                    if (!m_root->find(prevDir, oflags)){
                        *m_root += new Directory(innerInput);
                        //prevDir = innerInput;
                    } else {
                        *dynamic_cast<Directory*>(m_root->find(prevDir, oflags)) += new Directory(innerInput);
                        //prevDir = innerInput;
                    }
                    prevDir = innerInput;
                }

                // Adding file contents
                *dynamic_cast<Directory*>(m_root->find(prevDir, oflags)) += new File (filePath, fileContents);
                prevDir = "";
            }
        }
    }

    // Destructor
    Filesystem::~Filesystem(){
        delete m_root;
    }

    // Move Constructor
    Filesystem::Filesystem(Filesystem&& src){
        *this = std::move(src);
    }

    // Move assignment operator
    Filesystem& Filesystem::operator=(Filesystem&& src){
        m_root = src.m_root;
        m_current = src.m_current;
        src.m_root = nullptr;
        src.m_current = nullptr;
        return *this;
    }

    Filesystem& Filesystem::operator+=(Resource* newRsrc){
        *m_current += newRsrc;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& dirName){
        if (dirName.empty()){
            m_current = m_root;
        } else {
            Resource* temp = m_current->find(dirName);
            if ( temp != nullptr && temp->type() == NodeType::DIR){
                m_current = dynamic_cast<Directory*>(temp);
            } else {
                throw std::invalid_argument("Cannot change directory! " + dirName + " not found!");
            }
        }
        return m_current;
    }

}
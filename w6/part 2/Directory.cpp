/*
* Name: Rohan Kaicker
* Seneca Email: rkaicker@myseneca.ca
* Seneca Student ID: 119070217
* Date:
*
* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "Directory.h"

namespace sdds{

    Directory::~Directory(){
        for (size_t i = 0; i < m_contents.size(); i++){
            delete m_contents[i];
        }
    }

    void Directory::update_parent_path(const std::string& path){
        m_parent_path = path;
        for (auto e :m_contents){
            e->update_parent_path(m_parent_path + m_name);
        }
    }

    size_t Directory::size() const {
        size_t totalSize = 0u;
        for (auto e : m_contents){
            totalSize += e->size();
        }
        return totalSize;
    }

    Directory& Directory::operator+=(Resource* newRes){
        for (auto e : m_contents){
            if(e->name() == newRes->name()){
                throw std::string("This resource already exists in the directory");
            }
        }
        m_contents.push_back(newRes);
        m_contents.back()->update_parent_path(path());
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag){
        Resource* rsrc{nullptr};
        bool recursionFlag = false;
        for (auto e : flag){
            if (e == OpFlags::RECURSIVE){
                recursionFlag = true;
                break;
            }
        }
        for (auto e : m_contents){
            if (e->name() == name){
                rsrc = e;
                break;
            }
            else if (e->type() == NodeType::DIR && recursionFlag){
                rsrc = dynamic_cast<Directory*>(e)->find(name, flag);
            }
        }
        return rsrc;
    }

    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flag){
        bool recursionFlag = false;
        for (auto e : flag){
            if (e == OpFlags::RECURSIVE){
                recursionFlag = true;
                break;
            }
        }

        // Checking if resource exists
        size_t index = -1;
        for (size_t i = 0; i < m_contents.size(); i++){
            if (m_contents[i]->name() == name){
                index = i;
                break;
            }
        }

        // Exception checking
        if ((int)index == -1){
            throw std::string(name + " does not exist in " + m_name);
        }

        if ((m_contents[index]->type() == NodeType::DIR) && (recursionFlag == false)){
            throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
        }
        
        // Deleting element
        Resource* temp = m_contents[index];
        m_contents.erase(m_contents.begin() + index);
        delete temp;
    }

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flag)const{
        char type{};
        bool longFlag = false;
        for (auto e : flag){
            if (e == FormatFlags::LONG){
                longFlag = true;
                break;
            }
        }

        os << "Total size: " << size() << " bytes" << std::endl;
        for (size_t i = 0; i < m_contents.size(); i++){
            Resource* temp = m_contents[i];
            if (temp->type() == NodeType::DIR){
                type = 'D';
            } else {
                type = 'F';
            }
            os << type << " | ";
            os.setf(std::ios::left);
            os.width(15);
            os << temp->name() << " |";
            os.unsetf(std::ios::left);
            if (longFlag){
                if(temp->type() == NodeType::DIR){
                    os << " ";
                    os.width(2);
                    os << temp->count() << " | ";
                } else {
                    os << "    | ";
                }
                os.width(4);
                os << temp->size() << " bytes |";
            }
            os << std::endl;
        }

    }

}

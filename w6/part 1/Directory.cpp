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
}

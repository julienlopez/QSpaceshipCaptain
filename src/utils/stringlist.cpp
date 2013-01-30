#include "stringlist.hpp"

StringList::StringList()
{}
StringList::StringList(const std::string& str)
{
    m_list.push_back(str);
}
StringList::StringList(const type_list& lst): m_list(lst)
{}

StringList::const_iterator StringList::begin() const
{
    return m_list.begin();
}
StringList::const_iterator StringList::end() const
{
    return m_list.end();
}
StringList::const_reverse_iterator StringList::rbegin() const
{
    return m_list.rbegin();
}
StringList::const_reverse_iterator StringList::rend() const
{
    return m_list.rend();
}
StringList::iterator StringList::begin()
{
    return m_list.begin();
}
StringList::iterator StringList::end()
{
    return m_list.end();
}
StringList::reverse_iterator StringList::rbegin()
{
    return m_list.rbegin();
}
StringList::reverse_iterator StringList::rend()
{
    return m_list.rend();
}

void StringList::push_back(const std::string& str)
{
    m_list.push_back(str);
}

void StringList::push_front(const std::string& str)
{
    m_list.push_front(str);
}

bool StringList::empty() const
{
    return m_list.empty();
}

StringList::type_list::size_type StringList::size() const
{
    return m_list.size();
}

std::string& StringList::front()
{
    return m_list.front();
}

const std::string& StringList::front() const
{
    return m_list.front();
}

std::string& StringList::back()
{
    return m_list.back();
}

const std::string& StringList::back() const
{
    return m_list.back();
}

std::string StringList::join(const std::string& separator) const
{
    std::string res;
    if(m_list.empty()) return res;
    type_list::const_iterator i = m_list.begin();
    type_list::const_iterator i_end = m_list.end();
    --i_end;
    for(; i != i_end; ++i)
    {
        res += *i + separator;
    }
    if(i != m_list.end()) res += *i;
    return res;
}

StringList StringList::split(std::string str, const std::string& separator)
{
    StringList res;
    while(!str.empty())
    {
        size_t i = str.find(separator);
        if(i == std::string::npos)
        {
            res << str;
            break;
        }
        res << str.substr(0, i);
        str.erase(0, i + separator.length() );
    }
    return res;
}

StringList& StringList::operator << (const std::string& str)
{
    m_list.push_back(str);
    return *this;
}

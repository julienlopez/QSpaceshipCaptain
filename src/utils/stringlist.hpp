#ifndef STRINGLIST_HPP
#define STRINGLIST_HPP

#include <list>
#include <string>

class StringList
{
public:
    typedef std::list<std::string> type_list;
    typedef type_list::iterator iterator;
    typedef type_list::const_iterator const_iterator;
    typedef type_list::reverse_iterator reverse_iterator;
    typedef type_list::const_reverse_iterator const_reverse_iterator;

    StringList();
    StringList(const std::string& str);
    StringList(const type_list& lst);

    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();

    void push_back(const std::string& str);
    void push_front(const std::string &str);

    bool empty() const;
    type_list::size_type size() const;

    std::string& front();
    const std::string& front() const;
    std::string& back();
    const std::string& back() const;

    std::string join(const std::string& separator) const;

    static StringList split(std::string str, const std::string& separator);
    static StringList split(std::string str, const std::string& separator, const std::string& evade);

    StringList& operator << (const std::string& str);

private:
    type_list m_list;
};

#endif // STRINGLIST_HPP

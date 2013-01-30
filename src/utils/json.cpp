#include "json.hpp"
#include "stringlist.hpp"

#include <sstream>
#include <stack>
#include <boost/lexical_cast.hpp>

std::string JSon::toJson(const Any& any)
{
    if(any.isString()) return toJson(any.toString());
    if(any.isLong()) return toJson(any.toLong());
    if(any.isMap()) return toJson(any.toMap());
    if(any.isList()) return toJson(any.toList());
    if(any.isInt()) return toJson(any.toInt());
    return "format non pris en compte: " + std::string(any.typeString());
}

std::string JSon::toJson(const AnyMap& map)
{
    std::string res = "{\n";
    for(AnyMap::const_iterator i = map.begin(); i != map.end(); ++i)
        res += '\t' + i->first + ": " + toJson(i->second) + " , \n";
    if(res.size() > 3) res.erase(res.length()-3, 3); //removing three last characters
    return res + "\n}\n";
}

std::string JSon::toJson(const AnyList& list)
{
    std::string res = "[\n";
    for(AnyList::const_iterator i = list.begin(); i != list.end(); ++i)
        res += '\t' + toJson(*i) + " , ";
    if(res.size() > 3) res.erase(res.length()-3, 3); //removing three last characters
    return res + "\n]\n";
}

std::string JSon::toJson(int64_t l)
{
    std::ostringstream oss;
    oss << l;
    return oss.str();
}

std::string JSon::toJson(const std::string& str)
{
    return '"'+str+'"';
}

std::string JSon::toJson(int i)
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

Any JSon::fromJson(std::string json) throw(std::invalid_argument)
{
    clearBothEnds(json);
    if(json.empty()) return Any();
    if(*json.begin() == '{')
        return parseToMap(json);

    if(*json.begin() == '[')
        return parseToList(json);

    return parseValue(json);
}

AnyMap JSon::parseToMap(std::string json) throw(std::invalid_argument)
{
    if(json.size() < 2 || *json.begin() != '{' || json[json.length()-1] != '}')
    {
        throw std::invalid_argument("invalid string to parse to a map:\n" + json);
    }

    eraseFirst(json);
    eraseLast(json);
    clearBothEnds(json);

    AnyMap res;
    StringList lst = split(json, ',');
    for(StringList::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
        StringList l = split(*i, ':');
        if(l.size() != 2)
        {
            throw std::invalid_argument("invalid string to parse to a pair name/value:\n" + *i);
        }
        std::string name = l.front();
        clearBothEnds(name);
        if(name.length() < 2 ||*name.begin() != '"' || *(--name.end()) != '"')
        {
            throw std::invalid_argument("invalid name for a pair: " + name);
        }
        eraseFirst(name);
        eraseLast(name);
        std::string value = l.back();
        clearBothEnds(value);
        res[name] = fromJson(value);
    }
    return res;
}

AnyList JSon::parseToList(std::string json) throw(std::invalid_argument)
{
    if(json.size() < 2 || *json.begin() != '[' || json[json.length()-1] != ']')
    {
        throw std::invalid_argument("invalid string to parse to a list:\n" + json);
    }
    eraseFirst(json);
    eraseLast(json);
    clearBothEnds(json);

    AnyList res;
    StringList lst = split(json, ',');
    for(StringList::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
        res.push_back(fromJson(*i));
    }
    return res;
}

Any JSon::parseValue(std::string json) throw(std::invalid_argument)
{
    if(json == "false") return false;
    if(json == "true") return true;
    if(json == "null") return Any();

    if(json.size() >= 2 && *json.begin() == '"' && json[json.length()-1] == '"')
    {
        eraseFirst(json);
        eraseLast(json);
        return json;
    }

    if(json.find('.') == std::string::npos) {
        try
        {
            int i = boost::lexical_cast<int>(json);
            if(i < 255) return (uint8_t)i;
            return i;
        }
        catch(...) {}
    } else {
        try
        {
            double x = boost::lexical_cast<double>(json);
            return x;
        }
        catch(...) {}
    }

    throw std::invalid_argument("invalid string to parse to a basic value:\n" + json);
    return Any();
}

void JSon::clearBothEnds(std::string& str)
{
    while(!str.empty() && isspace(*str.begin())) eraseFirst(str);
    while(!str.empty() && isspace(str[str.length()-1])) eraseLast(str);
}

void JSon::eraseFirst(std::string& str)
{
    str.erase(0, 1);
}

void JSon::eraseLast(std::string& str)
{
    str.erase(str.length()-1, 1);
}

StringList JSon::split(std::string string, char separator)
{
    static std::string caractereEvitementDebut = "\"{[";
    static std::string caractereEvitementFin = "\"}]";

    StringList resultat;
    while(true)
    {
        size_t pos = string.find(separator);
        if(pos == std::string::npos) break;
        std::stack<unsigned int> stack;
        for(size_t i = 0; true; i++)
        {
            if(i == string.size()-1)
            {
                pos = -1;
                break;
            }
            if(string.at( i ) == separator && stack.empty())
            {
                if ( i > pos ) pos = i;
                break;
            }
            if(caractereEvitementDebut.find(string.at(i)) != std::string::npos && ( i == 0 || string.at( i - 1 ) != '\\' ))
            {
                stack.push(caractereEvitementDebut.find(string.at(i)));

            }
            if(!stack.empty() && string.at(i) == caractereEvitementFin.at( stack.top()))
            {
                stack.pop();

            }
        }
        if(pos == std::string::npos) break;
        resultat << string.substr(0, pos);
        string.erase(0,pos+1);
    }
    if(!string.empty()) resultat << string;
    return resultat;
}

#ifndef JSON_H
#define JSON_H

#include <utils/any/any.hpp>

#include <stdexcept>

class StringList;

class JSon
{
public:
    static std::string toJson(const Any& any);
    static std::string toJson(const AnyMap& map);
    static std::string toJson(const AnyList& list);
    static std::string toJson(int64_t l);
    static std::string toJson(const std::string& str);
    static std::string toJson(int i);

    /**
    * \throws std::invalid_argument if the string is not a valid.
    */
    static Any fromJson(std::string json);

private:
    /**
    * \brief parse a json string to a AnyMap
    * The string must start with { and the end with }
    * \throws std::invalid_argument if the string is not a valid.
    */
    static AnyMap parseToMap(std::string json);

    /**
    * \brief parse a json string to a AnyList
    * The string must start with [ and the end with ]
    * \throws std::invalid_argument if the string is not a valid.
    */
    static AnyList parseToList(std::string json);

    /**
    * \brief parse a json string to a Any
    * The string must be a basic json value: a string, a number, true, false or null
    * \throws std::invalid_argument if the string is not a valid.
    */
    static Any parseValue(std::string json);

    static void clearBothEnds(std::string& str);
    static void eraseFirst(std::string& str);
    static void eraseLast(std::string& str);
    static bool isNumber(const std::string& str);

public:
    static StringList split(std::string string, char separator);
};

#endif // JSON_H

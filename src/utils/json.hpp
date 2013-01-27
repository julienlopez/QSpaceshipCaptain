#ifndef JSON_H
#define JSON_H

#include <utils/any/any.hpp>

#include <stdexcept>

class JSon
{
public:
    static std::string toJson(const Any& any);
    static std::string toJson(const AnyMap& map);
    static std::string toJson(const AnyList& list);
    static std::string toJson(int64_t l);
    static std::string toJson(const std::string& str);
    static std::string toJson(int i);

    static Any fromJson(std::string json) throw(std::invalid_argument);

private:
    /**
      * \brief parse a json string to a AnyMap
      * The string must start with { and the end with }
    */
    static AnyMap parseToMap(std::string json) throw(std::invalid_argument);

    /**
      * \brief parse a json string to a AnyList
      * The string must start with [ and the end with ]
    */
    static AnyList parseToList(std::string json) throw(std::invalid_argument);

    /**
      * \brief parse a json string to a Any
      * The string must be a basic json value: a string, a number, true, false or null
    */
    static Any parseValue(std::string json) throw(std::invalid_argument);

    static void clearBothEnds(std::string& str);
    static void eraseFirst(std::string& str);
    static void eraseLast(std::string& str);
    static bool isNumber(const std::string& str);
};

#endif // JSON_H

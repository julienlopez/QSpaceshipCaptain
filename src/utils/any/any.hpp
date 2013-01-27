#ifndef ANY_HPP
#define ANY_HPP

#include <utils/types.hpp>

#include <boost/any.hpp>

#include <map>
#include <list>
#include <string>

class Any
{
public:
    Any();
    Any(int8_t i);
    Any(uint8_t i);
    Any(int16_t i);
    Any(uint16_t i);
    Any(int32_t i);
    Any(uint32_t i);
    Any(int64_t i);
    Any(uint64_t i);
    Any(double d);
    Any(const std::string& str);
    Any(const std::map<std::string, Any>& map);
    Any(const std::list<Any>& list);

    std::map<std::string, Any> toMap() const;
    std::list<Any> toList() const;
    int64_t toLong() const;
    uint64_t toULong() const;
    std::string toString() const;
    int toInt() const;
    uint32_t toUInt() const;
    int16_t toInt16() const;
    uint16_t toUInt16() const;
    int8_t toInt8() const;
    uint8_t toUInt8() const;

    bool isString() const;
    bool isLong() const;
    bool isMap() const;
    bool isList() const;
    bool isInt() const;

    std::string typeString() const;

private:
    boost::any m_data;
};

typedef std::map<std::string, Any> AnyMap;
typedef std::list<Any> AnyList;

#endif // ANY_HPP

#include "any.hpp"

#include <utils/point.hpp>

Any::Any()
{}
Any::Any(int8_t i): m_data(i)
{}
Any::Any(uint8_t i): m_data(i)
{}
Any::Any(int16_t i): m_data(i)
{}
Any::Any(uint16_t i): m_data(i)
{}
Any::Any(int32_t i): m_data(i)
{}
Any::Any(uint32_t i): m_data(i)
{}
Any::Any(int64_t i): m_data(i)
{}
Any::Any(uint64_t i): m_data(i)
{}
Any::Any(double d): m_data(d)
{}
Any::Any(const std::string& str): m_data(str)
{}
Any::Any(const std::map<std::string, Any>& map): m_data(map)
{}
Any::Any(const std::list<Any>& list): m_data(list)
{}
Any::Any(const Point& point): m_data(point)
{}

std::map<std::string, Any> Any::toMap() const
{
    return boost::any_cast<std::map<std::string, Any> >(m_data);
}

std::list<Any> Any::toList() const
{
    return boost::any_cast<std::list<Any> >(m_data);
}

int64_t Any::toLong() const
{
    return boost::any_cast<int64_t>(m_data);
}

uint64_t Any::toULong() const
{
    return boost::any_cast<uint64_t>(m_data);
}

std::string Any::toString() const
{
    return boost::any_cast<std::string>(m_data);
}

int Any::toInt() const
{
    return boost::any_cast<int>(m_data);
}

uint32_t Any::toUInt() const
{
    return boost::any_cast<uint32_t>(m_data);
}

int16_t Any::toInt16() const
{
    return boost::any_cast<int16_t>(m_data);
}

uint16_t Any::toUInt16() const
{
    return boost::any_cast<uint16_t>(m_data);
}

int8_t Any::toInt8() const
{
    return boost::any_cast<int8_t>(m_data);
}

uint8_t Any::toUInt8() const
{
    return boost::any_cast<uint8_t>(m_data);
}

double Any::toDouble() const
{
    return boost::any_cast<double>(m_data);
}

bool Any::isString() const
{
    return m_data.type() == typeid(std::string);
}

bool Any::isLong() const
{
    return m_data.type() == typeid(int64_t);
}

bool Any::isMap() const
{
    return m_data.type() == typeid(AnyMap);
}

bool Any::isList() const
{
    return m_data.type() == typeid(AnyList);
}

bool Any::isInt() const
{
    return m_data.type() == typeid(int);
}

std::string Any::typeString() const
{
    return m_data.type().name();
}

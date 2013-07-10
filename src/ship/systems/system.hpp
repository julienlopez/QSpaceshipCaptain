#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <utils/json.hpp>
#include <utils/factory.hpp>
#include <utils/point.hpp>

class System
{
public:
    typedef uint8_t type_id;

    virtual ~System() = default;

    virtual type_id type() const =0;

    virtual std::string toJson() const =0;

    static System* fromJson(const std::string& json);

    static System* fromJson(const AnyMap& map);

    uint8_t level() const;
    uint8_t levelMax() const;
    const std::string& icon() const;
    const Point& console() const;

    virtual bool isPowerGenerator() const;

protected:
    typedef Factory<System, type_id, System*(*)(const AnyMap&)> type_factory;

    System(type_id level, type_id levelMax, const std::string& icon, const Point& console);

//    void setLevel(uint8_t i);
//    void setLevelMax(uint8_t i);

private:
    uint8_t m_level;
    uint8_t m_levelMax;
    std::string m_icon;
    Point m_console;
};

#endif // SYSTEM_HPP

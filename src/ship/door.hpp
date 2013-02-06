#ifndef DOOR_HPP
#define DOOR_HPP

#include <utils/any/any.hpp>
#include <utils/point.hpp>

#include <stdexcept>

class Door
{
public:
    Door(const Point& from = Point(), const Point& to = Point());
    Door(const Door& door);

    const Point& from() const;
    const Point& to() const;

    bool isVertical() const;
    bool isHorizontal() const;
    bool isOpen() const;
    void setOpen(bool b);
    void open();
    void close();

    //Json methods
    std::string toJson() const;
    static Door fromJson(const std::string& json) throw(std::invalid_argument);
    static Door fromJson(const AnyMap& map) throw(std::invalid_argument);

private:
    bool m_isOpen;
    Point m_from;
    Point m_to;
};

#endif // DOOR_HPP

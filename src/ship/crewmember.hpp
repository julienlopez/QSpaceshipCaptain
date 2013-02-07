#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <utils/point.hpp>
#include <utils/any/any.hpp>

#include <string>
#include <stdexcept>

class CrewMember
{
public:
    CrewMember(const std::string& name);

    const std::string& name() const;
    const PointF& position() const;

    void setName(const std::string& name);
    void setPosition(const PointF& pos);

    std::string toJson() const;

    static CrewMember fromJson(const std::string& json) throw(std::invalid_argument);
    static CrewMember fromJson(const AnyMap& map) throw(std::invalid_argument);

private:
    std::string m_name;
    PointF m_position;
};

#endif // CREWMEMBER_HPP

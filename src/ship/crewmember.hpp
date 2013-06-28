#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <utils/typedefs.hpp>
#include <utils/any/any.hpp>
#include <utils/iupdateable.hpp>

#include <string>
#include <stdexcept>

class CrewMember : public iUpdateable
{
public:
    CrewMember(const std::string& name);

    const std::string& name() const noexcept;
    const PointF& position() const noexcept;

    void setName(const std::string& name);
    void setPosition(const PointF& pos) noexcept;

    /**
    * \brief returns a json string describing the crew member.
    */
    std::string toJson() const;

    /**
    * \brief Parse a crew member from a json string.
    * \throws std::invalid_argument if the string's format is invalid.
    */
    static CrewMember fromJson(const std::string& json);

    /**
    * \brief Parse a crew member from a variant map.
    * \throws std::invalid_argument if the map's content is invalid.
    */
    static CrewMember fromJson(const AnyMap& map);

    void followPath(const utils::type_list_points& points);

    virtual void update(double dt) override;

private:
    std::string m_name;
    PointF m_position;
    double m_speed;

    /**
    * path the crew member has to follow to get to where he's going.
    */
    utils::type_list_points m_path;
};

#endif // CREWMEMBER_HPP

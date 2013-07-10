#ifndef SHIP_HPP
#define SHIP_HPP

#include "room.hpp"
#include "door.hpp"
#include "crewmember.hpp"

#include <functional>

class Ship : public Size<uint8_t>, public iUpdateable
{
public:
    typedef Size<uint8_t> Size8;
    typedef std::list<Room> type_list_rooms;
    typedef std::list<Door> type_list_doors;
    typedef std::list<CrewMember> type_list_crew;

    Ship(const std::string& name = std::string(), const Size8& size = Size8(10, 10));

    const std::string& name() const;

    type_list_rooms::const_iterator roomsBegin() const;
    type_list_rooms::const_iterator roomsEnd() const;

//    type_list_doors::const_iterator doorsBegin() const;
//    type_list_doors::const_iterator doorsEnd() const;
    void foreachDoor(std::function<void (const Door&)>& functor) const;

    type_list_crew::const_iterator crewBegin() const;
    type_list_crew::const_iterator crewEnd() const;
    void foreachCrew(std::function<void (const CrewMember&)>& functor) const;

    //Json methods
    /**
    * \brief returns a json string describing the ship.
    */
    std::string toJson() const;

    /**
    * \brief Parse a ship from a json string.
    * \throws std::invalid_argument if the string's format is invalid.
    */
    static Ship fromJson(const std::string& json);

    /**
    * \brief Parse a ship from a variant map.
    * \throws std::invalid_argument if the map's content is invalid.
    */
    static Ship fromJson(const AnyMap& map);

    /**
    * \brief search the room at the given coordinates.
    * \arg \c point coordinates of the room.
    * \returns the room if found.
    * \throws std::invalid_argument exception thrown if no room exists at the given coordinates.
    */
    const Room& getRoomByCoord(const PointF& point) const;

    void add(CrewMember crewMember);
    CrewMember& memberByName(const std::string& name);

    bool isThereCrewAtPosition(const PointF& position) const;

    virtual void update(double dt) override;

    Room::cwp_system powerGenerator() const;

    uint8_t energyProduced() const;

private:
    std::string m_name;
    type_list_rooms m_rooms;
    type_list_doors m_doors;
    type_list_crew m_crew;
    PointF m_startingSpot;
};

#endif // SHIP_HPP

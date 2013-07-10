#include "powergenerator.hpp"

#include <cassert>
#include <sstream>

PowerGenerator::PowerGenerator(type_id level, type_id levelMax, const std::string& icon, const Point& console): System(level, levelMax, icon, console)
{}

PowerGenerator::type_id PowerGenerator::type() const
{
    return s_id();
}

bool PowerGenerator::isPowerGenerator() const
{
    return true;
}

std::string PowerGenerator::toJson() const
{
    std::ostringstream oss;
    oss << "{ \"type\" : " << s_id() << ", \"level\" : " << level() << ", \"level_max\" : "
        << levelMax() << ", \"icon\" : " << icon() << ", \"console\" : { \"x\" : " << console().x()
        << ", \"y\" : " << console().y() << " } }";
    return oss.str();
}

namespace {
    System* f(const AnyMap& map)
    {
        AnyMap::const_iterator i = map.find("type");
        assert(i != map.end());
        assert(i->second.toUInt8() == PowerGenerator::s_id());

        i = map.find("level");
        assert(i != map.end());
        System::type_id level = i->second.toUInt8();

        i = map.find("level_max");
        assert(i != map.end());
        System::type_id levelMax = i->second.toUInt8();

        i = map.find("icon");
        assert(i != map.end());
        std::string icon = i->second.toString();

        i = map.find("console");
        assert(i != map.end());
        AnyMap m = i->second.toMap();
        Point console(m["x"].toUInt8(), m["y"].toUInt8());

        return new PowerGenerator(level, levelMax, icon, console);
    }
}

const bool PowerGenerator::s_registered = PowerGenerator::type_factory::instance().registerProduct(PowerGenerator::s_id(), &f);

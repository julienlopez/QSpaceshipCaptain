#ifndef POWERGENERATOR_HPP
#define POWERGENERATOR_HPP

#include "system.hpp"

class PowerGenerator : public System
{
public:
    PowerGenerator(type_id level, type_id levelMax, const std::string& icon, const Point& console);

    virtual type_id type() const override;

    virtual bool isPowerGenerator() const override;

    virtual std::string toJson() const override;

    static constexpr type_id s_id()
    {
        return 1;
    }

    static const bool s_registered;

};

#endif // POWERGENERATOR_HPP

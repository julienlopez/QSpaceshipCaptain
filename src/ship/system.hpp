#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>

class System
{
public:
    System();

    std::string toJson() const;

    static System fromJson(const std::string& json);
};

#endif // SYSTEM_HPP

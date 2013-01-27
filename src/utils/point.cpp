#include "point.hpp"

#include <cmath>

Point::Point(double x, double y): m_x(x), m_y(y)
{}

double Point::x() const
{
    return m_x;
}

double Point::y() const
{
    return m_y;
}

Point Point::operator+(const Point& p) const
{
    return Point(m_x + p.m_x, m_y + p.m_y);
}

Point Point::operator-() const
{
    return Point(-m_x, -m_y);
}

Point Point::operator-(const Point& p) const
{
    return Point(m_x - p.m_x, m_y - p.m_y);
}

Point Point::operator*(double d) const
{
    return Point(d*m_x, d*m_y);
}

Point operator*(double d, const Point& p)
{
    return p*d;
}

Point Point::operator/(double d) const
{
    return Point(m_x/d, m_y/d);
}

double Point::dot(const Point& p) const
{
    return m_x * p.m_x + m_y * p.m_y;
}

double Point::length() const
{
    return sqrt(dot(*this));
}
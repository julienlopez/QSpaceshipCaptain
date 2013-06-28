#include "point.hpp"

Point::Point(int x, int y) noexcept: Point2D<int>(x, y)
{}

Point::Point(const Point2D<int>& point) noexcept: Point2D<int>(point.x(), point.y())
{}

Point::Point(const PointF& p) noexcept: Point2D<int>(p.x(), p.y())
{}

bool Point::operator==(const Point& p) const noexcept
{
    return BASE::operator ==(p);
}

bool Point::operator==(const PointF& p) const noexcept
{
    return PointF(*this) == p;
}

bool Point::operator< (const Point& p) const
{
    if(p.x() == x()) return p.y() < y();
    return p.x() < x();
}

PointF::PointF(double x, double y) noexcept: BASE(x, y)
{}

PointF::PointF(const Point2D<double>& point) noexcept: BASE(point.x(), point.y())
{}

PointF::PointF(const Point& p) noexcept: Point2D<double>(p.x(), p.y())
{}

PointF PointF::operator+(const PointF& p) const noexcept
{
    return BASE::operator +(p);
}

PointF operator+(const Point& p1, const PointF& p2) noexcept
{
    return PointF(p1) + p2;
}

PointF PointF::operator-(const PointF& p) const noexcept
{
    return BASE::operator -(p);
}

PointF& PointF::operator += (const PointF& p) noexcept
{
    Point2D<double>::operator +=(p);
    return *this;
}

bool PointF::operator==(const Point& p) const noexcept
{
    return BASE::operator ==(PointF(p));
}

bool PointF::operator==(const PointF& p) const noexcept
{
    return BASE::operator ==(p);
}

Vector::Vector(double x, double y) noexcept: Point2D<double>(x, y)
{}

Vector::Vector(const PointF& to, const PointF& from) noexcept: Point2D<double>(to.x() - from.x(), to.y() - from.y())
{}

void Vector::normalize()
{
    operator /=(length());
}

Vector::operator PointF() const noexcept
{
    return PointF(x(), y());
}

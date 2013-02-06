#include "point.hpp"

Point::Point(int x, int y): Point2D<int>(x, y)
{}

Point::Point(const Point2D<int>& point): Point2D<int>(point.x(), point.y())
{}

PointF::PointF(double x, double y): BASE(x, y)
{}

PointF::PointF(const Point2D<double>& point): BASE(point.x(), point.y())
{}

PointF::PointF(const Point& p): Point2D<double>(p.x(), p.y())
{}

PointF PointF::operator+(const PointF& p) const
{
    return BASE::operator +(p);
}

PointF operator+(const Point& p1, const PointF& p2)
{
    return PointF(p1) + p2;
}

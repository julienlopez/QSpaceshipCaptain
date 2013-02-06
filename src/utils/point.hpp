#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

template<typename T> class Point2D
{
public:

    static const double PI = 3.14159265;

    Point2D(T x = 0, T y = 0): m_x(x), m_y(y)
    {}

    T x() const
    {
        return m_x;
    }
    T y() const
    {
        return m_y;
    }

    Point2D operator+(const Point2D& p) const
    {
        return Point2D(m_x + p.m_x, m_y + p.m_y);
    }
    Point2D operator-() const
    {
        return Point2D(-m_x, -m_y);
    }
    Point2D operator-(const Point2D& p) const
    {
        return Point2D(m_x - p.m_x, m_y - p.m_y);
    }
    Point2D operator*(T d) const
    {
        return Point2D(d*m_x, d*m_y);
    }
    friend Point2D operator*(T d, const Point2D& p)
    {
        return p*d;
    }
    Point2D operator/(T d) const
    {
        return Point2D(m_x/d, m_y/d);
    }

    T dot(const Point2D& p) const
    {
        return m_x * p.m_x + m_y * p.m_y;
    }
    double length() const
    {
        return sqrt(dot(*this));
    }

    bool operator==(const Point2D& p) const
    {
        return m_x == p.m_x && m_y == p.m_y;
    }

    double angle() const
    {
        double a = atan2(y(),x());
        if (a<0) a = 2*PI+a;
        return a;
    }
    void rotate(double a)
    {
        double d = length();
        double p = a + angle();
        m_x = d*cos(p);
        m_y = d*sin(p);
    }
    void rotate(const Point2D &centre, double angle)
    {
        Point2D v = (*this)-centre;
        v.rotate(angle);
        *this = centre + v;
    }

private:
    T m_x;
    T m_y;
};

class Point : public Point2D<int>
{
public:
    Point(int x = 0, int y = 0);
    Point(const Point2D<int>& point);
};

class PointF : public Point2D<double>
{
    typedef Point2D<double> BASE;
public:
    PointF(double x = 0, double y = 0);
    PointF(const Point2D<double>& point);
    PointF(const Point& p);

    PointF operator+(const PointF& p) const;
    friend PointF operator+(const Point& p1, const PointF& p2);
};

#endif // POINT_HPP

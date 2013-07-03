#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>

template<typename T> class Point2D
{
public:

    static constexpr double PI = 3.14159265;

    Point2D(T x = 0, T y = 0) noexcept: m_x(x), m_y(y)
    {}

    T x() const noexcept
    {
        return m_x;
    }
    T y() const noexcept
    {
        return m_y;
    }
    void setX(T x) noexcept
    {
        m_x = x;
    }
    void setY(T y) noexcept
    {
        m_y = y;
    }

    Point2D operator+(const Point2D& p) const noexcept
    {
        return Point2D(m_x + p.m_x, m_y + p.m_y);
    }
    Point2D operator-() const noexcept
    {
        return Point2D(-m_x, -m_y);
    }
    Point2D operator-(const Point2D& p) const noexcept
    {
        return Point2D(m_x - p.m_x, m_y - p.m_y);
    }
    Point2D operator*(T d) const noexcept
    {
        return Point2D(d*m_x, d*m_y);
    }
    friend Point2D operator*(T d, const Point2D& p) noexcept
    {
        return p*d;
    }
    Point2D operator/(T d) const
    {
        return Point2D(m_x/d, m_y/d);
    }

    Point2D& operator +=(const Point2D& p)
    {
        m_x += p.m_x;
        m_y += p.m_y;
        return *this;
    }

    Point2D& operator *=(T d)
    {
        m_x *= d;
        m_y *= d;
        return *this;
    }

    Point2D& operator /=(T d)
    {
        m_x /= d;
        m_y /= d;
        return *this;
    }

    T dot(const Point2D& p) const noexcept
    {
        return m_x * p.m_x + m_y * p.m_y;
    }
    T dot() const noexcept
    {
        return dot(*this);
    }
    double length() const
    {
        return sqrt(dot());
    }

    bool operator==(const Point2D& p) const noexcept
    {
        return m_x == p.m_x && m_y == p.m_y;
    }

    bool operator!=(const Point2D& p) const noexcept
    {
        return !operator==(p);
    }

    double angle() const noexcept
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

class PointF;

class Point : public Point2D<int>
{
    typedef Point2D<int> BASE;
public:
    Point(int x = 0, int y = 0) noexcept;
    Point(const Point2D<int>& point) noexcept;
    Point(const PointF& p) noexcept;

    bool operator==(const Point& p) const noexcept;
    bool operator==(const PointF& p) const noexcept;

    bool operator< (const Point& p) const;
};

class PointF : public Point2D<double>
{
    typedef Point2D<double> BASE;
public:
    PointF(double x = 0, double y = 0) noexcept;
    PointF(const Point2D<double>& point) noexcept;
    PointF(const Point& p) noexcept;

    PointF operator+(const PointF& p) const noexcept;
    friend PointF operator+(const Point& p1, const PointF& p2) noexcept;
    PointF operator-(const PointF& p) const noexcept;

    PointF& operator += (const PointF& p) noexcept;

    bool operator==(const Point& p) const noexcept;
    bool operator==(const PointF& p) const noexcept;
};

class Vector : public Point2D<double>
{
public:
    Vector(double x = 0, double y = 0) noexcept;
    Vector(const PointF& to, const PointF& from) noexcept;

    void normalize();

    operator PointF() const noexcept;
};

#endif // POINT_HPP

#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:
    Point(double x = 0, double y = 0);

    double x() const;
    double y() const;

    Point operator+(const Point& p) const;
    Point operator-() const;
    Point operator-(const Point& p) const;
    Point operator*(double d) const;
    friend Point operator*(double d, const Point& p);
    Point operator/(double d) const;

    double dot(const Point& p) const;
    double length() const;

private:
    double m_x;
    double m_y;
};

#endif // POINT_HPP

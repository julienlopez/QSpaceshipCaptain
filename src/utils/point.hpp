#ifndef POINT_HPP
#define POINT_HPP

class Point
{
public:

    static const double PI = 3.14159265;

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

    bool operator==(const Point& p) const;

    double angle() const;
    void rotate(double angle);
    void rotate(const Point &centre, double angle);

private:
    double m_x;
    double m_y;
};

#endif // POINT_HPP

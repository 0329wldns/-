#include <iostream>
#include "Point.h"

Point::Point()
	: x(0.0), y(0.0)
{
};

Point::Point(double a, double b) : x(a), y(b)
{
};

std::istream& operator>>(std::istream& is, Point& p)
{
	is >> p.x >> p.y;
	
	return is;
}
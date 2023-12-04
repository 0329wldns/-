#ifndef _Point
#define _Point

struct Point
{
	double x, y;

	Point();
	Point(double, double);
	Point(const Point&) = default;

	friend std::istream& operator>>(std::istream&, Point&);
};
#endif

#include "Point.h"
#include "Shape.h"

class Circle : public Shape
{
	Point center;
	double rad;

public:
	Circle();
	Circle(const Point&, double);
	Circle(const Circle&);
	Circle& operator=(const Circle&);
	~Circle();

	virtual void draw() const override;
};

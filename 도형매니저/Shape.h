#ifndef _Shape
#define _Shape

class Shape
{
public:
	Shape() { };
	virtual ~Shape() { };

	virtual void draw() const = 0;
};
#endif


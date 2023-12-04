#include <iostream>
#include "Point.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "ShapeManager.h"

int main()
{
	ShapeManager sm(15);

	for (int i = 0; i < 5; ++i)
		sm.insert(new Rectangle(Point(i,i), Point(i,i)));

	for (int i = 0; i < 5; ++i)
		sm.insert(new Triangle(Point(), Point(), Point()));

	for (int i = 0; i < 5; ++i)
		sm.insert(new Circle(Point(), 3.432));

	while (sm.flag) {
		sm.menu();
	}
}
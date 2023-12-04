#include <iostream>
#include "Circle.h"

Circle::Circle()
	: center(), rad(0.0)
{
}

Circle::Circle(const Point& c, double r)
	:center(c), rad(r)
{
	//std::cout << "원 생성" << '\n';
}

Circle::Circle(const Circle& other)
	:center(other.center), rad(other.rad)
{
}

Circle& Circle::operator=(const Circle& other)
{
}

Circle::~Circle()
{
	//std::cout << "원 소멸" << '\n';
}

void Circle::draw() const
{
	std::cout << "원 - 중심점(" << center.x << ", " << center.y
		<< ") 반지름 " << rad << '\n';
}

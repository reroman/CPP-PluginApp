#include "circle.hpp"
#include <iostream>
using namespace std;

Circle::Circle()
	: Figure( "Circle" ){}

void Circle::setData()
{
	cout << "Give me the value of the radius: ";
	cin >> radius;
}

double Circle::area() const
{
	return PI * radius * radius;
}

double Circle::perimeter() const
{
	return 2.0 * PI * radius;
}

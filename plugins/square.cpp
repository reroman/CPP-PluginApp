#include "square.hpp"
#include <iostream>
using namespace std;

Square::Square()
	: Figure( "Square" ){}

void Square::setData()
{
	cout << "Give the size of one side: ";
	cin >> side;
}

double Square::area() const
{
	return side * side;
}

double Square::perimeter() const
{
	return 4 * side;
}


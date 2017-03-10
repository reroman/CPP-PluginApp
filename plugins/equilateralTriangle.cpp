#include "equilateralTriangle.hpp"
#include <iostream>
#include <cmath>
using namespace std;

EquilateralTriangle::EquilateralTriangle()
	: Figure( "Equilateral Triangle" ){}

void EquilateralTriangle::setData()
{
	cout << "Give me the size of one side: ";
	cin >> side;

	double cate = side / 2.0;
	height = sqrt( side * side - cate * cate );

}

double EquilateralTriangle::area() const
{
	return side * height / 2.0;
}

double EquilateralTriangle::perimeter() const
{
	return 3 * side;
}

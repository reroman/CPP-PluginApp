#include "equilateralTriangle.hpp"

#include <iostream>
#include <cmath>

EquilateralTriangle::EquilateralTriangle()
	: Figure( "Equilateral Triangle" ){}

void EquilateralTriangle::userInput() {
  std::cout << "Give me the size of one side: ";
  std::cin >> side;

  double const cate = side / 2.0;
  height = sqrt((side * side) - (cate * cate));
}

double EquilateralTriangle::area() const {
  return side * height / 2.0;
}

double EquilateralTriangle::perimeter() const {
  return 3 * side;
}

DEFAULT_FIGURE_FACTORY(EquilateralTriangle)

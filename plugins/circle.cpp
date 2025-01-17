#include "circle.hpp"

#include <iostream>

Circle::Circle()
	: Figure( "Circle" ){}

void Circle::userInput() {
  std::cout << "Give me the value of the radius: ";
  std::cin >> radius;
}

double Circle::area() const {
  return PI * radius * radius;
}

double Circle::perimeter() const {
  return 2.0 * PI * radius;
}

DEFAULT_FIGURE_FACTORY(Circle)

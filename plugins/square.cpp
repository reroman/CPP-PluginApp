#include "square.hpp"

#include <iostream>

Square::Square()
	: Figure( "Square" ){}

void Square::userInput() {
  std::cout << "Give the size of one side: ";
  std::cin >> side;
}

double Square::area() const {
  return side * side;
}

double Square::perimeter() const {
  return 4 * side;
}

DEFAULT_FIGURE_FACTORY(Square)

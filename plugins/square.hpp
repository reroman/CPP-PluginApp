#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <Figure.hpp>

class Square final : public plugin::Figure {
 public:
  Square();

  // Figure interface
  void userInput() final;
  double area() const final;
  double perimeter() const final;

 private:
  double side{};
};

#endif

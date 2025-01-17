#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <Figure.hpp>

class Circle final : public plugin::Figure {
 public:
  static constexpr double PI = 3.14159;

  Circle();

  // Figure interface
  void userInput() final;
  double area() const final;
  double perimeter() const final;

 private:
  double radius{};
};

#endif

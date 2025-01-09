#ifndef EQUIlATERALTRIANGLE_HPP
#define EQUIlATERALTRIANGLE_HPP

#include <Figure.hpp>

class EquilateralTriangle final : public plugin::Figure {
 public:
  EquilateralTriangle();

  // Figure interface
  void userInput() final;
  double area() const final;
  double perimeter() const final;

 private:
  double side{};
  double height{};
};

#endif

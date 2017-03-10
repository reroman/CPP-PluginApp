#ifndef EQUIlATERALTRIANGLE_HPP
#define EQUIlATERALTRIANGLE_HPP

#include <Figure.hpp>

class EquilateralTriangle: public plugin::Figure
{
	public:
		EquilateralTriangle();

		void setData();
		double area() const override;
		double perimeter() const override;

	private:
		double side, height;
};

DEFAULT_REGISTER_FIGURE( EquilateralTriangle );

#endif

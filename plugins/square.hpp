#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <Figure.hpp>

class Square: public plugin::Figure
{
	public:
		Square();

		void setData() override;
		double area() const override;
		double perimeter() const override;

	private:
		double side;
};

DEFAULT_REGISTER_FIGURE( Square );

#endif

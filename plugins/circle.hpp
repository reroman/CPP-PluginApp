#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <Figure.hpp>

class Circle : public plugin::Figure
{
	public:
		Circle();

		void setData() override;
		double area() const override;
		double perimeter() const override;
		
		static constexpr double PI = 3.14159;

	private:
		double radius;
};

DEFAULT_REGISTER_FIGURE( Circle );

#endif

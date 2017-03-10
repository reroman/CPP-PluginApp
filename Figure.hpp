#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>

namespace plugin{
class Figure
{
	public:
		Figure( std::string figureName )
			: name( figureName ){}
		virtual ~Figure(){}

		inline std::string getName( void ) const{ return name; }

		virtual void setData( void ) = 0;
		virtual double area( void ) const = 0;
		virtual double perimeter( void ) const = 0;

	private:
		std::string name;
};
}

#define DEFAULT_REGISTER_FIGURE( x );		\
extern "C"{ 						 		\
									 		\
plugin::Figure* createFigure(){       		\
	return new x;                    		\
}                                    		\
                                     		\
void destroyFigure( plugin::Figure *p ){   	\
	delete p;                        		\
}									 		\
}

#endif

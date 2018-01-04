#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>

#define CREATE_FIGURE_FUNCTION	"createFigure"
#define DESTROY_FIGURE_FUNCTION	"destroyFigure"

namespace plugin{
	/**
	 * Abstract class that represents a Figure. Every plugin
	 * in this application should extends this class.
	 */
	class Figure
	{
		public:
			/**
			 * Initializes a Figure with its name.
			 */
			Figure( std::string figureName )
				: name( figureName ){}
			virtual ~Figure(){}

			/**
			 * Gets the name of the figure.
			 */
			inline std::string getName( void ) const{ return name; }

			// ==== Methods that must be override ====
			/**
			 * Set required values to calculate area and perimeter
			 */
			virtual void setData( void ) = 0;

			/**
			 * Calculate the area of the figure.
			 * @return The value of the area.
			 */
			virtual double area( void ) const = 0;

			/**
			 * Calculate the perimeter of the figure.
			 * @return The value of the perimeter.
			 */
			virtual double perimeter( void ) const = 0;

		private:
			std::string name;
	};
}

/**
 * Every plugin created must implement these two
 * C functions: createFigure and destroyFigure. This macro
 * uses default constructors to create/destroy the figures.
 */
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

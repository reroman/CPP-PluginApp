#ifndef FIGURELOADER_HPP
#define FIGURELOADER_HPP

#include "Figure.hpp"
#include <string>
#include <list>

#ifdef _WIN32
#include <windows.h>
#endif

namespace plugin{

	// Pointers to createFigure() and destroyFigure() functions.
	using Creator = Figure* (*)();
	using Destroyer = void (*)( Figure* );

	// Helper class that loads a Figure from a dynamic link library
	class FigureLoader
	{
		public:
			/**
			 * Loads the figure.
			 * @param fileName The file that contains the figure.
			 * @throw std::runtime_error In case of error.
			 */
			FigureLoader( std::string fileName );
			~FigureLoader();

			/**
			 * Returns a pointer to the loaded Figure
			 */
			Figure* getFigure( void ) const;

			/**
			 * Returns the name of the file loaded.
			 */
			std::string getLibname( void ) const;

		private:
			static std::list<std::string> loadedLibs;	///< List of files loaded
			std::string libname;
#ifdef _WIN32
			HMODULE handle;
#else
			void *handle;
#endif
			Creator create;
			Destroyer destroy;
			Figure *figure;
	};
}
#endif

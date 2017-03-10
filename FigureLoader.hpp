#ifndef FIGURELOADER_HPP
#define FIGURELOADER_HPP

#include "Figure.hpp"
#include <string>
#include <list>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

namespace plugin{

using Creator = Figure* (*)();
using Destroyer = void (*)( Figure* );

class FigureLoader
{
	public:
		FigureLoader( std::string fileName ) throw( std::runtime_error );
		~FigureLoader();
		Figure* getFigure( void ) const;
		std::string getLibname( void ) const;
		
	private:
		static std::list<std::string> loadedLibs;
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

#include "FigureLoader.hpp"
#include <algorithm>
#include <stdexcept>
using std::runtime_error;
using std::string;

#ifdef _WIN32
#include <windows.h>

#define dlclose( x )	FreeLibrary( x )

/**
 * windows version for dlerror()
 */
string dlerror()
{
    //Get the error message, if any.
    DWORD errorMessageID = GetLastError();
    if(errorMessageID == 0)
        return string(); //No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    string message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);
    return message;
}

#else
# include <dlfcn.h>
#endif

namespace plugin{

std::list<string> FigureLoader::loadedLibs;

FigureLoader::FigureLoader( std::string fileName )
	: libname( fileName )
{
	// Check if the file is already loaded
	if( std::find( loadedLibs.begin(), loadedLibs.end(), libname ) != loadedLibs.end() )
		throw runtime_error( libname + ": already loaded" );

	// Open the library
#ifdef _WIN32
	handle = LoadLibrary( libname.c_str() );
#else
	handle = dlopen( libname.c_str(), RTLD_LAZY );
#endif

	if( !handle )
		throw runtime_error( dlerror() );

	// Obtain the address of the createFigure() function.
#ifdef _WIN32
	create = reinterpret_cast<Creator>( GetProcAddress( handle, CREATE_FIGURE_FUNCTION ) );
#else
	*reinterpret_cast<void**>( &create ) = dlsym( handle, CREATE_FIGURE_FUNCTION );
#endif
	if( !create ){
		string error( dlerror() );
		dlclose( handle );
		throw runtime_error( error );
	}

	// Obtain the address of the destroyFigure() function.
#ifdef _WIN32
	destroy = reinterpret_cast<Destroyer>( GetProcAddress( handle, DESTROY_FIGURE_FUNCTION ) );
#else
	*reinterpret_cast<void**>( &destroy ) = dlsym( handle, DESTROY_FIGURE_FUNCTION );
#endif
	if( !destroy ){
		string error( dlerror() );
		dlclose( handle );
		throw runtime_error( error );
	}

	// Create the figure using createFigure() function found in the file.
	figure = create();
	loadedLibs.push_back( libname );
}
	
FigureLoader::~FigureLoader()
{
	// Destroy the figure and close the library file
	destroy( figure );
	dlclose( handle );
	loadedLibs.remove( libname );
}

Figure* FigureLoader::getFigure( void ) const
{
	return figure;
}

string FigureLoader::getLibname( void ) const
{
	return libname;
}

}

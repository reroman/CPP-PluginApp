#include "FigureLoader.hpp"
#include <algorithm>
using std::runtime_error;
using std::string;

#ifdef _WIN32
#include <windows.h>

#define dlclose( x )	FreeLibrary( x )

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

FigureLoader::FigureLoader( std::string fileName ) throw( runtime_error )
	: libname( fileName )
{
	if( std::find( loadedLibs.begin(), loadedLibs.end(), libname ) != loadedLibs.end() )
		throw runtime_error( libname + ": already loaded" );

#ifdef _WIN32
	handle = LoadLibrary( libname.c_str() );
#else
	handle = dlopen( libname.c_str(), RTLD_LAZY );
#endif

	if( !handle )
		throw runtime_error( dlerror() );

#ifdef _WIN32
	create = reinterpret_cast<Creator>( GetProcAddress( handle, "createFigure" ) );
#else
	*reinterpret_cast<void**>( &create ) = dlsym( handle, "createFigure" );
#endif
	if( !create ){
		string error( dlerror() );
		dlclose( handle );
		throw runtime_error( error );
	}

#ifdef _WIN32
	destroy = reinterpret_cast<Destroyer>( GetProcAddress( handle, "destroyFigure" ) );
#else
	*reinterpret_cast<void**>( &destroy ) = dlsym( handle, "destroyFigure" );
#endif
	if( !destroy ){
		string error( dlerror() );
		dlclose( handle );
		throw runtime_error( error );
	}

	figure = create();
	loadedLibs.push_back( libname );
}
	
FigureLoader::~FigureLoader()
{
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

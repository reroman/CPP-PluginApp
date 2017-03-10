#include "FigureLoader.hpp"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
using namespace plugin;

int main( int argc, char **argv )
{
#ifdef _WIN32
#define popen _popen
	const char *cmd = "dir /B plugins\\*.dll";
#else
	const char *cmd = "ls plugins | grep .so";
#endif

	vector<FigureLoader*> figures;
	FILE *fileLibs = popen( cmd, "r" );
	char libname[200];
	int option;

	while( fgets( libname, 200, fileLibs ) ){
		*strrchr( libname, '\n' ) = '\0';

		try{
			figures.push_back( new FigureLoader( "plugins/" + string(libname) ) );
		}
		catch( runtime_error &e ){
			cerr << "Failed to load: " << libname
				<< "\n\t" << e.what() << endl;
		}
	}
	fclose( fileLibs );

	while( true ){
		cout << "Select a Figure:\n";
		for( unsigned i = 0 ; i < figures.size() ; i++ )
			cout << '\t' << i+1 << ") " << figures[i]->getFigure()->getName() << endl;
		cout << "\t*) Quit\nOption: ";
		cin >> option;

		try{
			plugin::Figure *p = figures.at( option-1 )->getFigure();
			p->setData();
			cout << "Area is " << p->area()
				<< "\nPerimeter is " << p->perimeter() << "\n\n";
		}
		catch( out_of_range &e ){
			cout << "Bye\n";
			break;
		}
	}

	for( auto i : figures )
		delete i;
	return 0;
}

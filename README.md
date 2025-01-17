# CPP-PluginApp
This application is an example of how to create extensible applications
using plugins in C++. This code is for teaching purposses.

## What does the app do?
The app calculates the area and perimeter of some figures. The necessary
code for each figure is in a shared library in the plugins directory. The app
tries to load every .so/.dll/.dylib file in that folder (unless some other
folder were passed as argument) at runtime.

## Quick overview of the code
There are two important classes: **plugin::Figure** and
**plugin::FigureLoader**. The first one is an abstract class that every plugin
must be inherit from. The second one is loader and owner of each plugin, it uses
the system API to load shared libraries at runtime.

### Class plugin::Figure
This class has one field for the name of the figure and three pure virtual
functions:
* `userInput()`: It's used to initialize all required values to make the
mathematics.
* `area()`: Calculates and returns the value of the area.
* `perimeter()`: Calculates and returns the value of the perimeter.

Also, for every derived class (plugin) must be a C function (`figureFactory()`),
that creates and returns a pointer to the derived class. There is the macro
(`DEFAULT_FIGURE_FACTORY`) that defines this function using the default
constructor of the class.

### Class plugin::FigureLoader
It encapsulates the functionality to load a dynamic library and create a
figure. It uses system APIs made in C and that's why the factory
function needs to be declared as C code (and because name mangling is simpler
than C++). The constructor loads the shared library using `dlopen()` or
`LoadLibrary()` function depending on the OS, searches the
factory function and calls it to create an instance of the plugin.

## Compilation and execution
### Using cmake

```
git clone https://github.com/reroman/CPP-PluginApp.git
cd CPP-PluginApp
cmake -B build .
cmake --build build
```

You can disable the build of plugins executing cmake as follows:

```
cmake -B build -DBUILD_PLUGINS=OFF .
```

... and create your own, just put the files in the plugins directory. 

To execute:

```
cd build
./figures plugins
```

If you don't pass a folder name it will take *plugins* directory by default.


## Author
Ricardo Román. Email: [reroman4@gmail.com](mailto:reroman4@gmail.com).


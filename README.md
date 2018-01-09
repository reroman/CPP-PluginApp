# CPP-PluginApp
This application is an example of how to create extensible applications
using plugins in C++.

## What the app does
The app calculates the area and perimeter of some figures. The necessary
code for each figure is in a shared library in the plugins directory. The
app tries to load every .so/.dll file in that folder at runtime.

## Quick overview of the code
There are two important classes: **plugin::Figure** and **plugin::FigureLoader**.
The first one is an abstract class that every plugin must be inherit from.
The second one is a helper that uses system APIs to load libraries at runtime.

### Class plugin::Figure
This class has one field for the name of the figure and three abstract methods:
* **setData**: It's used to initialize all required values to make the mathematics.
* **area**: Calculates and returns the value of the area.
* **perimeter**: Calculates and returns the value of the perimeter.

Also, for every derived class must be two methods, one to create a figure and one more
to destroy it. These methods must be declared as "C" code. The code
defines the macro **DEFAULT\_REGISTER\_FIGURE** for this purpose using default constructors
of the class within a `extern "C"` block.

### Class plugin::FigureLoader
Encapsulates the functionality to load a dynamic library and create a
figure. It uses system APIs made in C. That's the reason why the functions need 
to be declared as C code. The constructor loads a shared library using *dlopen()*
or *LoadLibrary()* function depending on the OS. After that, it is used the 
**plugin::Figure \*createFigure()** function to allocate and initialize an object.
When the object is destroyed the function **void destroyFigure( plugin::Figure\* )**
is called and the figure and library are both released.

## Compilation and execution
### Using cmake
```
mkdir build     # Create a new directory
cd build        # Change to it
cmake ..        # Execute cmake 
make            # Execute make
./figures       # Execute the program
```

You can disable the build of plugins executing cmake as follows:
```
cmake -DBUILD_PLUGINS=OFF ..
```

### Using only g++
```
g++ -o figures FigureLoader.cpp main.cpp -ldl   # Compile main program
cd plugins                                      # Change to plugins directory
g++ -o libcircle.so circle.cpp -fPIC -shared -I.. # Compile the library
cd ..                                           # Change to the parent
./figures                                       # Execute the program
```

## Author
Ricardo Román. Email: [reroman4@gmail.com](mailto:reroman4@gmail.com).
Telegram: [@reroman](https://t.me/reroman)


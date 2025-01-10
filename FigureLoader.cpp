#include "FigureLoader.hpp"

#include <stdexcept>

#ifdef _WIN32

namespace {

/** @brief Windows version for dlerror(). */
std::string dlerror() {
  DWORD const errorMessageID = GetLastError();
  if (errorMessageID == 0) {
    return std::string();
  }

  LPSTR messageBuffer = nullptr;
  size_t const size = FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)&messageBuffer, 0, NULL);

  std::string message(messageBuffer, size);

  LocalFree(messageBuffer);
  return message;
}

} // namespace

#endif

namespace plugin {

FigureLoader::FigureLoader(std::string_view fileName) : libname(fileName) {
  // Open the library.
#ifdef _WIN32
  handle.reset(LoadLibrary(libname.c_str()));
#else
  handle.reset(dlopen(libname.c_str(), RTLD_LAZY));
#endif

  if (!handle) {
    throw std::runtime_error(dlerror());
  }

  // Get the address of the figureFactory() function.
#ifdef _WIN32
  factory =
      reinterpret_cast<FactoryFn>(GetProcAddress(handle.get(), FACTORY_NAME));
#else
  factory = reinterpret_cast<FactoryFn>(dlsym(handle.get(), FACTORY_NAME));
#endif

  if (factory == nullptr) {
    throw std::runtime_error(dlerror());
  }

  // Create the figure instance.
  figure.reset(factory());
}

} // namespace plugin

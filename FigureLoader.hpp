#ifndef FIGURELOADER_HPP
#define FIGURELOADER_HPP

#include <memory>
#include <string>
#include <string_view>

#include "Figure.hpp"

#ifdef _WIN32
#include <windows.h>
#include <type_traits>

// Just for using the same name in both platforms.
using LibraryHandler = std::remove_pointer<HMODULE>::type;

inline void dlclose(LibraryHandler* handle) noexcept {
  FreeLibrary(handle);
}

#else
#include <dlfcn.h>
using LibraryHandler = void;
#endif

namespace plugin {

/**
 * @brief Loads and holds a figure from a shared library.
 */
class FigureLoader {
 public:
  /**
   * @brief Loads an instance of a plugin::Figure.
   * @param libraryPath Name of the file that contains the figure.
   * @throw std::runtime_error In case of error.
   */
  explicit FigureLoader(std::string_view libraryPath);

  /** @brief Gets the name of the file loaded. */
  std::string const& getLibname() const noexcept { return libname; }

  /** @brief Gets the instance of the figure loaded. */
  Figure& getFigure() const& noexcept { return *figure; }

  /** @note Not for rvalues. The library should remain open. */
  void getFigure() && = delete;

 private:
  /** @brief Deleter for the library handler. */
  struct LibHandlerDeleter {
    void operator()(LibraryHandler* handle) noexcept { dlclose(handle); }
  };

  std::string libname;
  std::unique_ptr<LibraryHandler, LibHandlerDeleter> handle;
  std::unique_ptr<Figure> figure;
};

} // namespace plugin
#endif

#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <string>
#include <string_view>

namespace plugin {

/** @brief Name of the factory function that creates a Figure object. */
constexpr auto FACTORY_NAME = "figureFactory";

/**
 * @brief Abstract class that represents a plugin Figure.
 * @details Every plugin in this application should extends this class and
 * override the functions userInput(), area() and perimeter(). It also requires
 * to define a C function figureFactory() that returns a pointer to a
 * Figure object.
 * @note MSVC doesn't support std::unique_ptr as return type in C functions.
 */
class Figure {
 public:
  /** @brief Initializes a Figure with its name. */
  Figure(std::string_view figureName) : name(figureName) {}

  /** @brief Destructor. */
  virtual ~Figure() = default;

  /** @brief  Gets the name of the figure. */
  std::string const& getName() const noexcept { return name; }

  /**
   * @brief Ask the user the required values to calculate area and perimeter.
   */
  virtual void userInput() = 0;

  /** @brief Calculate and return the area of the figure. */
  virtual double area() const = 0;

  /** @brief Calculate and return the perimeter of the figure. */
  virtual double perimeter() const = 0;

 protected:
  Figure(Figure const& other) = delete;
  Figure(Figure&& other) noexcept = default;
  Figure& operator=(Figure const& other) = delete;
  Figure& operator=(Figure&& other) noexcept = default;

 private:
  std::string name;
};

} // namespace plugin

#ifdef _MSC_VER
// Required for MSVC to locate the functions correctly.
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

/** @brief Default implementation of the figureFactory() function. */
#define DEFAULT_FIGURE_FACTORY(figure)                \
  extern "C" EXPORT plugin::Figure* figureFactory() { \
    return new figure();                              \
  }

#endif

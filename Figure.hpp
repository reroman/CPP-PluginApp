#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <memory>
#include <string>
#include <string_view>

namespace plugin {

/** @brief Name of the factory function that creates a Figure object. */
constexpr auto FACTORY_NAME = "figureFactory";

/**
 * @brief Abstract class that represents a plugin Figure.
 * @details Every plugin in this application should extends this class and
 * override the functions userInput(), area() and perimeter(). It also requires
 * to define a C function figureFactory() that returns a unique pointer to a
 * Figure object.
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

}  // namespace plugin

/** @brief Default implementation of the figureFactory() function. */
#define DEFAULT_FIGURE_FACTORY(figure)                         \
  extern "C" std::unique_ptr<plugin::Figure> figureFactory() { \
    return std::make_unique<figure>();                         \
  }

#endif

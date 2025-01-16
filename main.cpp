#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "FigureLoader.hpp"

/**
 * @brief Get the list of files in a directory.
 * @param directory Name of the directory.
 * @return A vector with the names of the files in the directory.
 */
std::vector<std::string> getPluginList(std::string_view directory);

int main(int argc, char** argv) {
  std::string const pluginsDir = [&]() {
    if (argc > 1) {
      return std::string(argv[1]);
    }
    return std::string("plugins");
  }();

  std::vector<plugin::FigureLoader> loaders;

  for (auto const plugins = getPluginList(pluginsDir);
       auto const& pluginFile : plugins) {
    try {
      std::cout << "Loading " << pluginFile << "...";
      loaders.emplace_back(pluginFile);
      std::cout << " Loaded!\n";
    } catch (std::runtime_error const& e) {
      std::cerr << "Failed: " << e.what() << '\n';
    }
  }

  while (true) {
    std::cout << "\nSelect a Figure:";
    for (int index = 1; auto const& loader : loaders) {
      std::cout << "\n\t" << index++ << ") " << loader.getFigure().getName();
    }
    std::cout << "\n\t*) Quit\nOption: ";

    std::size_t selection{};
    std::cin >> selection;

    try {
      plugin::Figure& figure = loaders.at(selection - 1).getFigure();

      figure.userInput();
      std::cout << "Area is " << figure.area() << "\nPerimeter is "
                << figure.perimeter() << '\n';
    } catch (std::out_of_range const&) {
      std::cout << "Bye\n";
      break;
    }
  }
  return 0;
}

std::vector<std::string> getPluginList(std::string_view directory) try {
  std::filesystem::path const pluginsDir(directory);
  std::vector<std::string> plugins;

  for (auto const& entry : std::filesystem::directory_iterator(pluginsDir)) {
    if (auto const& ext = entry.path().extension();
        entry.is_regular_file() &&
        (ext == ".dll" || ext == ".so" || ext == ".dylib")) {
      plugins.push_back(entry.path().relative_path().string());
    }
  }
  return plugins;
} catch (std::filesystem::filesystem_error const& e) {
  std::cerr << e.what() << '\n';
  return {};
}

#include <filesystem>
#include <iostream>
#include <print>
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
      // Load the plugin
      loaders.emplace_back(pluginFile);
    } catch (std::runtime_error const& e) {
      std::println(stderr, "Failed to load: {}\n\t{}", pluginFile, e.what());
    }
  }

  while (true) {
    std::println("Select a Figure:");
    for (int index = 1; auto const& loader : loaders) {
      std::println("\t{}) {}", index++, loader.getFigure().getName());
    }
    std::print("\t*) Quit\nOption: ");

    std::size_t selection{};
    std::cin >> selection;

    try {
      plugin::Figure& figure = loaders.at(selection - 1).getFigure();

      figure.userInput();
      std::println(
          "Area is {}\n"
          "Perimeter is {}\n",
          figure.area(), figure.perimeter());
    } catch (std::out_of_range const&) {
      std::println("Bye");
      break;
    }
  }
  return 0;
}

std::vector<std::string> getPluginList(std::string_view directory) {
  std::filesystem::path const pluginsDir(directory);
  std::vector<std::string> plugins;

  for (auto const& entry : std::filesystem::directory_iterator(pluginsDir)) {
    if (entry.is_regular_file()) {
      plugins.push_back(entry.path().relative_path().string());
    }
  }
  return plugins;
}

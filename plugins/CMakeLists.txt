add_library(square SHARED square.hpp square.cpp)
target_link_libraries(square PRIVATE figure_plugin)

add_library(equilateraltriangle SHARED equilateralTriangle.hpp
                                       equilateralTriangle.cpp)
target_link_libraries(equilateraltriangle PRIVATE figure_plugin)

add_library(circle SHARED circle.hpp circle.cpp)
target_link_libraries(circle PRIVATE figure_plugin)

cmake_minimum_required(VERSION 3.10)

project(YAIS CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")  # Full gas

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# First executable
add_executable(ising.out
    code/main.cpp
    code/configuration.cpp
    code/MCMCengine.cpp
)
target_link_libraries(ising.out
    PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
)

#  Second executable
add_executable(isingGraphics.out
    code/graphics.cpp
    code/configuration.cpp
    code/MCMCengine.cpp
)
target_link_libraries(isingGraphics.out
    PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
)

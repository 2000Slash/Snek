cmake_minimum_required(VERSION 3.10)

# set the project name
project(Snek)

# add the executable
add_executable(Snek src/main.cpp src/Snek.cpp src/ObjectManager.cpp)
set(CMAKE_BUILD_TYPE Debug)
target_link_libraries(Snek SDL2 SDL2_image)
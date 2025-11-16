cmake_minimum_required(VERSION 3.10)
project(Ping-Pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
file(GLOB SOURCES "src/*.cpp")

add_executable(table_tennis ${SOURCES})
target_include_directories(table_tennis PRIVATE src)
target_link_libraries(table_tennis PRIVATE sfml-graphics sfml-window sfml-system)

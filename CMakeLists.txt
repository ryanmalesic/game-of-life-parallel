cmake_minimum_required(VERSION 3.16)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)

find_package(RAJA REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(include)
add_subdirectory(src)

target_link_libraries(GameOfLife PUBLIC RAJA)
if (OpenMP_CXX_FOUND)
    target_link_libraries(GameOfLife PUBLIC OpenMP::OpenMP_CXX)
endif ()
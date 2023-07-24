cmake_minimum_required(VERSION 3.25)
project(cppdemo)

set(CMAKE_CXX_STANDARD 11)

add_executable(rvo rvo.cpp)
target_compile_options(rvo PRIVATE -fno-elide-constructors)

add_executable(move move.cpp)
target_compile_options(move PRIVATE -fno-elide-constructors)

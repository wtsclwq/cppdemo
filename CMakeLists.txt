cmake_minimum_required(VERSION 3.25)
project(cppdemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(rvo rvo.cpp)
target_compile_options(rvo PRIVATE -fno-elide-constructors)

add_executable(move move.cpp)
target_compile_options(move PRIVATE -fno-elide-constructors)

add_executable(u_ptr u_ptr.cpp)
target_compile_options(u_ptr PRIVATE -fno-elide-constructors)

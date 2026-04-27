cmake_minimum_required(VERSION 3.10)
project(Clicker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(clicker glowny.cpp)

install(TARGETS clicker DESTINATION bin)

install(FILES klasizm2.h random.h saver.h DESTINATION include/clicker)

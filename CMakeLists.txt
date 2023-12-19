cmake_minimum_required(VERSION 3.20)
project(designated_init)

find_package(Boost REQUIRED system iostreams)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB Sources *.cpp *.cc)

add_executable(designated_init ${Sources})
target_link_libraries(designated_init Boost::system Boost::iostreams)

cmake_minimum_required(VERSION 3.7)
project(CPPCAD)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FALGS "${CMAKE_CXX_FALGS} -w")
INCLUDE_DIRECTORIES(sys/include MygraphicLib/include)

add_subdirectory(sys)
add_subdirectory(MygraphicLib)
add_executable(CPPCAD main.cpp)
target_link_libraries(CPPCAD sysLib)
target_link_libraries(CPPCAD MygraphicLib)
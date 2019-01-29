cmake_minimum_required(VERSION 3.5)

project(AVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11 -fsanitize=address -fno-omit-frame-pointer")

set(SRC Lexer.cpp main.cpp Parser.cpp Factory.cpp)

add_executable(avm ${SRC})
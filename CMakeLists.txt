cmake_minimum_required(VERSION 3.5)

project(AVM)

include_directories(
        ${PROJECT_SOURCE_DIR}/inc
        ${PROJECT_SOURCE_DIR}/src
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11 -fsanitize=address -fno-omit-frame-pointer")

set(SRC src/Lexer.cpp src/main.cpp src/Parser.cpp src/Factory.cpp)

add_executable(avm ${SRC})
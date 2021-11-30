cmake_minimum_required (VERSION 3.16.3)

project(REPL-for-cpp)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 \
#    -Wall -Wextra -Werror -Wextra-semi -Wno-self-assign-overloaded -Wno-self-assign-overloaded -Wvla-extension \
#    -g -v -O0 \
#    -fsanitize=address -fno-omit-frame-pointer -fno-operator-names")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -ldl")

add_executable(REPL-for-cpp main.cpp)
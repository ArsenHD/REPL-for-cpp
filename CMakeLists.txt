cmake_minimum_required (VERSION 3.8)

project(REPL-for-cpp)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20
    -Wall -Wextra -Werror -Wextra-semi -Wno-self-assign-overloaded -Wno-self-assign-overloaded -Wvla-extension \
    -g -v -O0
    -fsanitize=address -fno-omit-frame-pointer -fno-operator-names")
endif()

add_executable()
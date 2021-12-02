cmake_minimum_required (VERSION 3.8)

project(REPL-for-cpp)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 \
#    -Wall -Wextra -Werror -Wextra-semi -Wno-self-assign-overloaded -Wno-self-assign-overloaded -Wvla-extension \
#    -g -v -O0 \
#    -fsanitize=address -fno-omit-frame-pointer -fno-operator-names")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -L./libs -Wl,-rpath=./libs")

add_executable(REPL-for-cpp main.cpp
        utils/library_utils.cpp
        utils/code_generator.cpp
        utils/ast_utils.cpp
        utils/directory_manager.cpp
        flags/flags.cpp multiline/code_block.cpp
        model/file_model.cpp
        )
target_link_libraries(REPL-for-cpp dl)
